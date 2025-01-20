use std::marker::PhantomData;

pub(crate) type Cost = i32;
pub(crate) type Penalty = i32;
pub(crate) trait Resource {
    fn compute_cost(&self, time: i32) -> Cost;
    fn compute_penalty(&self, _time: i32) -> Penalty {
        0
    }
}

pub struct ResourcesEntry<T> {
    capacity: i32,
    _type: PhantomData<T>,
}

impl<T> ResourcesEntry<T> {
    pub const fn new(capacity: i32) -> Self {
        Self {
            capacity,
            _type: PhantomData,
        }
    }
}

struct CpuResource;
struct MemoryResource;
struct StorageResource;
const CPU_INITIAL_COST: i32 = 50;
const CPU_COST_THRESHOLD: i32 = 2;
const CPU_MULTIPLIER: i32 = 10;

impl Resource for ResourcesEntry<CpuResource> {
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

impl Resource for ResourcesEntry<MemoryResource> {
    fn compute_cost(&self, time: i32) -> Cost {
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

impl Resource for ResourcesEntry<StorageResource> {
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
pub(crate) fn create_resource<T>(capacity: i32) -> impl Resource
where
    ResourcesEntry<T>: Resource,
{
    ResourcesEntry::<T>::new(capacity)
}

fn main() {
    let cpu = create_resource::<CpuResource>(0);
    let mem = create_resource::<MemoryResource>(2048);
    let storage = create_resource::<StorageResource>(100);
    println!("cpu cost is {}", cpu.compute_cost(3));
    println!("mem cost is {}", mem.compute_cost(2));
    println!("storage cost is {}", storage.compute_cost(14));
    println!("cpu penalty is {}", cpu.compute_penalty(3));
    println!("mem penalty is {}", mem.compute_penalty(2));
    println!("storage penalty is {}", storage.compute_penalty(14));
}
