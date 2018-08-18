#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <functional>
#include <chrono>
#include <cstdlib>
#include "workers.hpp"

void t_print_example()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        auto f = [i]()
        {
            std::cout << i << std::endl;
        };
        std::thread t(f);
        threads.push_back(std::move(t));
    }
    for (auto& t : threads) {
        t.join();
    }
}

void t_print_example_with_mutex()
{
    std::vector<std::thread> threads;
    std::mutex print_mutex;
    for (int i = 0; i < 10; ++i) {
        auto f = [i, &print_mutex]()
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << i << std::endl;
        };
        std::thread t(f);
        threads.push_back(std::move(t));
    }
    for (auto& t : threads) {
        t.join();
    }
}

void t_print_example_with_atomic()
{
    std::vector<std::thread> threads;
    std::atomic_int counter{0};
    std::mutex print_mutex;
    for (int i = 0; i < 10; ++i) {
        auto f = [i, &counter, &print_mutex]()
        {
            counter += i;
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << counter << std::endl;
        };
        std::thread t(f);
        threads.push_back(std::move(t));
    }
    for (auto& t : threads) {
        t.join();
    }
}

void t_detach_example()
{
    std::atomic_bool kill_flag(true);
    std::thread t
    (
        [&kill_flag]()
        {
            while(kill_flag)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::cout << "Detached thread " << std::this_thread::get_id() << std::endl;
            }
            std::cout << "Exit detached thread " << std::this_thread::get_id() << std::endl;
        }
    );
    t.detach();
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Main thread " << std::this_thread::get_id() << std::endl;
    }
    kill_flag = false;
    std::cout << "Exit main thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "Threading print example" << std::endl;
    t_print_example();
    ////////////////////////////////////////////////////////////////
    std::cout << "Threading with mutex print example" << std::endl;
    t_print_example_with_mutex();
    ////////////////////////////////////////////////////////////////
    std::cout << "Threading with atomic print example" << std::endl;
    t_print_example_with_atomic();
    ////////////////////////////////////////////////////////////////
    std::cout << "Threading map example" << std::endl;
    std::cout << "Concurrent threads: " << std::thread::hardware_concurrency() << std::endl;
    ThreadPool pool;
    std::vector<int> args{0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0};
    auto res = pool.map<std::function<int(int)>, int, int>
    (
         [](int i)
         {
             std::this_thread::sleep_for(std::chrono::seconds(rand()%2));
             return i +10;
         },
         args
    );
    for (int& r: res)
    {
        std::cout << r << std::endl;
    }
    ////////////////////////////////////////////////////////////////
    std::cout << "Threading detach example" << std::endl;
    t_detach_example();
    return 0;
}