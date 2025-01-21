from abc import ABC, abstractmethod
from enum import Enum

Cost = int
Penalty = int


class Resource(ABC):
    def __init__(self, capacity: int):
        self.capacity = capacity

    @abstractmethod
    def compute_cost(self, time: int) -> Cost:
        pass

    @staticmethod
    def compute_penalty(_: int) -> Penalty:
        return 0


CPU_INITIAL_COST = 50
CPU_COST_THRESHOLD = 2
CPU_MULTIPLIER = 10


class CpuResource(Resource):
    def compute_cost(self, time: int) -> Cost:
        cost = CPU_INITIAL_COST
        if time > CPU_COST_THRESHOLD:
            cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER
        return cost


BASIC_MEM_QUOTA = 1024
MEM_INITIAL_COST = 30
MEM_MULTIPLIER = 2
MB = int


class MemoryResource(Resource):
    def compute_cost(self, time: int) -> Cost:
        cost = MEM_INITIAL_COST
        if self.capacity > BASIC_MEM_QUOTA:
            cost += time * (self.capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER
        return cost


STORAGE_INITIAL_COST = 20
STORAGE_COST_THRESHOLD = 3
STORAGE_MULTIPLIER = 1.5
GB = int


class StorageResource(Resource):
    def compute_cost(self, time: int) -> Cost:
        cost = STORAGE_INITIAL_COST
        if time > STORAGE_COST_THRESHOLD:
            cost += (time - STORAGE_COST_THRESHOLD) * self.capacity * STORAGE_MULTIPLIER
        return Cost(cost)

    @staticmethod
    def compute_penalty(time: int) -> Penalty:
        return 1 if time > 12 else 0


class ResourceType(Enum):
    CPU = 0
    Memory = 1
    Storage = 2


def create_resource(resource_type: ResourceType, capacity: int) -> Resource:
    match resource_type:
        case ResourceType.CPU:
            return CpuResource(capacity)
        case ResourceType.Memory:
            return MemoryResource(capacity)
        case ResourceType.Storage:
            return StorageResource(capacity)


if __name__ == '__main__':
    cpu = create_resource(ResourceType.CPU, 0)
    mem = create_resource(ResourceType.Memory, 2048)
    storage = create_resource(ResourceType.Storage, 100)
    print(f'cpu cost is {cpu.compute_cost(3)}')
    print(f'mem cost is {mem.compute_cost(2)}')
    print(f'storage cost is {storage.compute_cost(14)}')
    print(f'cpu penalty is {cpu.compute_penalty(3)}')
    print(f'mem penalty is {mem.compute_penalty(2)}')
    print(f'storage penalty is {storage.compute_penalty(14)}')
