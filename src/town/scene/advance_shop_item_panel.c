#include "common.h"
#include "town/scene.h"
#include "town/scene/object.h"
#include "town/scene/animation.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/score_sprite_data.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

extern u8 D_8028E214[];
extern u8 town_display_timing_table[];

extern void create_object_position_configures_color(u32, s32, s32, u32);
extern void create_object_initializes_position_sprite(const RisingScoreSpawn *, s32, s32);

typedef struct S_8052EA14_0 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
} S_8052EA14_0;   /* record in advance_shop_item_panel */

/* Per-frame shop-panel step: advance the panel's mode machine and spawn its sparkle particles. */
void advance_shop_item_panel(RisingScorePanel *object, ObjectPosition *position, SpriteFrameState *sprite)
{
    TownScoreCounterView *base;
    RisingScoreSpawn local;
    u8 *cell;
    S_8052EA14_0 *record;
    u16 bits;
    s32 dispatch;
    s32 i;
    s32 value0;
    s32 value;
    s32 next_value;
    s32 x;
    s32 random_low;
    u32 random;
    s32 case_0_height;
    s32 case_3_height;
    s32 position_base;
    s32 height0;
    s32 height3;
    s32 height_raw;

    base = object->score;

    if (object->flags & 2) {
        if (sprite->color.c.r != 0) {
            sprite->color.word += 0xFFFEFEFF;
        }
    }

    bits = base->flags;
    base->flags = bits | 2;
    if (object->flags & 1) {
        base->flags = bits | 6;
    }

    func_8003EA54(sprite);

    if (object->flags & 4) {
        if (sprite->frame_entry == shop_panel_sprite_entries) {
            func_80034A1C(sprite, D_8028E214, 0);
        }
    }

    if (sprite->flags & 0x6000) {
        func_80034A1C(sprite, shop_panel_sprite_entries, 0);
    }

    dispatch = object->mode;
    switch (dispatch) {
    case 0:
        value0 = position->z.v;
        if (value0 > 0) {
            i = 3;
            position->z.v = value0 + position->velocity_z;
            case_0_height = 0x80000;
            do {
                i--;
                x = func_80071494() & 0xFF;
                x -= 0x80;
                x <<= 14;
                x += position->x.v;
                random = func_80071494();
                height0 = position->y.v;
                height0 += case_0_height;
                create_object_position_configures_color(0x00808080, x, height0,
                              (random & 0xF) << 16);
            } while (i >= 0);
            break;
        }
        position->z.v = 0;
        position->velocity_z = 0;
        object->mode = 1;
        break;

    case 1:
        if (!(base->flags & 1)) {
            break;
        }
        cell = &town_display_timing_table[base->area * 400] + base->index * 40;
        record = (S_8052EA14_0 *)(cell + (object->column * 12 + 4));
        local.timer = record->unk_08;
        local.velocity_x = record->unk_00;
        local.accel_x = record->unk_04;
        local.mode = 0;
        local.flags = 0;
        local.root = object;
        create_object_initializes_position_sprite(&local, position->y.v, 0);
        break;

    case 2:
        bits = object->timer - 1;
        object->timer = bits;
        if ((s16)bits > 0) {
            break;
        }
        if (object->column == 0) {
            create_value_object(0x5A);
        }
        position->velocity_z = 0x40000;
        object->mode = 3;
        break;

    case 3:
        value = position->z.v;
        if (value <= 0x7FFFFF) {
            next_value = value + position->velocity_z;
            position->z.v = next_value;
            if (next_value <= 0x3FFFFF) {
                i = 3;
                position_base = 0x05600000;
                case_3_height = 0x80000;
                for (; i >= 0; i--) {
                    x = func_80071494() & 0xFF;
                    x -= 0x80;
                    x <<= 14;
                    x += position_base;
                    random = func_80071494();
                    {
                        u32 colour = 0x00808080;
                        s32 pos_x = x;
                        u32 spin = (random & 0xF) << 16;
                        height_raw = position->y.v;
                        height3 = height_raw + case_3_height;
                        create_object_position_configures_color(colour, pos_x, height3, spin);
                    }
                }
            }
        } else {
            object->timer = 2;
            object->mode = 4;
        }
        break;

    case 4:
        bits = object->timer - 1;
        object->timer = bits;
        if ((s16)bits > 0) {
            break;
        }
        func_8023FB18((u8 *)object + 4);
        (*(u16 *)((u8 *)object + (-2))) |= 0x8000;
        scene_object_flags |= 0x8000;
    }

cleanup:
    object->flags &= 0xFFFD;
}
