#include "common.h"
#include "shared/object_flags.h"

typedef struct PtrSet {
    void *ptr[3];
} PtrSet;

typedef struct DeepRecord {
    u8 pad00[0x10];
    s32 value10;
} DeepRecord;

typedef struct MidRecord {
    u8 pad00[8];
    DeepRecord *deep08;
} MidRecord;

typedef struct RootRecord {
    u8 pad00[4];
    MidRecord *mid04;
    u8 pad08[0x2e];
    s16 state36;
} RootRecord;

typedef struct StateRecord {
    RootRecord *root00;
    s16 mode04;
    s16 timer06;
    u16 flags08;
} StateRecord;

typedef struct MotionRecord {
    u8 pad00[8];
    s32 value08;
    s32 value0c;
    s32 value10;
    s32 value14;
} MotionRecord;

typedef struct SpriteRecord {
    void *kind00;
    u8 pad04[8];
    s32 color0c;
    u8 pad10[4];
    u16 flags14;
} SpriteRecord;

extern PtrSet D_80020048;
extern u8 D_800F2A34[0x28];
extern u8 D_800F2A5C[0x68];
extern u8 D_800F2AC4[0x40];
extern u8 D_800F2B04[0x28];
extern u8 D_800F2B2C[0x28];

extern void select_record_entry_and_value(SpriteRecord *, void *, s32);
extern void advance_sprite_animation_and_textures(SpriteRecord *);
extern s32 rand(void);
extern void add_motion_deltas_to_position(MotionRecord *);
extern s32 query_lowered_transform_position(MotionRecord *);

/* Updates a sprite's launch, bounce, and fade states. */
void update_snowball_target(StateRecord *state, MotionRecord *motion, SpriteRecord *sprite)
{
    RootRecord *root;
    DeepRecord *motion_source;
    PtrSet sprite_choices;
    void *next_sprite;
    PtrSet *choices_ptr;

    next_sprite = 0;
    root = state->root00;
    motion_source = root->mid04->deep08;
    sprite_choices = D_80020048;
    advance_sprite_animation_and_textures(sprite);
    add_motion_deltas_to_position(motion);
    choices_ptr = &sprite_choices;

    switch (state->mode04) {
    case 0:
        sprite->color0c += 0x101010;
        if ((u8)sprite->color0c < 0xa0) {
            break;
        }
        sprite->color0c = 0x808080;
        {
            u16 sprite_flags = sprite->flags14;

            sprite_flags &= 0xfff3;

            sprite->flags14 = sprite_flags;
        }
        state->mode04++;
        break;

    case 1:
        if (state->flags08 & 1) {
            next_sprite = choices_ptr->ptr[rand() % 3];
            motion->value0c = ((rand() & 0x7f) - 0x40) << 15;
            motion->value14 = (0 - ((rand() & 0xf) + 8)) << 16;
            if (motion->value0c > 0) {
                sprite->flags14 |= 1;
            }
            motion->value10 = motion_source->value10;
            state->mode04 = 0x20;
        }
        if (root->state36 != 10) {
            break;
        }
        if (rand() & 1) {
            next_sprite = D_800F2B04;
        } else {
            next_sprite = D_800F2B2C;
        }
        state->mode04 = 0x100;
        break;

    case 0x20:
    {
        s32 floor_y;

        motion->value14 += 0x40000;
        floor_y = (s16)query_lowered_transform_position(motion);
        if (floor_y < motion->value08) {
            motion->value08 = floor_y;
            motion->value14 = (-motion->value14) >> 3;
        }
        if (sprite->flags14 & 0x6000) {
            state->timer06 = 10;
            if (sprite->kind00 == D_800F2AC4) {
                sprite->color0c = 0xa0a0a0;
                sprite->flags14 |= 0xc;
                state->mode04 = 0x22;
                break;
            }
            if (rand() & 1) {
                next_sprite = D_800F2A34;
            } else {
                next_sprite = D_800F2A5C;
            }
            state->mode04++;
        }
        motion->value0c -= motion->value0c >> 3;
        motion->value10 -= motion->value10 >> 3;
        break;
    }

    case 0x21:
    {
        s32 floor_y;
        u16 sprite_flags;

        motion->value14 += 0x40000;
        floor_y = (s16)query_lowered_transform_position(motion);
        if (floor_y < motion->value08) {
            motion->value08 = floor_y;
            motion->value14 = (-motion->value14) >> 3;
        }
        motion->value0c -= motion->value0c >> 3;
        motion->value10 -= motion->value10 >> 3;
        sprite_flags = sprite->flags14;
        if (!(sprite_flags & 0x6000)) {
            break;
        }
        sprite->flags14 = sprite_flags | 0xc;
        sprite->color0c = 0xa0a0a0;
        state->mode04++;
        break;
    }

    case 0x22:
        sprite->color0c += (s32)0xffdfdfe0;
        if (motion->value08 > 0) {
            motion->value14 = 0;
            motion->value08 = 0;
        }
        if ((u8)sprite->color0c < 0x20) {
            sprite->color0c = 0;
        }
        if (root->state36 != 9) {
            state->timer06--;
            if (state->timer06 > 0) {
                break;
            }
        }
        state->mode04 = 0xfff;
        break;

    case 0x100:
        sprite->color0c = 0xa0a0a0;
        sprite->flags14 |= 0xc;
        state->mode04++;
                        /* fallthrough */
    case 0x101:
        sprite->color0c += (s32)0xffdfdfe0;
        if ((u8)sprite->color0c < 0x20) {
            sprite->color0c = 0;
            state->mode04 = 0xfff;
        }
        break;

    case 0xfff:
        ((u16 *)state)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;

    }

    if (next_sprite != 0) {
        select_record_entry_and_value(sprite, next_sprite, 0);
        sprite->flags14 &= 0x9fff;
    }
}
