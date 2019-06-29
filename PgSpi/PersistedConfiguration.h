#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <atomic>

namespace spi
{
	class ConfigValue
	{
	public:

		inline const std::string asString() const
		{
			return "";// text.load(std::memory_order::memory_order_acq_rel);
		}

		virtual float asFloat() const = 0;
		virtual int asInt() const = 0;
		virtual bool asBool() const = 0;

		inline void fromString(const std::string& value)
		{
			//text.store(value, std::memory_order::memory_order_acq_rel);
		}

		virtual void fromFloat(float value) = 0;
		virtual void fromInt(int value) = 0;
		virtual void fromBool(bool value) = 0;

	protected:
		virtual void updateValue(const std::string& value) = 0;

	private:
		//std::atomic<std::string> text;
	};

	template <typename V>
	class SimpleValue : ConfigValue
	{
	public:
		virtual float asFloat() const
		{
			return static_cast<float>(get());
		}

		virtual int asInt() const
		{
			return static_cast<int>(get());
		}

		virtual bool asBool() const
		{
			return static_cast<bool>(get());
		}

		virtual void fromFloat(float src)
		{
			set(src);
		}

		virtual void fromInt(int src)
		{
			set(src);
		}

		virtual void fromBool(bool src)
		{
			set(src);
		}

	protected:
		inline V get()
		{
			return value.load(std::memory_order::memory_order_acq_rel);
		}

		inline void set(V src)
		{
			value.store(src, std::memory_order::memory_order_acq_rel);
		}

		virtual void updateValue(const std::string& src)
		{
			value.store(::atof(src.c_str()), std::memory_order::memory_order_acq_rel);
		}

	private:
		std::atomic<V> value;
	};


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
	}
}