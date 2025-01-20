package main

import "fmt"

type Cost int32
type Penalty int32

type Resource interface {
	ComputeCost(time int32) Cost
	ComputePenalty(time int32) Penalty
}

type DefaultComputePenalty struct{}

func (d DefaultComputePenalty) ComputePenalty(_ int32) Penalty {
	return 0
}

type CpuResource struct {
	DefaultComputePenalty
}

const (
	CpuInitialCost   int32 = 50
	CpuCostThreshold int32 = 2
	CpuMultiplier    int32 = 10
)

func (c CpuResource) ComputeCost(time int32) Cost {
	cost := CpuInitialCost
	if time > CpuCostThreshold {
		cost += (time - CpuCostThreshold) * CpuMultiplier
	}
	return Cost(cost)
}

type MB int32
type MemoryResource struct {
	DefaultComputePenalty
	capacity MB
}

const (
	BasicMemQuota  MB    = 1024
	MemInitialCost int32 = 30
	MemMultiplier  int32 = 2
)

func (m MemoryResource) ComputeCost(time int32) Cost {
	cost := MemInitialCost
	if m.capacity > BasicMemQuota {
		cost += time * int32(m.capacity-BasicMemQuota) * MemMultiplier
	}
	return Cost(cost)
}

type GB int32
type StorageResource struct {
	capacity GB
}

const (
	StorageInitialCost   int32   = 20
	StorageCostThreshold int32   = 3
	StorageMultiplier    float64 = 1.5
)

func (s StorageResource) ComputeCost(time int32) Cost {
	cost := StorageInitialCost
	if time > StorageCostThreshold {
		cost += int32(float64(time-StorageCostThreshold) * float64(s.capacity) * StorageMultiplier)
	}
	return Cost(cost)
}

func (s StorageResource) ComputePenalty(time int32) Penalty {
	if time > 12 {
		return 1
	}
	return 0
}

type ResourceType uint8

const (
	Cpu ResourceType = iota
	Memory
	Storage
)

func createResource(resourceType ResourceType, capacity int32) Resource {
	var resource Resource
	switch resourceType {
	case Cpu:
		resource = CpuResource{DefaultComputePenalty{}}
		return resource
	case Memory:
		resource = MemoryResource{DefaultComputePenalty{}, MB(capacity)}
		return resource
	case Storage:
		resource = StorageResource{GB(capacity)}
		return resource
	}
	return nil
}

func main() {
	cpu := createResource(Cpu, 0)
	memory := createResource(Memory, 2048)
	storage := createResource(Storage, 100)
	fmt.Println("cpu cost is ", cpu.ComputeCost(3))
	fmt.Println("mem cost is ", memory.ComputeCost(2))
	fmt.Println("storage cost is ", storage.ComputeCost(14))
	fmt.Println("cpu penalty is ", cpu.ComputePenalty(3))
	fmt.Println("mem penalty is ", memory.ComputePenalty(2))
	fmt.Println("storage penalty is ", storage.ComputePenalty(14))
}
