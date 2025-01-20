package com.example.practise;

interface ResourceTrait {
    int computeCost(int time);

    default int computePenalty(int _time) {
        return 0;
    }
}

abstract class Resource {
    protected final int capacity;

    Resource(int capacity) {
        this.capacity = capacity;
    }
}

class CpuResource extends Resource implements ResourceTrait {

    private static final int CPU_INITIAL_COST = 50;
    private static final int CPU_COST_THRESHOLD = 2;
    private static final int CPU_MULTIPLIER = 10;

    CpuResource(int capacity) {
        super(capacity);
    }

    @Override
    public int computeCost(int time) {
        var cost = CPU_INITIAL_COST;
        if (time > CPU_COST_THRESHOLD) {
            cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER;
        }
        return cost;
    }
}

class MemoryResource extends Resource implements ResourceTrait {
    private static final int BASIC_MEM_QUOTA = 1024;
    private static final int MEM_INITIAL_COST = 30;
    private static final int MEM_MULTIPLIER = 2;

    MemoryResource(int capacity) {
        super(capacity);
    }

    @Override
    public int computeCost(int time) {
        int cost = MEM_INITIAL_COST;
        if (capacity > BASIC_MEM_QUOTA) {
            cost += time * (capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
        }
        return cost;
    }
}

class StorageReSource extends Resource implements ResourceTrait {
    private static final int STORAGE_INITIAL_COST = 20;
    private static final int STORAGE_COST_THRESHOLD = 3;
    private static final double STORAGE_MULTIPLIER = 1.5;

    StorageReSource(int capacity) {
        super(capacity);
    }

    @Override
    public int computeCost(int time) {
        int cost = STORAGE_INITIAL_COST;
        if (time > STORAGE_COST_THRESHOLD) {
            cost += (int) ((time - STORAGE_COST_THRESHOLD) * capacity * STORAGE_MULTIPLIER);
        }
        return cost;
    }

    @Override
    public int computePenalty(int time) {
        return time > 12 ? 1 : 0;
    }
}

enum ResourceType {
    Cpu, Memory, Storage
}

class ResourceFactory {
    static ResourceTrait create(ResourceType type, int capacity) {
        ResourceTrait trait = null;
        switch (type) {
            case Cpu -> trait = new CpuResource(capacity);
            case Memory -> trait = new MemoryResource(capacity);
            case Storage -> trait = new StorageReSource(capacity);
        }
        return trait;
    }
}

public class DynamicPolymorphic {
    public static void main(String[] args) {
        var cpu = ResourceFactory.create(ResourceType.Cpu, 0);
        var mem = ResourceFactory.create(ResourceType.Memory, 2048);
        var storage = ResourceFactory.create(ResourceType.Storage, 100);
        System.out.println("cpu cost is " + cpu.computeCost(3));
        System.out.println("mem cost is " + mem.computeCost(2));
        System.out.println("storage cost is " + storage.computeCost(14));
        System.out.println("cpu penalty is " + cpu.computePenalty(3));
        System.out.println("mem penalty is " + mem.computePenalty(2));
        System.out.println("storage penalty is " + storage.computePenalty(14));
    }
}
