#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/object.h"

typedef struct {
    u8 pad_00[0x8C];
    void *field_8C;
    u8 pad_90[6];
    u16 field_96;
    u16 field_98;
    u8 pad_9A;
    u8 state;
} D0;

typedef struct {
    u8 pad_00[4];
    s8 kind;
    u8 pad_05[0x0F];
    u16 flags;
    u8 pad_16[0x0E];
    u8 value_24;
    u8 value_25;
    u8 pad_26[6];
    void *field_2C;
} D2;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
    u8 pad_18[0x12];
    s16 value_2A;
    u8 pad_2C[0x1A];
    u16 value_46;
    u8 pad_48[0x18];
    void *field_60;
} D3;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
} D3Nested;

extern u8 cyclone_move_direction_frames[8];

extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(D3 *, s32);
struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);
extern void create_directional_target_object(D0 *, void *, SpriteFrameState *);
extern void format_entity_message(s32, D3 *);

/* Advances a timed actor state sequence and updates its sprite direction. */
void advance_timed_actor_state_sequence(D0 *action, ObjectPosition *position, SpriteFrameState *sprite, D3 *actor) {
    u16 sprite_flags;
    u16 ticks_left;

    switch (action->state) {
    case 0:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            sprite->flags = sprite_flags | 0x6000;
            action->state = 2;
            return;
        }
        if (!(sprite->unk_04 == 1 && (sprite_flags & 0x1000)) && (sprite_flags & 0x6000) == 0) {
            break;
        }
        create_directional_target_object(action, position, sprite);
        if (actor->flags & 0x4000) {
            format_entity_message(1, actor);
        } else if (((D3Nested *) actor->field_60)->flags & 0x4000) {
            format_entity_message(0, actor);
        }
        play_sound_if_enabled(0x80D);
        action->field_96 = 0x20;
        action->state = action->state + 1;
        break;

    case 1:
        ticks_left = action->field_96 - 1;
        action->field_96 = ticks_left;
        if ((ticks_left << 16) != 0) {
            if (!(sprite->flags & 0x8000)) {
                break;
            }
        }
        action->field_96 = 4;
        action->state = action->state + 1;
        break;

    case 2:
        ticks_left = action->field_96 - 1;
        action->field_96 = ticks_left;
        if ((ticks_left << 16) != 0) {
            if (!(sprite->flags & 0xE000)) {
                return;
            }
        }
        spend_actor_mp(actor, 0x400);
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        action->field_8C = update_actor_animation;
        g_dungeon_status.active_actor = 0;
        actor->value_46 &= 0x7FFF;
        break;
    }

    if (sprite->flags & 0xE000) {
        sprite->frameTable = cyclone_move_direction_frames;
        select_sprite_entry(sprite, cyclone_move_direction_frames[(((g_game_work.view.camera_rotation.parts.viewAngle + actor->value_2A + 0x100) >> 9) & 7)], 0);
        action->field_98 &= 0xFFF7;
    }

    return;
}
