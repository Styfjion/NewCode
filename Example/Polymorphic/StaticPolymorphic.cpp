#include <cstdint>
#include <iostream>
#include <memory>
//
// Created by y00564656 on 25-1-20.
//
using Cost = int32_t;
using Penalty = int32_t;

template <typename>
class Resource
{
public:
    ~Resource() = default;

    explicit Resource(const int32_t capacity): m_capacity(capacity)
    {
    }

    Cost ComputeCost(int32_t time);

    static Penalty ComputePenalty(int32_t time);

protected:
    int32_t m_capacity;
};

constexpr int32_t CPU_INITIAL_COST = 50;
constexpr int32_t CPU_COST_THRESHOLD = 2;
constexpr int32_t CPU_MULTIPLIER = 10;

struct CpuResource
{
}; // 类标签

template <>
Cost Resource<CpuResource>::ComputeCost(const int32_t time)
{
    int32_t cost = CPU_INITIAL_COST;
    if (time > CPU_COST_THRESHOLD)
    {
        cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER;
    }
    return cost;
}


constexpr int32_t BASIC_MEM_QUOTA = 1024;
constexpr int32_t MEM_INITIAL_COST = 30;
constexpr int32_t MEM_MULTIPLIER = 2;

struct MemoryResource
{
};

template <>
Cost Resource<MemoryResource>::ComputeCost(const int32_t time)
{
    int32_t cost = MEM_INITIAL_COST;
    if (m_capacity > BASIC_MEM_QUOTA)
    {
        cost += time * (m_capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
    }
    return cost;
}

constexpr int32_t STORAGE_INITIAL_COST = 20;
constexpr int32_t STORAGE_COST_THRESHOLD = 3;
constexpr double STORAGE_MULTIPLIER = 1.5;

struct StorageResource
{
};

template <>
Cost Resource<StorageResource>::ComputeCost(const int32_t time)
{
    int32_t cost = STORAGE_INITIAL_COST;
    if (time > STORAGE_COST_THRESHOLD)
    {
        cost += static_cast<int32_t>((time - STORAGE_COST_THRESHOLD) * m_capacity * STORAGE_MULTIPLIER);
    }
    return cost;
}

template <>
Penalty Resource<StorageResource>::ComputePenalty(const int32_t time)
{
    return time > 12 ? 1 : 0;
}

template<typename T>
Penalty Resource<T>::ComputePenalty(const int32_t time)
{
    return 0;
}

enum class ResourceType
{
    Cpu,
    Memory,
    Storage
};

template <typename T>
std::unique_ptr<Resource<T>> CreateResource(int32_t capacity)
{
    return std::make_unique<Resource<T>>(capacity);
} //静态模板方法创建模板

int main()
{
    const auto cpu = CreateResource<CpuResource>(0);
    const auto memory = CreateResource<MemoryResource>(2048);
    const auto storage = CreateResource<StorageResource>(100);
    std::cout << "cpu cost is " << cpu->ComputeCost(3) << std::endl;
    std::cout << "mem cost is " << memory->ComputeCost(2) << std::endl;
    std::cout << "storage cost is " << storage->ComputeCost(14) << std::endl;
    std::cout << "cpu penalty is " << Resource<CpuResource>::ComputePenalty(3) << std::endl;
    std::cout << "mem penalty is " << Resource<MemoryResource>::ComputePenalty(2) << std::endl;
    std::cout << "storage penalty is " << Resource<StorageResource>::ComputePenalty(14) << std::endl;
}
