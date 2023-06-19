use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

//Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution {}

type ContianerNode = Rc<RefCell<Option<Box<ListNode>>>>;

impl Solution {
    pub fn remove_zero_sum_sublists(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut pre_sum_map: HashMap<i32, Option<Box<ListNode>>> = HashMap::from([(0, None)]);
        let mut pre_sum_stack = vec![0];
        let mut cur_sum = 0;
        let mut new_head = head.clone();
        let mut node = head.clone();
        while node.is_some() {
            let node_val = node.as_ref().unwrap().val;
            cur_sum += node_val;
            match pre_sum_map.get_mut(&cur_sum) {
                None => {
                    pre_sum_map.insert(cur_sum, node.clone());
                    pre_sum_stack.push(cur_sum)
                }
                Some(val) => {
                    match val {
                        None => {
                            new_head = node.as_ref().unwrap().next.clone();
                        }
                        Some(inner_val) => {
                            inner_val.next = node.as_ref().unwrap().next.clone();
                        }
                    };
                    while *pre_sum_stack.last().unwrap() != cur_sum {
                        pre_sum_map.remove(&pre_sum_stack.pop().unwrap());
                    }
                }
            }
            node = node.as_ref().unwrap().next.clone();
        }
        new_head
    }

    fn build_node_container(head: Option<Box<ListNode>>) -> Vec<ContianerNode> {
        let mut node = head.as_ref();
        let mut container = Vec::<ContianerNode>::new();
        while node.is_some() {
            container.push(Rc::new(RefCell::new(node.cloned())));
            node = node.as_ref().unwrap().next.as_ref()
        }
        container
    }
}

fn main() {
    let val = vec![1, 2, 3, -3, -2];
    let mut nodes: Vec<_> = val
        .into_iter()
        .map(|unit| Some(Box::new(ListNode::new(unit))))
        .collect();
    for i in (0..nodes.len()).rev() {
        if i < nodes.len() - 1 {
            nodes[i].as_mut().unwrap().next = nodes[i + 1].clone();
        }
    }

    let mut node = nodes[0].as_ref();
    while node.is_some() {
        println!("{}", node.unwrap().val);
        node = node.unwrap().as_ref().next.as_ref();
    }
}
