#include "common.h"

/* Struct for func_80050A00's first argument: only the accessed offset (0x68, a pointer)
   is given a real field; 0x30/0x40/0x58 are only address-taken (sub-object bases). */
typedef struct {
    u8 pad0[0x68];
    void *field_68;
} S_80050A00;

extern void func_800509C4(void *a0, void *a1);
extern void func_8005084C(void *a0, void *a1, void *a2, void *a3);
extern void func_800506BC(void *a0, void *a1, void *a2);

/* func_80050A00: Re-inits a0 via func_800509C4(a0, a1); inits three sub-objects at
   a0+0x58/0x30/0x40 via func_8005084C; then calls func_800506BC on the object pointed
   to by a0->field_68, passing a0 and a1 along. */
void func_80050A00(S_80050A00 *a0, void *a1)
{
    func_800509C4(a0, a1);
    func_8005084C(a0, (u8 *)a0 + 0x58, (u8 *)a0 + 0x30, (u8 *)a0 + 0x40);
    func_800506BC(a0->field_68, a0, a1);
}
