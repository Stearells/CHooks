#include "main.h"

ch_hook my_hook;

void my_func(int n)
{
    printf("from original: %d\n", n * 10);
}

void my_hooked_func(int n)
{
    void* original_address = ch_uninstall_hook(&my_hook);
    my_func(n);
    ch_install_hook(&my_hook, original_address, (void*)my_hooked_func);
    printf("from hooked: %d\n", n);
}

int main()
{
    ch_init_hook(&my_hook);
    ch_install_hook(&my_hook, (void*)my_func, (void*)my_hooked_func);
    my_func(5);
    ch_uninstall_hook(&my_hook);
    return 0;
}
