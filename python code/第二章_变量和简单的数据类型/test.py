n = str(input("请输入内容: "))
if n in ["傻逼", "sb", "傻子"]:
    print("你说谁呢？")
else:
    print("你说的'" + n + "'真好听！")

#include <stdio.h>
#include <string.h>
#int main() {
#    char n[100];
#    scanf("%s", n);
#    if (strcmp(n, "傻逼") == 0 || strcmp(n, "sb") == 0 || strcmp(n, "傻子") == 0) {
#        printf("你说谁呢？");
#    } else {
#        printf("你说的'%s'真好听！", n);
#    }
#}
