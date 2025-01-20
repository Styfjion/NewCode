#include <cstdint>
#include <iostream>
#include <memory>
using Cost = int32_t;
using Penalty = int32_t;

class Resource
{
public:
    virtual ~Resource() = default;

    explicit Resource(const int32_t capacity): m_capacity(capacity)
    {
    }

    virtual Cost ComputeCost(int32_t time) = 0;

    virtual Penalty ComputePenalty(int32_t time)
    {
        return 0;
    }

protected:
    int32_t m_capacity;
};

constexpr int32_t CPU_INITIAL_COST = 50;
constexpr int32_t CPU_COST_THRESHOLD = 2;
constexpr int32_t CPU_MULTIPLIER = 10;

class CpuResource : public Resource
{
public:
    explicit CpuResource(const int32_t capacity): Resource(capacity)
    {
    }

    ~CpuResource() override = default;

    Cost ComputeCost(const int32_t time) override
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

class MemoryResource : public Resource
{
public:
    explicit MemoryResource(const MB capacity): Resource(capacity)
    {
    }

    ~MemoryResource() override = default;

    Cost ComputeCost(const int32_t time) override
    {
        int32_t cost = MEM_INITIAL_COST;
        if (m_capacity > BASIC_MEM_QUOTA)
        {
            cost += time * (m_capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
        }
        return cost;
    }
};

constexpr int32_t STORAGE_INITIAL_COST = 20;
constexpr int32_t STORAGE_COST_THRESHOLD = 3;
constexpr double STORAGE_MULTIPLIER = 1.5;
using GB = int32_t;

class StorageResource : public Resource
{
public:
    explicit StorageResource(const GB capacity): Resource(capacity)
    {
    }

    ~StorageResource() override = default;

    Cost ComputeCost(const int32_t time) override
    {
        int32_t cost = STORAGE_INITIAL_COST;
        if (time > STORAGE_COST_THRESHOLD)
        {
            cost += static_cast<int32_t>((time - STORAGE_COST_THRESHOLD) * m_capacity * STORAGE_MULTIPLIER);
        }
        return cost;
    }

    Penalty ComputePenalty(const int32_t time) override
    {
        return time > 12 ? 1 : 0;
    }
};

enum class ResourceType
{
    Cpu,
    Memory,
    Storage
};

std::unique_ptr<Resource> CreateResource(const ResourceType type, int32_t capacity)
{
    switch (type)
    {
    case ResourceType::Cpu:
        return std::make_unique<CpuResource>(capacity);
    case ResourceType::Memory:
        return std::make_unique<MemoryResource>(capacity);
    case ResourceType::Storage:
        return std::make_unique<StorageResource>(capacity);
    }
    return nullptr;
} // 动态工厂类方法

template <typename T>
concept ReseourceTrait = std::derived_from<T, Resource>;

template <ReseourceTrait T>
std::unique_ptr<T> CreateResource(int32_t capacity)
{
    return std::make_unique<T>(capacity);
} // 静态模板方法


int main()
{
    const auto cpu = CreateResource(ResourceType::Cpu, 0);
    const auto memory = CreateResource(ResourceType::Memory, 2048);
    const auto storage = CreateResource(ResourceType::Storage, 100);
    std::cout << "cpu cost is " << cpu->ComputeCost(3) << std::endl;
    std::cout << "mem cost is " << memory->ComputeCost(2) << std::endl;
    std::cout << "storage cost is " << storage->ComputeCost(14) << std::endl;
    std::cout << "cpu penalty is " << cpu->ComputePenalty(3) << std::endl;
    std::cout << "mem penalty is " << memory->ComputePenalty(2) << std::endl;
    std::cout << "storage penalty is " << storage->ComputePenalty(14) << std::endl;
    std::cout << "------------------------------" << std::endl;
    const auto cpu2 = CreateResource<CpuResource>(0);
    const auto memory2 = CreateResource<MemoryResource>(2048);
    const auto storage2 = CreateResource<StorageResource>(100);
    std::cout << "cpu cost is " << cpu2->ComputeCost(3) << std::endl;
    std::cout << "mem cost is " << memory2->ComputeCost(2) << std::endl;
    std::cout << "storage cost is " << storage2->ComputeCost(14) << std::endl;
    std::cout << "cpu penalty is " << cpu2->ComputePenalty(3) << std::endl;
    std::cout << "mem penalty is " << memory2->ComputePenalty(2) << std::endl;
    std::cout << "storage penalty is " << storage2->ComputePenalty(14) << std::endl;
}
