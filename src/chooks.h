/*
    Stearells (C) 2023
    CHooks
*/

#ifndef _CHOOKS_H_
#define _CHOOKS_H_

#include <windows.h> // VirtualProtect only used.
#include <mem.h>

#ifdef _WIN64
	typedef unsigned long long ch_uint;
#else
	typedef unsigned long      ch_uint;
#endif

typedef unsigned char ch_bool;

#define ch_nullptr (void*)0
#define ch_true 1
#define ch_false 0

/* main hook structure */
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

#endif // _CHOOKS_H_
