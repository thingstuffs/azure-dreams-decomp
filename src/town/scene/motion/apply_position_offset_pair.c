#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/motion.h"
#include "shared/town_root.h"




typedef struct S_80019E7C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    union { s32 * p; u8 * p2; } unk_1C;   /* accessed as both */
} S_80019E7C_1;   /* base in apply_position_offset_pair */


/* Invokes the root callback and adjusts two object fields using signed offsets. */
void apply_position_offset_pair(void *offsets)
{
    Rec_D_80016000 *root;
    u16 second_offset;

    town_scene_root->services->callback_258(1);
    root = town_scene_root;
    root->position->x += *(s16 *)offsets;
    second_offset = *(u16 *)((u8 *)offsets + 2);
    root->position->y += (s16)second_offset / 2 - 0x40;
}
