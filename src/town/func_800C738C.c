#include "common.h"
#include "shared/object_index_slots.h"

typedef struct S_800C4AEC_0 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x20];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0xC];
    void * unk_98;
} S_800C4AEC_0;   /* temp_a3 in func_800C4AEC */

typedef struct S_800C4AEC_1 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_800C4AEC_1;   /* temp_t0 in func_800C4AEC */

typedef struct S_800C4AEC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    s16 unk_12;
} S_800C4AEC_2;   /* store_ptr in func_800C4AEC */


#define NULL 0

extern u16 D_800D2650[];
extern u16 D_800D2FC0[];

extern void func_800C41D4(void *, s32, s32);


/* Update the sprite position using frame offsets, save the object position, and apply the update. */
void func_800C4AEC(void *object_arg, s32 update_arg, s32 setup_context)
{
    S_800C4AEC_0 *object = object_arg;
    S_800C4AEC_1 *sprite;
    u32 flags;
    s32 x_offset;
    s32 y_offset;
    u32 row_offset;

    *(((u8 *)D_80082660) + object->unk_60 * 8) = 0;
    sprite = object->unk_98;
    if (sprite != NULL && ((flags = sprite->unk_08) & 0xC0000000) == 0xC0000000) {
        u32 table_select = (flags >> 23) & 1;
        u32 frame_index = (flags >> 24) & 0x3F;

        if (table_select == 0) {
            u16 *offsets;

            row_offset = frame_index * 32;
            offsets = (u16 *)((u8 *)D_800D2650 + row_offset);

            x_offset = offsets[0] + offsets[2];
            y_offset = offsets[1] + offsets[3];
        } else {
            u16 *offsets;

            row_offset = frame_index * 32;
            offsets = (u16 *)((u8 *)D_800D2FC0 + row_offset);

            x_offset = offsets[0] + offsets[2];
            y_offset = offsets[1] + offsets[3];
        }
    } else {
        y_offset = x_offset = 0;
    }
    if (sprite != NULL) {
        ((S_800C4AEC_2 *)object->unk_98)->unk_10 = object->unk_88 - x_offset;
        ((S_800C4AEC_2 *)object->unk_98)->unk_12 = object->unk_8A - y_offset;
    }
    object->unk_84 = object->unk_88;
    object->unk_86 = object->unk_8A;
    func_800C41D4(object, update_arg, setup_context);
}
