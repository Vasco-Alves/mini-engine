#pragma once

#include "mini-engine/entity.hpp"
#include "mini-engine/component_pool.hpp"

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>

namespace me {

	namespace detail {
		struct EntityRecord {
			std::string name;
			bool alive = true;
		};
	}

	class Registry {
	public:
		Entity create_entity(const std::string& name = "Entity") {
			entity::entity_id id = m_nextId++;
			m_entities[id] = { name, true };
			return Entity(id, this);
		}

		void destroy_entity(entity::entity_id e) {
			if (m_entities.find(e) != m_entities.end()) {
				m_entities[e].alive = false;
				remove_entity(e);
			}
		}

		bool is_alive(entity::entity_id e) const {
			auto it = m_entities.find(e);
			return (it != m_entities.end()) && it->second.alive;
		}

		// ---------------------------------------------------------------------
		// Component Management
		// ---------------------------------------------------------------------

		template <typename T>
		void add_component(entity::entity_id e, const T& component) {
			get_pool<T>()->add(e, component);
		}

		template <typename T>
		T* try_get_component(entity::entity_id e) {
			return get_pool<T>()->try_get(e);
		}

		template <typename T>
		bool has_component(entity::entity_id e) {
			return get_pool<T>()->has(e);
		}

		// Returns the raw map so you can iterate: for(auto& [id, comp] : view)
		template <typename T>
		auto& view() {
			return get_pool<T>()->data;
		}

	private:
		// Helper to find or create the specific pool for type T
		template<typename T>
		detail::ComponentPool<T>* get_pool() {
			auto typeId = std::type_index(typeid(T));
			if (m_pools.find(typeId) == m_pools.end())
				m_pools[typeId] = std::make_unique<detail::ComponentPool<T>>();
			return static_cast<detail::ComponentPool<T>*>(m_pools[typeId].get());
		}

		void remove_entity(me::entity::entity_id e) {
			for (auto& pair : m_pools)
				pair.second->remove(e);
		}

	private:
		std::unordered_map<entity::entity_id, detail::EntityRecord> m_entities;
		std::unordered_map<std::type_index, std::unique_ptr<detail::IPool>> m_pools;
		entity::entity_id m_nextId = 1;
	};

	// ---------------------------------------------------------------------
	// Entity Implementation
	// ---------------------------------------------------------------------

	template <typename T>
	void Entity::add_component(const T& component) {
		if (m_registry) m_registry->add_component<T>(m_id, component);
	}

	template <typename T>
	T* Entity::get_component() {
		if (m_registry) return m_registry->try_get_component<T>(m_id);
		return nullptr;
	}

	template <typename T>
	bool Entity::has_component() const {
		if (m_registry) return m_registry->has_component<T>(m_id);
		return false;
	}

	inline void Entity::destroy() {
		if (m_registry) m_registry->destroy_entity(m_id);
	}

} // namespace me