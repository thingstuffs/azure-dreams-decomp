#include "common.h"

typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

typedef void (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern s32 func_807018AC(s16 value);
extern u8 D_80700000[];

void func_80875404(void)
{
    Packed8 local;
    CallbackTable callbacks;
    register s32 offset ASM_REG("$16");
    register s16 *base ASM_REG("$17");
    register s16 *base_after ASM_REG("$18");
    register s32 index ASM_REG("$19");
    register s16 *value_ptr ASM_REG("$2");
    s32 dispatch_offset;

    local = *(Packed8 *)(D_80700000 + 0xBD4);
    callbacks = *(CallbackTable *)(D_80700000 + 0xBDC);
    index = 0;
    if (*(s16 *)&local != 0) {
        ASM_SCHED_BARRIER();
        base = (s16 *)&local;
        offset = 0;
loop_2:
        dispatch_offset = index * 4;
        base_after = base;
        if (func_807018AC(*(s16 *)(offset + (s32)base)) == 0) {
            goto dispatch;
        }
        offset += 2;
        index += 1;
        value_ptr = (s16 *)(offset + (s32)base_after);
        ASM_KEEP_NV(value_ptr);
        if (*value_ptr == 0) {
            goto block_4;
        }
        goto loop_2;
    }
block_4:
    dispatch_offset = index * 4;
dispatch:
    callbacks.callback[index](index);
}
