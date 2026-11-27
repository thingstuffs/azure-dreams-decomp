#include "common.h"
#include "town/shop/floating_number_widget_g00612.h"

typedef struct {
    s32 tint_color;
    s16 scale_x;
    s16 scale_y;
    s16 x;
    s16 y;
    s16 depth;
    s8 unkE;
    s8 mode;
} TownPartA;

typedef struct {
    s32 rot_xy;
    s32 rot_z_offset_x;
    s16 offset_y;
    s16 offset_z;
} TownPartB;

typedef struct {
    s32 sprite_cmd;
    TownPartA *partA;
    TownPartB *partB;
} TownOwner;

/* Initialize and attach both town parts, then set the owner and part defaults. */
void initialize_shop_parts(TownOwner *owner, TownPartA *part_a, TownPartB *part_b) {
    s32 *defaults_a = display_block_defaults.words;
    DisplayPositionWords *defaults_b = &display_vector_defaults;
    s32 first_b_word;

    part_a->tint_color = display_block_defaults.words[0];
    ((s32 *)part_a)[1] = defaults_a[1];
    ((s32 *)part_a)[2] = defaults_a[2];
    first_b_word = display_vector_defaults.unk0;
    ((s32 *)part_a)[3] = defaults_a[3];
    part_b->rot_xy = first_b_word;
    part_b->rot_z_offset_x = defaults_b->unk4;
    ((s32 *)part_b)[2] = defaults_b->unk8;
    owner->partA = part_a;
    owner->partB = part_b;
    owner->sprite_cmd = 0;
    owner->partA->x = 0;
    owner->partA->y = -0x6C;
    owner->partA->depth = 0x200;
    owner->partA->mode = 4;
    owner->partA->scale_y = 0;
    owner->partB->offset_y = 0x30;
}
