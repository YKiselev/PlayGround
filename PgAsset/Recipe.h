#pragma once

namespace assets
{
	template <typename T, typename C>
	class Recipe
	{
	public:
		using value_type = T;

		Recipe(const C& context) : context{ context } {}

		const C& context;
	};


	template <typename T, typename K, typename C>
	class AssetKey final : public Recipe<T, C>
	{
	public:
		AssetKey(const K& key, const C& context) : Recipe(context), key{ key } {}

		const K key;
	};
}