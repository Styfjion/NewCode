以下是 C++ 中 `std::async` 的使用方法详解，结合执行策略、参数传递和实际场景进行说明：

---

### 一、基础用法：启动异步任务
`std::async` 的核心功能是启动异步任务并返回 `std::future` 对象，通过 `future.get()` 获取结果。
```cpp
#include <future>
#include <iostream>

int compute(int x) {
    return x * x;
}

int main() {
    // 启动异步任务（默认策略）
    auto future = std::async(compute, 5); 
    std::cout << "结果：" << future.get(); // 输出：25
}
```
- **特点**：异步任务可能在新线程或当前线程执行，取决于策略（见下文）。
- **返回值**：`std::future` 对象存储结果，调用 `get()` 时会阻塞等待任务完成。

---

### 二、执行策略
`std::async` 支持三种执行策略，需通过 `std::launch` 参数显式指定：

1. **`std::launch::async`**  
   强制创建新线程执行任务，适用于需要并行加速的场景。
   ```cpp
   auto future = std::async(std::launch::async, compute, 5);
   ```

2. **`std::launch::deferred`**  
   延迟执行，仅在调用 `future.get()` 时在当前线程同步执行，适用于资源敏感任务。
   ```cpp
   auto future = std::async(std::launch::deferred, compute, 5);
   ```

3. **默认策略（组合模式）**  
   未指定策略时，由编译器决定执行方式（可能异步或延迟），不推荐依赖此行为。

---

### 三、参数传递方式
`std::async` 支持多种参数传递方式，需注意**生命周期管理**和**引用传递**：

1. **按值传递**  
   ```cpp
   auto future = std::async(std::launch::async, compute, 5); // 值传递
   ```

2. **按引用传递**  
   使用 `std::ref` 包装引用：
   ```cpp
   int x = 5;
   auto future = std::async(std::launch::async, [](int& n) { return n * n; }, std::ref(x));
   ```

3. **移动语义（`std::move`）**  
   适用于不可复制的对象（如 `std::unique_ptr`）：
   ```cpp
   auto data = std::make_unique<int>(5);
   auto future = std::async(std::launch::async, [](std::unique_ptr<int> p) { return *p; }, std::move(data));
   ```

---

### 四、异常处理
异步任务抛出的异常会通过 `future.get()` 传递到调用线程，需用 `try-catch` 捕获：
```cpp
try {
    auto future = std::async([]() { throw std::runtime_error("Error!"); });
    future.get();
} catch (const std::exception& e) {
    std::cerr << "捕获异常：" << e.what();
}
```

---

### 五、高级用法
1. **批量任务并行处理**  
   使用容器管理多个 `std::future` 对象：
   ```cpp
   std::vector<std::future<int>> tasks;
   for (int i = 0; i < 10; ++i) {
       tasks.emplace_back(std::async(std::launch::async, compute, i));
   }
   for (auto& f : tasks) {
       std::cout << f.get() << " ";
   }
   ```

2. **共享结果（`std::shared_future`）**  
   允许多个线程访问同一结果：
   ```cpp
   auto future = std::async(std::launch::async, compute, 5);
   std::shared_future<int> shared = future.share();
   // 多个线程可调用 shared.get()
   ```

3. **超时控制**  
   通过 `wait_for()` 实现非阻塞等待：
   ```cpp
   auto future = std::async(/*...*/);
   if (future.wait_for(std::chrono::seconds(3)) == std::future_status::ready) {
       // 任务完成
   }
   ```

---

### 六、注意事项
1. **资源管理**：确保 `future` 对象的生命周期覆盖异步任务执行周期，避免资源泄漏。
2. **线程池限制**：频繁创建线程可能影响性能，建议结合线程池使用。
3. **死锁风险**：避免在主线程中同步等待异步任务时阻塞其他必要操作。

通过合理使用 `std::async`，可以简化多线程开发，提升程序性能和响应速度。
