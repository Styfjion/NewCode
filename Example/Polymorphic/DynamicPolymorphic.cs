namespace ConsoleApp1;

internal interface IResource
{
    int ComputeCost(int time);

    int ComputePenalty(int time)
    {
        return 0;
    }
}

internal abstract class Resource(int capacity)
{
    protected readonly int Capacity = capacity;
}

internal class CpuResource(int capacity) : Resource(capacity), IResource
{
    private const int CpuInitialCost = 50;
    private const int CpuCostThreshold = 2;
    private const int CpuMultiplier = 10;


    public int ComputeCost(int time)
    {
        var cost = CpuInitialCost;
        if (time > CpuCostThreshold)
        {
            cost += (time - CpuCostThreshold) * CpuMultiplier;
        }

        return cost;
    }
}

internal class MemoryResource(int capacity) : Resource(capacity), IResource
{
    private const int BasicMemQuota = 1024;
    private const int MemInitialCost = 30;
    private const int MemMultiplier = 2;

    public int ComputeCost(int time)
    {
        var cost = MemInitialCost;
        if (Capacity > BasicMemQuota)
        {
            cost += time * (Capacity - BasicMemQuota) * MemMultiplier;
        }

        return cost;
    }
}

internal class StorageReSource(int capacity) : Resource(capacity), IResource
{
    private const int StorageInitialCost = 20;
    private const int StorageCostThreshold = 3;
    private const double StorageMultiplier = 1.5;

    public int ComputeCost(int time)
    {
        var cost = StorageInitialCost;
        if (time > StorageCostThreshold)
        {
            cost += (int)((time - StorageCostThreshold) * Capacity * StorageMultiplier);
        }

        return cost;
    }

    public int ComputePenalty(int time)
    {
        return time > 12 ? 1 : 0;
    }
}

internal enum ResourceType
{
    Cpu,
    Memory,
    Storage
}

internal static class ResourceFactory
{
    public static IResource Create(ResourceType type, int capacity)
    {
        return type switch
        {
            ResourceType.Cpu => new CpuResource(capacity),
            ResourceType.Memory => new MemoryResource(capacity),
            ResourceType.Storage => new StorageReSource(capacity),
            _ => throw new ArgumentOutOfRangeException(nameof(type), type, null)
        };
    }
}

public static class DynamicPolymorphic
{
    public static void Main(string[] args)
    {
        var cpu = ResourceFactory.Create(ResourceType.Cpu, 0);
        var mem = ResourceFactory.Create(ResourceType.Memory, 2048);
        var storage = ResourceFactory.Create(ResourceType.Storage, 100);
        Console.WriteLine("cpu cost is " + cpu.ComputeCost(3));
        Console.WriteLine("mem cost is " + mem.ComputeCost(2));
        Console.WriteLine("storage cost is " + storage.ComputeCost(14));
        Console.WriteLine("cpu penalty is " + cpu.ComputePenalty(3));
        Console.WriteLine("mem penalty is " + mem.ComputePenalty(2));
        Console.WriteLine("storage penalty is " + storage.ComputePenalty(14));
    }
}