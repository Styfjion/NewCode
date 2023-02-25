#[derive(Default, Debug)]
struct Data {
    id: i32,
    name: String,
    data: Vec<i32>
}

fn set_val<'a>(mut data: &'a mut Vec<i32>, new_obj: &'a mut Data) {
    data.push(1);
    data.push(2);

    data = &mut new_obj.data;
    data.push(3);
}

#[cfg(test)]
mod test {
    use crate::mut_ref_test::{Data, set_val};

    #[test]
    fn test_fn() {
        let mut data1 = Data::default();
        data1.data.push(1);

        let mut data2 = Data::default();
        data2.data.push(1);

        set_val(&mut data1.data, &mut data2);

        println!("data1:{:?}", data1);
        println!("data2:{:?}", data2);
    }
}
