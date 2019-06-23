#pragma once

#include <memory>
#include <istream>

namespace assets
{
	template <typename T, typename C>
	class ReadableAsset
	{
	public:
		virtual ~ReadableAsset() = 0;

		virtual std::unique_ptr<T> read(std::istream& stream, const C& context) = 0;
	};
}