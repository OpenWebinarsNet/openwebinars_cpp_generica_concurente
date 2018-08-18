#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>


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

int main() {
    std::cout << "Threading print example" << std::endl;
    t_print_example();
    std::cout << "Threading with mutex print example" << std::endl;
    t_print_example_with_mutex();
    std::cout << "Threading with atomic print example" << std::endl;
    t_print_example_with_atomic();
    return 0;
}