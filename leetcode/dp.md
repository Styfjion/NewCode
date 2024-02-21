## lee871
https://leetcode.cn/problems/minimum-number-of-refueling-stops/description/

背包dp
1. 二维解法
`dp[i][j]`表示到达第i个加油站时加j次油时，可以行驶的最远距离
```rust
pub fn min_refuel_stops(target: i32, start_fuel: i32, stations: Vec<Vec<i32>>) -> i32 {
    let mut dp = vec![vec![0; stations.len() + 1]; stations.len() + 1];
    dp.iter_mut().for_each(|row| row[0] = start_fuel);
    for i in 1..dp.len() {
        for j in 1..dp.len() {
            dp[i][j] = dp[i - 1][j];
            // 注意dp数组从0开始，对应到实际的加油站为第一个加油站
            if dp[i - 1][j - 1] >= stations[i - 1][0] {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + stations[i - 1][1]);
            }
        }
    }
    for (idx, val) in dp.last().unwrap().iter().enumerate() {
        if *val >= target {
            return idx as i32;
        }
    }
    -1
}
```
2. 滚动数组优化为一维
注意压缩后第二重循环需要倒序，因为`dp[i][j]`由`dp[i - 1][j - 1]`更新得到，压缩为一维后需要先更新后面的
```rust
pub fn min_refuel_stops(target: i32, start_fuel: i32, stations: Vec<Vec<i32>>) -> i32 {
    let mut dp = vec![0; stations.len() + 1];
    dp[0] = start_fuel;
    for i in 1..dp.len() {
        // 倒序更新
        for j in (1..i + 1).rev() {
            if dp[j - 1] >= stations[i - 1][0] {
                dp[j] = max(dp[j], dp[j - 1] + stations[i - 1][1]);
            }
        }
    }
    for (idx, val) in dp.iter().enumerate() {
        if *val >= target {
            return idx as i32;
        }
    }
    -1
}
```

## lee97
https://leetcode.cn/problems/interleaving-string/description/
1. 记忆化搜索
`cache[i][j]`表示使用s1的前i段，s2的前j段能否组成s3
```rust
struct SolImpl {
    s1: String,
    s2: String,
    s3: String,
    cache: Vec<Vec<i32>>,
}

impl SolImpl {
    fn new(s1: String, s2: String, s3: String) -> Self {
        let cache = vec![vec![0; s2.len() + 1]; s1.len() + 1];
        Self { s1, s2, s3, cache }
    }
    fn dfs(&mut self, i: usize, j: usize) -> bool {
        if self.cache[i][j] != 0 {
            return self.cache[i][j] == 1;
        }
        // 递归到最终返回true
        if i + j == self.s3.len() {
            return true;
        }

        let mut ans = false;
        if i < self.s1.len() && self.s1.as_bytes()[i] == self.s3.as_bytes()[i + j]{
            ans |= self.dfs(i + 1, j)
        }
        if j < self.s2.len() && self.s2.as_bytes()[j] == self.s3.as_bytes()[i + j]{
            ans |= self.dfs(i, j + 1)
        }
        self.cache[i][j] = if ans { 1 } else { -1 };
        ans
    }
}

impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        if s1.len() + s2.len() != s3.len() {
            return false
        }
        let mut sol = SolImpl::new(s1, s2, s3);
        sol.dfs(0, 0)
    }
}
```
2. 线性dp
`dp[i][j]`表示使用s1的前i段，s2的前j段能否组成s3，线性dp最后返回矩阵右下角的值
```rust
impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        if s1.len() + s2.len() != s3.len() {
            return false
        }
        let mut dp = vec![vec![false;s2.len() + 1];s1.len() + 1];
        dp[0][0] = true;
        // 注意dp数组从0开始，对应到字符串的第一个字母
        // 先计算递推的边界值
        for i in 1..s1.len() + 1 {
            if !dp[i - 1][0] {
                break;
            }
            dp[i][0] = s1.as_bytes()[i - 1] == s3.as_bytes()[i - 1]
        }

        for j in 1..s2.len() + 1 {
            if !dp[0][j - 1] {
                break;
            }
            dp[0][j] = s2.as_bytes()[j - 1] == s3.as_bytes()[j - 1];
        }
        for i in 1..s1.len() + 1 {
            for j in 1..s2.len() + 1 {
                if s1.as_bytes()[i - 1] == s3.as_bytes()[i + j - 1] {
                    dp[i][j] |= dp[i - 1][j]
                }
                if s2.as_bytes()[j - 1] == s3.as_bytes()[i + j - 1] {
                    dp[i][j] |= dp[i][j - 1]
                }
            }
        }
        *dp.last().unwrap().last().unwrap()
    }
}
```

## lee375
https://leetcode.cn/problems/guess-number-higher-or-lower-ii/description/
1. 记忆化搜索
```rust
use std::cmp::{max, min};
impl Solution {
    pub fn get_money_amount(n: i32) -> i32 {
        let mut cache = vec![vec![-1; (n + 1) as usize]; (n + 1) as usize];
        Self::dfs(1, n as usize, &mut cache)
    }

    fn dfs(left: usize, right: usize, cache: &mut [Vec<i32>]) -> i32 {
        if cache[left][right] != -1 {
            return cache[left][right];
        }

        if left >= right {
            return 0;
        }

        let mut ans = i32::MAX;
        for i in left..right {
            let cur_sum = max(
                Self::dfs(left, i - 1, cache),
                Self::dfs(i + 1, right, cache),
            ) + i as i32;
            ans = min(ans, cur_sum)
        }
        cache[left][right] = ans;
        ans
    }
}
```
2. 区间dp
区间dp分三重循环，长度循环，边界循环，分割点循环
最终返回矩阵以区间坐标为下标的值

```rust
use std::cmp::{max, min};
impl Solution {
    pub fn get_money_amount(n: i32) -> i32 {
        let mut dp = vec![vec![0; (n + 1) as usize]; (n + 1) as usize];
        // 循环长度
        for len in 1..n {
            // 循环边界
            for left in 1..n - len + 1 {
                let right = left + len;
                dp[left as usize][right as usize] = i32::MAX;
                // 循环分割点
                for x in left..right {
                    let cur_sum = max(
                        dp[left as usize][(x - 1) as usize],
                        dp[(x + 1) as usize][right as usize],
                    ) + x;
                    dp[left as usize][right as usize] = min(dp[left as usize][right as usize], cur_sum);
                }
            }
        }
        dp[1][n as usize]
    }
}
```