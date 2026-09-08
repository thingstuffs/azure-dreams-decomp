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

/* Starts the ratio ramp using the current counter, advances it, and updates the object. */
void func_80050640(S_80050640 *obj)
{
    func_80050550(&obj->buf58, obj->counter++, 3);

    obj->vtable = (void (*)(void *, s32, s32, s32))func_800505BC;
    func_80050308(obj);
}
