#include "logger.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cassert>

// 压力测试
void stress_test() {
    std::cout << "\n=== 运行压力测试 ===" << std::endl;
    const int thread_count = 100;    // 压力测试线程数
    const int logs_per_thread = 1000000; // 每个线程输出的日志数

    auto stress_task = [logs_per_thread](int thread_id) {
        for (int i = 0; i < logs_per_thread; ++i) {
            // 生成不同长度的日志内容
            std::stringstream ss;
            ss << "压力测试 - 线程" << thread_id << " - 日志" << i 
               << " - 这是一条长度可变的测试日志，用于模拟实际业务场景中的不同日志长度。";
            LOGINFO << ss.str();
        }
    };

    std::vector<std::thread> threads;
    auto start_time = std::chrono::high_resolution_clock::now();

    // 启动压力测试线程
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(stress_task, i);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 等待异步日志处理完成
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    
    size_t total_logs = thread_count * logs_per_thread;
    double logs_per_sec = total_logs / (double)duration.count();
    
    std::cout << "压力测试完成：" 
              << thread_count << "个线程共输出" << total_logs << "条日志，"
              << "耗时" << duration.count() << "秒，"
              << "平均吞吐量：" << std::fixed << std::setprecision(2) 
              << logs_per_sec << "条/秒" << std::endl;
}

int main(){
    stress_test();
}