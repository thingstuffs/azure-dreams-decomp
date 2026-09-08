#include "common.h"

/* 8-byte "frame" element: a scalar and a pointer field */
typedef struct S_800489F4_Frame {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ void *unk4;
} S_800489F4_Frame;

/* object touched by this function; only the accessed fields are named */
typedef struct S_800489F4_Obj {
    /* 0x00 */ S_800489F4_Frame *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad05[3];
    /* 0x08 */ void *unk8;
    /* 0x0C */ u8 pad0C[8];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[0x28 - 0x16];
    /* 0x28 */ S_800489F4_Frame ****unk28;
} S_800489F4_Obj;

/* Installs the selected animation frame and its secondary pointer, then updates the animation flags. */
void func_800489F4(S_800489F4_Obj *object, s16 animation_index, s16 frame_index) {
    S_800489F4_Frame ***frame_table_ref = *object->unk28;
    S_800489F4_Frame **frame_table = *frame_table_ref;
    S_800489F4_Frame *frame_base = frame_table[animation_index];
    S_800489F4_Frame *frame = &frame_base[frame_index];
    void *frame_data;

    object->unk0 = frame;
    frame_data = frame->unk4;
    object->unk4 = (u8)frame_index;
    object->unk14 = (object->unk14 & ~0x40) | 0x20;
    object->unk8 = frame_data;
}
