#include "chooks.h"

void ch_init_hook(ch_hook* hook)
{
    /* clear structure fields */

    //hook->original_address = ch_nullptr;
    //hook->original_code = ch_nullptr;
    //hook->size = 0;

    memchr(hook, 0, sizeof(ch_hook));
}

ch_bool ch_install_hook(ch_hook* hook, void* source, void* destination)
{
    /* hook already installed */
    if(hook->original_code != ch_nullptr)
        return ch_false;
    
    /* source or destination is nullptr */
    if(source == ch_nullptr || destination == ch_nullptr)
        return ch_false;

    /* create patch */
#ifdef _WIN64
    /* 
       mov rax, destination
       push rax
       ret
    */
	unsigned char patch[] =
	{
		0x48, 0xB8,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x50,
		0xC3
	};

	*((ch_uint*)&patch[2]) = (ch_uint)destination;
#else
    /* 
       mov eax, destination
       push eax
       ret
    */
	unsigned char patch[] =
	{
		0xB8,
		0x00, 0x00, 0x00, 0x00,
		0x50,
		0xC3
	};

	*((ch_uint*)&patch[1]) = (ch_uint)(ch_uint*)destination;
#endif

    /* allocate memory to store original code */
    hook->original_code = malloc(sizeof(patch));
    if (hook->original_code == ch_nullptr)
        return ch_false;
    
    /* unprotect original code */
    DWORD old_protection;
    VirtualProtect(source, sizeof(patch), PAGE_EXECUTE_READWRITE, &old_protection);

    /* store original code */
    memcpy(hook->original_code, source, sizeof(patch));

    /* write patch */
    memcpy(source, &patch, sizeof(patch));

    /* save original address and patch size*/
    hook->original_address = source;
    hook->size = sizeof(patch);

    return ch_true;
}

void *ch_uninstall_hook(ch_hook* hook)
{
    /* hook is not installed */
    if (hook->original_code == ch_nullptr)
        return ch_nullptr;
    
    /* restore original code */
    memcpy(hook->original_address, hook->original_code, hook->size);

    /* free hook data */
    free(hook->original_code);
    hook->original_code = ch_nullptr;
    hook->size = 0;

    return hook->original_address;
}

ch_bool ch_is_hook_installed(ch_hook* hook)
{
    return hook->original_code != ch_nullptr ? ch_true : ch_false;
}
