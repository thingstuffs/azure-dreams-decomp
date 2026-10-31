#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor/callback.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "shared/object_node.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"


typedef s32 M2C_UNK;



extern void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);

extern void create_actor_linked_effect(void *);
extern void * create_offset_actor_object(ActorRecord *, ObjectPosition *, SpriteFrameState *);

extern void golem_action_continuation_address(void *, void *, void *, void *);
extern u8 golem_direction_frames[8];

   /* entity in advance_actor_item_use_sequence */

typedef struct S_801738B4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801738B4_4;   /* global in advance_actor_item_use_sequence */

/* Advances an actor's item-use sequence and resets its state when the action ends. */
void advance_actor_item_use_sequence(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *item;
    s32 special_mode;
    s32 action_state;
    s32 item_selector;
    u16 remaining_ticks;
    s32 target_x;
    s32 target_y;
    void *active_object;
    void *copy_object;
    u8 *action_status;
    s32 use_shared_object;

    special_mode = 0;
    action_state = body->action_phase.u;
    switch (action_state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            item_selector = (actor->action_flags & 0x3FFF) - 1;
            switch (item_selector) {
            case 6:
                special_mode = 1;
                /* fall through */
            case 2:
                item = (u8 *)actor + 0x0E;
                break;
            case 5:
                special_mode = 1;
                /* fall through */
            case 1:
                item = (u8 *)actor + 0x0B;
                break;
            case 4:
                special_mode = 1;
                /* fall through */
            case 0:
                item = (u8 *)actor;
                item += 8;
                break;
            default:
                item = 0;
                break;
            }
        } else {
            item_selector = actor->action_flags & 0x3FFF;
            switch (item_selector) {
            case 3:
                item = (u8 *)actor + 0x0E;
                break;
            case 2:
                item = (u8 *)actor + 0x0B;
                break;
            case 1:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        }

        if (*item != 0) {

            body->action_state_flags &= 0xFF7F;
            use_shared_object = (special_mode == 1);
            if (use_shared_object) {
                copy_object = primary_actor_record;
                actor->target = copy_object;
                action_status = *(u8 * *)&((ObjectNodeHeader *)((u8 *)copy_object - 0x20))->sprite;
                actor->target_tile_x = action_status[0x24];
                actor->target_tile_y = action_status[0x25];
            } else if (item_action_definitions[*item].kind == 2) {
                copy_object = actor->target;
                if (copy_object != 0) {
                    action_status = *(u8 * *)&((ObjectNodeHeader *)((u8 *)copy_object - 0x20))->sprite;
                    actor->target_tile_x = action_status[0x24];
                    actor->target_tile_y = action_status[0x25];
                }
            } else {
                target_x = (s32)scan_actor_along_heading(actor,
                    sprite->tile_x,
                    sprite->tile_y,
                    actor->facing, 0x10);
                actor->target = (void *)target_x;
                target_x = __builtin_abs(actor->target_tile_x);
                target_y = __builtin_abs(actor->target_tile_y);
                actor->target_tile_x = target_x;
                actor->target_tile_y = target_y;
            }
            if (create_actor_spell_effect(actor, item, special_mode, &body->action_state_flags)) {
                create_actor_linked_effect(actor);
                body->action_phase.u++;
            }
            break;
        } else {
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            active_object = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
            advance_status_timers(actor);
            (*((u8 *)actor + 0x6D))--;
            body->unk_8C.run = &golem_action_continuation_address;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= 0x7FFF;
            break;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            break;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase.u++;

    case 2:
        if ((sprite->unk_04 == 3 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            create_offset_actor_object(body, position, sprite);
            body->action_phase.u++;
        }

    case 3:
        if ((sprite->unk_04 == 4 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x0800;
            body->action_timer.u = 1;
            body->action_state_flags |= 0x0080;
        }

        remaining_ticks = body->action_timer.u - 1;
        body->action_timer.u = remaining_ticks;
        if ((s16)remaining_ticks <= 0) {
            body->action_timer.u = 0;
            sprite->flags &= 0xF7FF;
        }
        if (!(sprite->flags & 0xE000)) {
            break;
        }

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        if (*(unsigned char **)&sprite->frameTable != golem_direction_frames) {
            (sprite->frameTable) = golem_direction_frames;
            select_sprite_entry(sprite,
                golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }

        action_status = (u8 *)&g_dungeon_status.turn_scale;
        if (((ObjectNodeHeader *)action_status)->sprite != 0) {
            break;
        }
        ((S_801738B4_4 *)action_status)->unk_0A--;
        body->unk_8C.run = &golem_action_continuation_address;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        (*((u8 *)actor + 0x6D))--;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

    }

    return;
}
