#include "common.h"
#include "shared/menu_display.h"

typedef struct {
    s32 tint_color;
    s32 scale_xy;
    s32 pos_xy;
    s32 depth_and_mode;
} Template16;


typedef struct {
    s32 tint_color;
    s16 scale_x;
    s16 scale_y;
    s16 x;
    s16 y;
    s16 depth;
    u8 unkE;
    u8 mode;
} Instance16;

typedef struct {
    s32 rot_xy;
    s32 rot_z_offset_x;
    s16 offset_y;
    s16 offset_z;
} Instance12;

typedef struct {
    s32 sprite_cmd;
    Instance16 *block;
    Instance12 *vector;
} Owner;

/* Initialize and attach two instances from templates, then apply their default values. */
void initialize_display_instances(Owner *owner, Template16 *instance16, Instance12 *instance12) {
    MenuDisplayBlock *template16 = &display_block_defaults;
    DisplayPositionWords *template12 = &display_vector_defaults;
    s32 *header_word;

    instance16->tint_color = template16->words[0];
    header_word = &template12->unk0;
    instance16->scale_xy = template16->words[1];
    instance16->pos_xy = template16->words[2];
    instance16->depth_and_mode = template16->words[3];

    instance12->rot_xy = *header_word;
    instance12->rot_z_offset_x = template12->unk4;
    ((DisplayPositionWords *)instance12)->unk8 = template12->unk8;

    owner->block = (Instance16 *)instance16;
    owner->vector = instance12;
    owner->sprite_cmd = 0;

    owner->block->x = -60;
    owner->block->y = -92;
    owner->block->depth = 0x200;
    owner->block->scale_y = 0;
    owner->vector->offset_y = 0x30;
    owner->block->mode = 4;
}
