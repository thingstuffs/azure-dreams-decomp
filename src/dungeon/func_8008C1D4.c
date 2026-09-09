#include "common.h"

typedef struct S_func_80091934_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_func_80091934_0;

/* Sets object state bytes from the mode and clears its state word. */
void func_80091934(S_func_80091934_0 *object, s32 unused_1, s32 unused_2, s32 mode) {
    object->unk_9A = 0x2B;
    if (mode == 0) {
        object->unk_9B = 0x10;
    } else {
        object->unk_9B = 0;
    }
    object->unk_8C = 0;
    return;
}
