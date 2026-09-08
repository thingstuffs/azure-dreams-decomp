#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800C2864;
extern void *D_800FE4A0;

typedef struct S_800C283C_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    M2C_UNK * unk_50;
} S_800C283C_0;   /* v1 in func_800C283C */

/* Reset the current object's state and data pointer when its address matches. */
void func_800C283C(s32 object_addr) {
    S_800C283C_0 *current_object = D_800FE4A0;
    if (current_object == (void *)object_addr) {
        current_object->unk_14 = 0;
        current_object->unk_50 = &D_800C2864;
    }
}
