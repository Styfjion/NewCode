pub(crate) type Cost = i32;
pub(crate) type Penalty = i32;
pub(crate) trait Resource {
    fn compute_cost(&self, time: i32) -> Cost;
    fn compute_penalty(&self, _time: i32) -> Penalty {
        0
    }
}

const CPU_INITIAL_COST: i32 = 50;
const CPU_COST_THRESHOLD: i32 = 2;
const CPU_MULTIPLIER: i32 = 10;
pub(crate) struct CpuResource;
impl Resource for CpuResource {
    fn compute_cost(&self, time: i32) -> Cost {
        let mut cost = CPU_INITIAL_COST;
        if time > CPU_COST_THRESHOLD {
            cost += (time - CPU_COST_THRESHOLD) * CPU_MULTIPLIER;
        }
        cost
    }
}

const BASIC_MEM_QUOTA: i32 = 1024;
const MEM_INITIAL_COST: i32 = 30;
const MEM_MULTIPLIER: i32 = 2;
type MB = i32;
pub(crate) struct MemoryResource {
    capacity: MB,
}

impl MemoryResource {
    pub(crate) fn new(capacity: MB) -> Self {
        Self { capacity }
    }
}

impl Resource for MemoryResource {
    fn compute_cost(&self, time: MB) -> Cost {
        let mut cost = MEM_INITIAL_COST;
        if self.capacity > BASIC_MEM_QUOTA {
            cost += time * (self.capacity - BASIC_MEM_QUOTA) * MEM_MULTIPLIER;
        }
        cost
    }
}

const STORAGE_INITIAL_COST: i32 = 20;
const STORAGE_COST_THRESHOLD: i32 = 3;
const STORAGE_MULTIPLIER: f64 = 1.5;
type GB = i32;
pub(crate) struct StorageResource {
    capacity: GB,
}

impl StorageResource {
    pub(crate) fn new(capacity: GB) -> Self {
        Self { capacity }
    }
}

impl Resource for StorageResource {
    fn compute_cost(&self, time: i32) -> Cost {
        let mut cost = STORAGE_INITIAL_COST;
        if time > STORAGE_COST_THRESHOLD {
            cost += ((time - STORAGE_COST_THRESHOLD) as f64
                * self.capacity as f64
                * STORAGE_MULTIPLIER) as i32;
        }
        cost
    }

    fn compute_penalty(&self, time: i32) -> Penalty {
        if time > 12 {
            1
        } else {
            0
        }
    }
}

#[derive(Copy, Clone)]
pub enum ResourceType {
    Cpu,
    Memory,
    Storage,
}
pub(crate) fn create_resource(
    resource_type: ResourceType,
    capacity: i32,
) -> Box<dyn Resource + Send + Sync> {
    match resource_type {
        ResourceType::Cpu => Box::new(CpuResource),
        ResourceType::Memory => Box::new(MemoryResource::new(capacity)),
        ResourceType::Storage => Box::new(StorageResource::new(capacity)),
    }
}

fn main() {
    let cpu = create_resource(ResourceType::Cpu, 0);
    let mem = create_resource(ResourceType::Memory, 2048);
    let storage = create_resource(ResourceType::Storage, 100);
    println!("cpu cost is {}", cpu.compute_cost(3));
    println!("mem cost is {}", mem.compute_cost(2));
    println!("storage cost is {}", storage.compute_cost(14));
    println!("cpu penalty is {}", cpu.compute_penalty(3));
    println!("mem penalty is {}", mem.compute_penalty(2));
    println!("storage penalty is {}", storage.compute_penalty(14));
}
