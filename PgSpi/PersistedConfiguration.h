#pragma once

#include <string>
#include <exception>
#include <stdexcept>

namespace spi
{
	class ConfigNode
	{
	public:
		virtual ~ConfigNode() = 0;
		virtual const std::string asString() const = 0;
	};

	class PersistedConfiguration
	{
	public:
		virtual ~PersistedConfiguration() = 0;

		virtual void persist(const std::string& name) const;
		virtual void load(const std::string& name);
		virtual void loadAll(const std::string& name);


		template<typename T>
		const T get(const std::string& name) const
		{
			throw std::domain_error("Unsupported type for name: " + name);
		}

	protected:
		virtual ConfigNode* getNode(const std::string& name) const = 0;
	};

	template<>
	const std::string PersistedConfiguration::get<std::string>(const std::string& name) const
	{
		ConfigNode* const node = getNode(name);
		if (!node)
		{
			throw std::invalid_argument("Unknown name: " + name);
		}
		return node->asString();
	}
}