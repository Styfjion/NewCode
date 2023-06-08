use std::sync::atomic::{AtomicI32, Ordering};
use std::sync::Mutex;

#[derive(Default)]
struct Counter {
    cur_value: Mutex<i32>,
    prime: i32
}

impl Counter {
    fn create_counter<'b: 'a, 'a>(&'b mut self, init: i32) -> Vec<Box<dyn FnMut() -> i32 + 'a>> {
        //闭包里捕获了类变量，必须进行生命周期标注，返回值的生命周期不长于类的生命周期
        self.prime = init;
        {
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value = init;
        }

        let add = ||{
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value += 1;
            *cur_value
        };

        let dec = ||{
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value -= 1;
            *cur_value
        };

        let reset = ||{
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value = self.prime;
            *cur_value
        };
        vec![Box::new(add), Box::new(dec), Box::new(reset)]
    }
}

fn create_counter(init: i32) -> Vec<Box<fn() -> i32>> {
    static CUR_VALUE: AtomicI32 = AtomicI32::new(0);
    static PRIME: AtomicI32 = AtomicI32::new(0);
    CUR_VALUE.store(init, Ordering::Relaxed);
    PRIME.store(init, Ordering::Relaxed);

    let add = ||{
        let cur_value = CUR_VALUE.fetch_add(1, Ordering::Relaxed);
        cur_value + 1
    };

    let dec = ||{
        let cur_value = CUR_VALUE.fetch_sub(1, Ordering::Relaxed);
        cur_value - 1
    };

    let reset = ||{
        let prime = PRIME.load(Ordering::Relaxed);
        CUR_VALUE.store(prime, Ordering::Relaxed);
        prime
    };

    vec![Box::new(add), Box::new(dec), Box::new(reset)]
}

fn main() {
    let mut sol = Counter::default();
    let mut counters = sol.create_counter(5);
    println!("{}", counters[0].as_mut()());
    println!("{}", counters[2].as_mut()());
    println!("{}", counters[1].as_mut()());
    println!("----------------------------------------------");
    let counters2 = create_counter(5);
    println!("{}", counters2[0].as_ref()());
    println!("{}", counters2[2].as_ref()());
    println!("{}", counters2[1].as_ref()());
}
// 6
// 5
// 4
// ----------------------------------------------
// 6
// 5
// 4
