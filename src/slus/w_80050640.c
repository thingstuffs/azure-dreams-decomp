#include "common.h"

typedef struct S_80050640 {
    void (*vtable)(void *a0, s32 a1, s32 a2, s32 a3);
    s32 unk4;
    s32 counter; /* 0x8 */
    u8 pad0C[0x58 - 0xC];
    u8 buf58[8]; /* passed to func_80050550 as a0 */
} S_80050640;

extern void func_80050550(void *a0, s32 a1, s32 a2);
extern void func_800505BC(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_80050308(void *a0);

/* Bumps the object's counter (returning the pre-increment value into
 * func_80050550), installs func_800505BC as the object's vtable/callback
 * function pointer, then dispatches through func_80050308. */
void func_80050640(S_80050640 *a0)
{
    func_80050550(&a0->buf58, a0->counter++, 3);

    a0->vtable = (void (*)(void *, s32, s32, s32))func_800505BC;
    func_80050308(a0);
}
