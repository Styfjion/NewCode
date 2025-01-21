type Cost = number;
type Penalty = number;

abstract class Resource {
  constructor(protected capacity: number) {
    this.capacity = capacity;
  }

  abstract computeCost(time: number): Cost;

  computePenalty(_time: number): Penalty {
    return 0;
  }
}

const CPU_INITIAL_COST = 50;
const CPU_COST_THRESHOLD = 2;
const CPU_MULTIPLIER = 10;

class CpuResource extends Resource {
  computeCost(time: number): Cost {
    let cost = CPU_INITIAL_COST;
    if (time > CPU_COST_THRESHOLD) {
      cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER;
    }
    return cost;
  }
}

const BASIC_MEM_QUOTA = 1024;
const MEM_INITIAL_COST = 30;
const MEM_MULTIPLIER = 2;

class MemoryResource extends Resource {
  computeCost(time: number): Cost {
    let cost = MEM_INITIAL_COST;
    if (this.capacity > BASIC_MEM_QUOTA) {
      cost += time * (this.capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
    }
    return cost;
  }
}

const STORAGE_INITIAL_COST = 20;
const STORAGE_COST_THRESHOLD = 3;
const STORAGE_MULTIPLIER = 1.5;

class StorageResource extends Resource {
  computeCost(time: number): Cost {
    let cost = STORAGE_INITIAL_COST;
    if (time > STORAGE_COST_THRESHOLD) {
      cost +=
        (time - STORAGE_COST_THRESHOLD) * this.capacity * STORAGE_MULTIPLIER;
    }
    return Math.round(cost);
  }

  computePenalty(time: number): Penalty {
    return time > 12 ? 1 : 0;
  }
}

enum ResourcesType {
  Cpu,
  Memory,
  Storage,
}

function createResource(
  resourceType: ResourcesType,
  capacity: number,
): Resource {
  switch (resourceType) {
    case ResourcesType.Cpu:
      return new CpuResource(capacity);
    case ResourcesType.Memory:
      return new MemoryResource(capacity);
    case ResourcesType.Storage:
      return new StorageResource(capacity);
  }
}

const cpu = createResource(ResourcesType.Cpu, 0);
const memory = createResource(ResourcesType.Memory, 2048);
const storage = createResource(ResourcesType.Storage, 100);
console.log(`cpu cost is ${cpu.computeCost(3)}`);
console.log(`mem cost is ${memory.computeCost(2)}`);
console.log(`storage cost is ${storage.computeCost(14)}`);
console.log(`cpu penalty is ${cpu.computePenalty(3)}`);
console.log(`mem penalty is ${memory.computePenalty(2)}`);
console.log(`storage penalty is ${storage.computePenalty(14)}`);
