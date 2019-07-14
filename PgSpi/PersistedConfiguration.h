#pragma once

#include <string>
#include <charconv>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <atomic>
#include <type_traits>
#include <shared_mutex>

namespace spi
{
	namespace traits
	{
		template <typename T>
		constexpr bool isAtomic()
		{
			return std::is_trivially_copyable_v<T> && std::is_copy_constructible_v<T> && std::is_move_constructible_v<T>
				&& std::is_copy_assignable_v<T> && std::is_move_assignable_v<T>;
		}
	}

	template <typename V>
	struct AtomicValue
	{
		using value_type = V;

		AtomicValue()
		{
		}
		AtomicValue(V src)
		{
			set(src);
		}
		AtomicValue(const AtomicValue<V>& src) = delete;
		AtomicValue(AtomicValue<V>&& src) = delete;
		AtomicValue<V>& operator = (const AtomicValue<V>& src) = delete;
		AtomicValue<V>& operator = (AtomicValue<V>&& src) = delete;

		V get() const
		{
			return value.load(std::memory_order::memory_order_acquire);
		}
		void set(const V src)
		{
			value.store(src, std::memory_order::memory_order_release);
		}

	private:
		std::atomic<V> value;
	};

	template <typename V>
	struct LockedValue
	{
		using value_type = std::string;

		LockedValue()
		{
		}
		LockedValue(const V& src)
		{
			set(src);
		}
		LockedValue(const LockedValue<V>& src) = delete;
		LockedValue(LockedValue<V>&& src) = delete;
		LockedValue<V>& operator = (const LockedValue<V>& src) = delete;
		LockedValue<V>& operator = (LockedValue<V>&& src) = delete;

		V get() const
		{
			std::shared_lock lock{ mutex };
			return value;
		}
		void set(const V& src)
		{
			std::unique_lock lock{ mutex };
			value = src;
		}

	private:
		mutable std::shared_mutex mutex;
		V value;
	};

	template <typename V, typename N = std::conditional<traits::isAtomic<V>(), AtomicValue<V>, LockedValue<V>>::type>
	struct Value
	{
		using value_type = V;
		using wrapper_type = N;

		Value()
		{
		}

		Value(V src)
		{
			value.set(src);
		}
		Value(const Value<V, N>& src) = delete;
		Value(const Value<V, N>&& src) = delete;
		Value<V, N> operator = (const Value<V, N>& src) = delete;
		Value<V, N> operator = (Value<V, N>&& src) = delete;

		V get() const
		{
			return value.get();
		}

		void set(V src)
		{
			value.set(src);
		}
	private:
		N value;
	};

	/*
	class PersistedConfiguration
	{
	public:
		virtual ~PersistedConfiguration() = 0;

		virtual void persist(const std::string& name) const = 0;
		virtual void load(const std::string& name) = 0;
		virtual void loadAll(const std::string& name) = 0;

		template<typename T>
		const T& get(const std::string& name) const
		{
			throw std::domain_error("Unsupported type for name: " + name);
		}

	protected:
		virtual const ConfigValue* findNode(const std::string& name) const = 0;

		inline const ConfigValue& node(const std::string& name) const
		{
			const ConfigValue* const node = findNode(name);
			if (!node)
			{
				throw std::invalid_argument("Unknown name: " + name);
			}
			return *node;
		}
	};

	template<>
	inline const std::string& PersistedConfiguration::get<std::string>(const std::string& name) const
	{
		return node(name).asString();
	}

	template<>
	inline const float& PersistedConfiguration::get<float>(const std::string& name) const
	{
		return node(name).asFloat();
	}

	template<>
	inline const int& PersistedConfiguration::get<int>(const std::string& name) const
	{
		return node(name).asInt();
	}

	template<>
	inline const bool& PersistedConfiguration::get<bool>(const std::string& name) const
	{
		return node(name).asBool();
	}*/
}