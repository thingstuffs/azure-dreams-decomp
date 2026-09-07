#include "common.h"

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

extern u8 D_80082660;
extern u16 D_800D2650[];
extern u16 D_800D2FC0[];

extern void func_800C41D4(void *, s32);


/* Update the sprite position using frame offsets, save the object position, and apply the update. */
void func_800C4AEC(void *object_arg, s32 update_arg)
{
    register void *object ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    register void *sprite ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register s32 saved_update_arg ASM_REG("$9");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u32 sprite_flags;
    u32 table_select;
    u32 frame_index;
    u16 *frame_offsets;
    u32 extra_x;
    u32 extra_y;
    s32 x_offset;
    register s32 y_offset ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
    u32 coord;
    S_800C4AEC_2 *sprite_pos;

    object = object_arg;
    *(&D_80082660 + ((S_800C4AEC_0 *)object)->unk_60 * 8) = 0;
    sprite = ((S_800C4AEC_0 *)object)->unk_98;
    saved_update_arg = update_arg;
    if (sprite != NULL) {
        sprite_flags = ((S_800C4AEC_1 *)sprite)->unk_08;
        if ((sprite_flags & 0xC0000000) == 0xC0000000) {
            table_select = (sprite_flags >> 23) & 1;
            frame_index = (sprite_flags >> 24) & 0x3F;
            if (table_select == 0) {
                frame_offsets = &D_800D2650[frame_index * 16];
            } else {
                frame_offsets = &D_800D2FC0[frame_index * 16];
            }
            x_offset = frame_offsets[0];
            extra_x = frame_offsets[2];
            ASM_KEEP(extra_x);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            y_offset = frame_offsets[1];
            extra_y = frame_offsets[3];
            ASM_KEEP(extra_y);   /* MATCH pin: load-bearing for the whole function shape */
            x_offset += extra_x;
            y_offset += extra_y;
            goto apply_offsets;
        }
    }
    x_offset = 0;
    ASM_KEEP(x_offset);   /* MATCH pin: retail register colouring depends on it */
    y_offset = x_offset;

apply_offsets:
    if (sprite != NULL) {
        coord = ((S_800C4AEC_0 *)object)->unk_88;
        sprite_pos = ((S_800C4AEC_0 *)object)->unk_98;
        coord -= x_offset;
        sprite_pos->unk_10 = (s16)coord;
        coord = ((S_800C4AEC_0 *)object)->unk_8A;
        sprite_pos = ((S_800C4AEC_0 *)object)->unk_98;
        coord -= y_offset;
        sprite_pos->unk_12 = (s16)coord;
    }
    ((S_800C4AEC_0 *)object)->unk_84 = ((S_800C4AEC_0 *)object)->unk_88;
    ((S_800C4AEC_0 *)object)->unk_86 = ((S_800C4AEC_0 *)object)->unk_8A;
    func_800C41D4(object, saved_update_arg);
}
