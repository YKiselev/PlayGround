#include "pch.h"
#include <shared_mutex>
#include <unordered_map>
#include <array>
#include <iostream>
#include <string>
#include <cstdlib>
#include <charconv>
#include <string_view>
#include <atomic>
#include <type_traits>
#include <PersistedConfiguration.h>
/*
using spi::PersistedConfiguration;
using spi::SimpleValue;

class MyPersistedConfiguration : public PersistedConfiguration
{
public:
	virtual void persist(const std::string& name) const override
	{
	}

	virtual void load(const std::string& name) override
	{
	}

	virtual void loadAll(const std::string& name) override
	{
	}

protected:
	virtual const ConfigValue* findNode(const std::string& name) const override
	{
		//std::shared_lock lock(mutex);
		//std::string k = name;
		//auto it = values.find(name);
		//if (it != values.end())
		//{
		//	return  &(it->second);
		//}
		return nullptr;
	}

private:
	mutable std::shared_mutex mutex;
	//std::unordered_map<std::string, ConfigValue> values;
};
*/

using spi::Value;

template <typename V>
struct Converter
{
	static std::string toString(V& value)
	{
		std::array<char, 48> buf;
		auto [p, ec] = std::to_chars(buf.data(), buf.data() + buf.size(), value.get());
		if (ec == std::errc())
		{
			return std::string(buf.data(), p - buf.data());
		}
		else
		{
			return "value_too_long";
		}

	}

	static void fromString(const std::string& src, V& value)
	{
		if (src.empty())
		{
			value.set({});
		}
		else
		{
			V::value_type result;
			auto ec = std::from_chars(src.data(), src.data() + src.size(), result).ec;
			if (ec == std::errc())
			{
				value.set(result);
			}
			else
			{
				value.set({});
			}
		}
	}
};

template <>
struct Converter<Value<std::string>>
{
	static std::string toString(Value<std::string>& value)
	{
		return value.get();
	}

	static void fromString(const std::string& src, Value<std::string>& value)
	{
		value.set(src);
	}
};


template <typename V, typename Converter = Converter<V>>
struct Var
{
	Var(V& src) : value{ src }
	{
	}

	std::string toString() const
	{
		return Converter::toString(value);
	}

	void fromString(const std::string& src)
	{
		Converter::fromString(src, value);
	}
private:
	V& value;
};

TEST(AtomicValue, float_getString)
{
	Value<int> vint{ 5 };
	Value<float> vfloat{ 3.14f };
	Value<std::string> vstr{ "test1" };

	//Value<int> vint2{ vint };
	//Value<float> vfloat2{ vfloat };
	//Value<std::string> vstr2{ vstr };

	//Value<int> vint3{ vfloat };
	//Value<float> vfloat3{ vint };
	//Value<std::string> vstr3{ vint };

	//Value<int> vint4 = vint;
	//Value<float> vfloat4 = vfloat;
	//Value<std::string> vstr4 = vstr;

	std::cout << "i=" << vint.get() << ", f=" << vfloat.get() << ", str=" << vstr.get() << std::endl;
	std::cout << "i=" << typeid(decltype(vint)::wrapper_type).name() << ", f=" << typeid(decltype(vfloat)::wrapper_type).name() << ", str=" << typeid(decltype(vstr)::wrapper_type).name() << std::endl;

	Var v1{ vint };
	Var v2{ vfloat };
	Var v3{ vstr };

	v1.fromString("123");
	v2.fromString("33.45");
	v3.fromString("black fox");

	std::cout << "i=" << vint.get() << ", f=" << vfloat.get() << ", str=" << vstr.get() << std::endl;

	std::cout << "i=" << v1.toString() << ", f=" << v2.toString() << ", str=" << v3.toString() << std::endl;

	//Value<int> vint4 = std::move(vint);
	//Value<float> vfloat4 = std::move(vfloat);
	//Value<std::string> vstr4 = std::move(vstr);
}

struct Square
{
	constexpr int operator ()(int v)
	{
		return v * v;
	}
};

struct Cube
{
	constexpr int operator ()(int v)
	{
		return v * v * v;
	}
};

template<typename T>
constexpr bool is_cubable()
{
	return sizeof(T) <= 2;
}

template <typename T>
constexpr T squareOrCube(T value)
{
	return std::conditional<is_cubable<T>(), Square, Cube>::type{}(value);
}

template <unsigned N, typename...Cases>
struct select;

template <unsigned N, typename T, typename...Cases>
struct select<N, T, Cases...> : select<N - 1, Cases...>
{
};

template <typename T, typename...Cases>
struct select<0, T, Cases...>
{
	using type = T;
};

template <unsigned N, typename...Cases>
using Select = typename select<N, Cases...>::type;

TEST(PersistedConfiguration, getString)
{
	int x = is_cubable<char>() ? Square{}(99) : Cube{}(99);
	int y = is_cubable<int>() ? Square{}(99) : Cube{}(99);

	int z = std::conditional<is_cubable<char>(), Square, Cube>::type{}(99);
	int w = std::conditional<is_cubable<long>(), Square, Cube>::type{}(99);

	constexpr auto z2 = squareOrCube<short>(99);
	constexpr auto z3 = squareOrCube<long>(99);

	std::cout << "x=" << x << ", y=" << y << std::endl;
	std::cout << "z2=" << z2 << ", z3=" << z3 << std::endl;

	int a = Select<0, Square, Cube>{}(99);
	int b = Select<1, Square, Cube>{}(99);

	std::cout << "a=" << a << ", b=" << b << std::endl;
}