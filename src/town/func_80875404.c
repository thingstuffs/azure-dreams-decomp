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
    s32 offset;
    register s16 *base ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s16 *base_after;
    register s32 index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *value_ptr;
    s32 dispatch_offset;

    local = *(Packed8 *)(D_80700000 + 0xBD4);
    callbacks = *(CallbackTable *)(D_80700000 + 0xBDC);
    index = 0;
    if (*(s16 *)&local != 0) {
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
