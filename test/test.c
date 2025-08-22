#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int global_counter = 0;

void* thread_func(void* arg) {
    for (int i = 0; i < 1000; i++) {
        global_counter++;  // Helgrindでデータ競合検出
    }
    return NULL;
}

int main() {
    char* buffer = malloc(100);  // メモリ確保（memcheckでリーク検出）
    strcpy(buffer, "Hello, world!");  // 安全でない関数（CodeQLで警告）

    char* leak = malloc(50);  // メモリリーク（freeしない）

    int uninitialized;  // 未初期化変数（memcheckで警告）
    if (uninitialized > 0) {
        printf("Uninitialized value used: %d\n", uninitialized);
    }

    int unused_variable = 42;  // 未使用変数（CodeQLで