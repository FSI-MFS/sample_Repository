#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>

int global_counter = 0; // Helgrindで競合検出対象
std::mutex mtx;

void unsafe_increment() {
    for (int i = 0; i < 1000; ++i) {
        global_counter++; // ロックなし → データ競合
    }
}

void safe_increment() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        global_counter++;
    }
}

int main() {
    char* buffer = new char[100]; // メモリ確保（Valgrindでリーク検出）
    strcpy(buffer, "Hello, unsafe world!"); // 安全でない関数（CodeQLで警告）

    char* leak = new char[50]; // メモリリーク（deleteしない）

    int uninitialized; // 未初期化変数（Valgrindで警告）
    if (uninitialized > 0) {
        std::cout << "Uninitialized value: " << uninitialized << std::endl;
    }

    int unused_variable = 42; // 未使用変数（CodeQLで警告）

    std::thread t1(unsafe_increment);
    std::thread t2(unsafe_increment);
    t1.join();
    t2.join();

    std::thread t3(safe_increment);
    std::thread t4(safe_increment);
    t3.join();
    t4.join();

    delete[] buffer;
    // leakはdeleteしない → メモリリーク

    std::cout << "Final counter: " << global_counter << std::endl;
    return 0;
}
