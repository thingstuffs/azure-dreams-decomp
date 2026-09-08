#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800C30A4_0_pre {
    u16 unk_00;
} S_800C30A4_0_pre;   /* the 0x2 bytes before arg0 in func_800C30A4, addressed as arg0[-1] */



extern s32 D_800814A0;
extern u8 D_80082660[];

/* Clears the object slot and sets the object and global removal flags. */
void func_800C30A4(void *object) {
    s32 slot_offset;
    u8 *slots;

    slots = D_80082660;
    slot_offset = ((Rec_func_80094268_arg0 *)object)->unk_60 * 8;
    (*(s32 *)((u8 *)(slots + slot_offset) + 4)) = 0;
    (*(u16 *)((u8 *)object + -2)) = (u16) (((S_800C30A4_0_pre *)object)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
}
