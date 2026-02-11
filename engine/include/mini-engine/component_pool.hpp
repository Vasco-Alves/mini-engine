#pragma once

#include "mini-engine/entity.hpp"

#include <unordered_map>

namespace me::detail {

	// Base interface allows us to store different pools in a list
	struct IPool {
		virtual ~IPool() = default;
		virtual void remove(me::entity::entity_id e) = 0;
		virtual bool has(me::entity::entity_id e) const = 0;
	};

	template <typename T>
	struct ComponentPool : public IPool {
		std::unordered_map<me::entity::entity_id, T> data;

		void add(me::entity::entity_id e, const T& component) {
			data[e] = component;
		}

		T* try_get(me::entity::entity_id e) {
			auto it = data.find(e);
			return (it != data.end()) ? &it->second : nullptr;
		}

		bool has(me::entity::entity_id e) const override {
			return data.find(e) != data.end();
		}

		void remove(me::entity::entity_id e) override {
			data.erase(e);
		}
	};

} // namespace me::detail