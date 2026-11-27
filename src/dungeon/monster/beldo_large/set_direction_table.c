/* Encounter direction tables and timed effect sequences. */
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/object.h"
#include "dungeon/effect/particle.h"
#include "dungeon/system.h"
#include "dungeon/data.h"
#include "dungeon/monster/beldo_large_frames.h"

typedef union {
    u16 unsigned_value;
    s16 signed_value;
} DungeonTimer;

typedef struct {
    u8 pad_00[0x8C];
    u8 *action_handler;
    u8 pad_90[6];
    DungeonTimer timer;
    u8 pad_98[3];
    u8 state;
    u8 pad_9C[0x10];
    u8 mode;
} DungeonState;

typedef struct {
    u8 pad_00[0x0C];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
} DungeonWork;

typedef struct {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0x0E];
    u8 tile_x;
    u8 tile_y;
    u8 pad_26[6];
    u8 *frame_table;
} DungeonObject;

typedef struct {
    u8 pad_00[0x2A];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 action_flags;
    u8 pad_48[0x2A];
    u8 target_tile_x;
    u8 target_tile_y;
} DungeonInput;

extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

struct SpriteFrameState;
extern void create_targeted_ribbon_trail(DungeonState *, DungeonWork *, DungeonObject *, u8 *, s32);

/*
 * Installs the supplied sprite table and selects its eight-way entry using the input facing
 * relative to the camera.
 */
static __inline__ void set_direction_table(SpriteFrameState *object, DungeonInput *input, u8 *table) {
    u32 direction_index;

    object->frameTable = table;
    direction_index = ((s32)(g_game_work.view.camera_rotation.parts.viewAngle + input->facing + 0x100) >> 9) & 7;
    select_sprite_entry(object, *((u8 *)((u32)direction_index + (unsigned long)table)), 0);
}

/* Advance the timed dungeon object sequence and update its direction table. */
void advance_beldo_large_pose_sequence(DungeonState *state, DungeonWork *work,
                   DungeonObject *object, DungeonInput *input) {
    u32 state_index;
    state_index = state->state;
    switch (state_index) {
    case 1:
    {
        s32 mode;
        mode = state->mode;
        switch (mode) {
        case 0:
            set_direction_table(object, input, beldo_large_frame_set_6);
            break;
        case 1:
            set_direction_table(object, input, beldo_large_frame_set_17);
            break;
        case 2:
            set_direction_table(object, input, beldo_large_frame_set_18);
            break;
        case 3:
            set_direction_table(object, input, beldo_large_frame_set_6 + 0x18);
            break;
        }
    }
        create_layered_sprite_pulse(work);
        state->timer.unsigned_value = 6;
        state->state = state->state + 1;
        play_sound_if_enabled(0x703);
        return;

    case 2:
    {
        u16 timer;

        timer = state->timer.unsigned_value - 1;
        state->timer.unsigned_value = timer;
        if ((timer << 16) <= 0 || (object->flags & 0xE000))
            goto case0;
        return;
    }

    case 3:
    {
        u16 timer;
        s16 current_timer;

        timer = state->timer.unsigned_value + 1;
        state->timer.unsigned_value = timer;
        if ((s16)timer == 1) {
            create_targeted_ribbon_trail(state, work, object, ((u8 *)(&view_reference_entity)), 0);
            current_timer = state->timer.signed_value;
            if (current_timer == (s16)timer) {
                create_targeted_ribbon_trail(state, work, object, ((u8 *)(&view_reference_entity)), current_timer);
                if (state->timer.signed_value == current_timer)
                    create_targeted_ribbon_trail(state, work, object, ((u8 *)(&view_reference_entity)), 2);
            }
        }
        if (state->timer.signed_value == 0xB) {
            state->timer.unsigned_value = 0;
            state->state = state->state + 1;
        }
        return;
    }

    case 4:
    {
        s32 mode;
        u8 *direction_table;
        u8 *previous_table;

        if (!(object->flags & 0xE000))
            return;
        work->velocity_z = 0;
        work->velocity_y = 0;
        work->velocity_x = 0;
        set_record_integer_tile_center(work, object->tile_x, object->tile_y);
        mode = state->mode;
        switch (mode) {
        case 0:
            previous_table = object->frame_table;
            direction_table = beldo_large_frame_set_2;
            break;
        case 1:
            previous_table = object->frame_table;
            direction_table = beldo_large_frame_set_5;
            break;
        case 2:
            previous_table = object->frame_table;
            direction_table = beldo_large_frame_set_1;
            break;
        case 3:
            previous_table = object->frame_table;
            direction_table = beldo_large_frame_set_2 + 0x18;
            break;
        default:
            goto case0;
        }
        if (previous_table != direction_table) {
            set_direction_table(object, input, direction_table);
        }
        state->timer.unsigned_value = 0;
        state->state = state->state + 1;
        return;
    }

    case 5:
    {
        u16 timer;

        timer = state->timer.unsigned_value;
        state->timer.unsigned_value = timer + 1;
        if ((s16)timer < 0x3C)
            return;
    }

case0:
    case 0:
        state->timer.unsigned_value = 0;
        state->state = state->state + 1;
        return;

    case 6:
        input->target_tile_y = 0;
        input->target_tile_x = 0;
        state->action_handler = beldo_large_action_resume_address;
        g_dungeon_status.active_actor = 0;
        input->action_flags = input->action_flags & 0x7FFF;

        return;
    }
}
