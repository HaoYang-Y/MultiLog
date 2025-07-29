#include "logger.h"
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <iostream>
// 线程安全测试
void thread_safety_test() {
    std::cout << "\n=== 运行线程安全测试 ===" << std::endl;
    const int thread_count = 5;    // 并发线程数
    const int logs_per_thread = 100; // 每个线程输出的日志数

    auto log_task = [logs_per_thread](int thread_id) {
        for (int i = 0; i < logs_per_thread; ++i) {
            LOGINFO << "线程" << thread_id << "输出第" << i << "条日志";
            // 随机微小延迟模拟实际业务场景
            std::this_thread::sleep_for(std::chrono::microseconds(rand() % 100));
        }
    };

    std::vector<std::thread> threads;
    auto start_time = std::chrono::high_resolution_clock::now();

    // 启动多个线程并发写日志
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(log_task, i);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "线程安全测试完成：" 
              << thread_count << "个线程共输出" 
              << (thread_count * logs_per_thread) << "条日志，"
              << "耗时" << duration.count() << "ms" << std::endl;
}

int main(){
    thread_safety_test();
}