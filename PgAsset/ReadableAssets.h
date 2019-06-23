#pragma once

#include <string>
#include <memory>
#include <any>
#include "ReadableAsset.h"
#include "Recipe.h"

namespace assets
{
	template <typename K>
	class ReadableAssets
	{
	public:
		virtual ~ReadableAssets() = 0;

		template <typename T, typename C>
		inline std::shared_ptr<T>> resolve(const std::string& resource, const AssetKey<T, K, C>& key)
		{
			const std::unique_ptr<ReadableAsset<T, C>> readableAsset = resolve(resource, key);
			if (readableAsset != nullptr) {

			}
		}

		inline std::shared_ptr<ReadableAsset<K, T, C>> resolve(const AssetKey& key)
		{
			return resolve("", key);
		}

	protected:
		virtual std::unique_ptr<ReadableAsset<T, C>> resolve(const std::string& resource, const K& key) = 0;
	};
}
