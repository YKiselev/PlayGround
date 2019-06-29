#include "pch.h"
#include <shared_mutex>
#include <unordered_map>
#include <array>
#include <PersistedConfiguration.h>

using spi::PersistedConfiguration;
using spi::ConfigValue;
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

template <typename V>
struct S
{
	S()
	{
	}
	S(V src)
	{
		set(src);
	}

	inline void set(V src)
	{
		value.store(src, std::memory_order::memory_order_release);
	}

	inline V get() 
	{
		return value.load(std::memory_order::memory_order_acquire);
	}
private:
	std::atomic<V> value;
};

TEST(SimpleValue, float_getString)
{
	S<float> f;
	S<int> i;
	S s = &f;

	auto a = s.get();

	//std::atomic<S> s;

	//SimpleValue<float> value;
	//value.fromBool(true);
	//EXPECT_TRUE(value.asBool());
	//value.fromFloat(3.14f);
	//EXPECT_FLOAT_EQ(3.14f, value.asFloat());
	//std::atomic<float> fa;
}

TEST(PersistedConfiguration, getString)
{

}