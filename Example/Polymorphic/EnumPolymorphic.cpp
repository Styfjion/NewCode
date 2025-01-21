#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

using Cost = int32_t;
using Penalty = int32_t;
constexpr int32_t CPU_INITIAL_COST = 50;
constexpr int32_t CPU_COST_THRESHOLD = 2;
constexpr int32_t CPU_MULTIPLIER = 10;
using MB = int32_t;

class CpuResource
{
public:
    static Cost ComputeCost(const int32_t time)
    {
        int32_t cost = CPU_INITIAL_COST;
        if (time > CPU_COST_THRESHOLD)
        {
            cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER;
        }
        return cost;
    }
};

constexpr int32_t BASIC_MEM_QUOTA = 1024;
constexpr int32_t MEM_INITIAL_COST = 30;
constexpr int32_t MEM_MULTIPLIER = 2;
using MB = int32_t;

class MemoryResource
{
public:
    explicit MemoryResource(const MB capacity): m_capacity(capacity)
    {
    }


    [[nodiscard]] Cost ComputeCost(const int32_t time) const
    {
        int32_t cost = MEM_INITIAL_COST;
        if (m_capacity > BASIC_MEM_QUOTA)
        {
            cost += time * (m_capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
        }
        return cost;
    }

private:
    MB m_capacity;
};

constexpr int32_t STORAGE_INITIAL_COST = 20;
constexpr int32_t STORAGE_COST_THRESHOLD = 3;
constexpr double STORAGE_MULTIPLIER = 1.5;
using GB = int32_t;

class StorageResource
{
public:
    explicit StorageResource(const GB capacity): m_capacity(capacity)
    {
    }

    [[nodiscard]] Cost ComputeCost(const int32_t time) const
    {
        int32_t cost = STORAGE_INITIAL_COST;
        if (time > STORAGE_COST_THRESHOLD)
        {
            cost += static_cast<int32_t>((time - STORAGE_COST_THRESHOLD) * m_capacity * STORAGE_MULTIPLIER);
        }
        return cost;
    }

    static Penalty ComputePenalty(const int32_t time)
    {
        return time > 12 ? 1 : 0;
    }

private:
    GB m_capacity;
};

using Resource = std::variant<CpuResource, MemoryResource, StorageResource>;

Cost ComputeCost(const Resource& resource, const int32_t time)
{
    return std::visit([&](const auto& inner)
    {
        return inner.ComputeCost(time);
    }, resource);
}

Penalty ComputePenalty(const Resource& resource, const int32_t time)
{
    return std::visit([&]<typename T>(const T& inner)
    {
        if constexpr (std::is_same_v<T, StorageResource>)
        {
            return inner.ComputePenalty(time);
        }
        else
        {
            return 0;
        }
    }, resource);
}


int main()
{
    const auto cpu = std::make_unique<CpuResource>();
    const auto memory = std::make_unique<MemoryResource>(2048);
    const auto storage = std::make_unique<StorageResource>(100);
    std::cout << "cpu cost is " << ComputeCost(*cpu, 3) << std::endl;
    std::cout << "mem cost is " << ComputeCost(*memory, 2) << std::endl;
    std::cout << "storage cost is " << ComputeCost(*storage, 14) << std::endl;
    std::cout << "cpu penalty is " << ComputePenalty(*cpu, 3) << std::endl;
    std::cout << "mem penalty is " << ComputePenalty(*memory, 2) << std::endl;
    std::cout << "storage penalty is " << ComputePenalty(*storage, 14) << std::endl;
}
