```c
typedef struct ch_hook_s
{
    void*         original_code;
    void*         original_address;
    unsigned char size;
} ch_hook;

void     ch_init_hook           (ch_hook* hook);
ch_bool  ch_install_hook        (ch_hook* hook, void* source, void* destination);
void*    ch_uninstall_hook      (ch_hook* hook);
ch_bool  ch_is_hook_installed   (ch_hook* hook);
```
