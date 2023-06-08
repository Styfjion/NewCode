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
            return *cur_value;
        };

        let dec = ||{
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value -= 1;
            return *cur_value;
        };

        let reset = ||{
            let mut cur_value = self.cur_value.lock().unwrap();
            *cur_value = self.prime;
            return *cur_value;
        };
        return vec![Box::new(add), Box::new(dec), Box::new(reset)];
    }
}

fn main() {
    let mut sol = Counter::default();
    let mut counters = sol.create_counter(5);
    println!("{}", counters[0].as_mut()());
    println!("{}", counters[2].as_mut()());
    println!("{}", counters[1].as_mut()());
}
// 6
// 5
// 4
