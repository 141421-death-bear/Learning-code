#include <stdio.h>

int main() {
    int b = 300 * 400 *500;  // 结果为60000000
    int a = 50000 * 50000; // 结果溢出
    printf("%d\n", a);
    printf("%d\n", b);
}