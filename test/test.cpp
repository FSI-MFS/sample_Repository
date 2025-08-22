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

    char* leak = new char