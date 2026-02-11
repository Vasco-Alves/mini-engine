#pragma once

#include <cstdint>

namespace me {

	class Registry;

	namespace entity {
		using entity_id = std::uint32_t;
		constexpr entity_id null = 0;
	}

	class Entity {
	public:
		Entity() = default;
		Entity(entity::entity_id id, Registry* registry) : m_id(id), m_registry(registry) {}

		entity::entity_id id() const {
			return m_id;
		}

		bool is_valid() const {
			return m_id != entity::null && m_registry != nullptr;
		}

		operator bool() const {
			return is_valid();
		}

		template <typename T>
		void add_component(const T& component);

		template <typename T>
		T* get_component();

		template <typename T>
		bool has_component() const;

		void destroy();

	private:
		entity::entity_id m_id = entity::null;
		Registry* m_registry = nullptr;
	};

} // namespace me