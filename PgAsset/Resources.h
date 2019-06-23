#pragma once

#include <istream>
#include <string>
#include <vector>
#include <optional>

namespace assets
{
	class Resources
	{
	public:
		virtual ~Resources() = 0;

		virtual std::optional<std::istream> open(const std::string& resource) = 0;

		virtual std::vector<std::istream> openAll(const std::string& resource) = 0;
	};
}