#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172834_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172834_0;   /* arg0 in update_jump_motion_2 */

typedef struct S_80172834_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172834_3;   /* record in update_jump_motion_2 */

extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_two_row_object_group(u16 *, s32);

extern u8 D_80171058[];
extern u8 D_80174888[];

/* Starts the selected actor action, waits for completion, and resets its state. */
void update_jump_motion_2(void *action_state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *action_data;
    s32 phase;
    s32 is_special;
    void *target;
    s16 x;
    s32 y;
    u16 position[3];

    phase = ((S_80172834_0 *)action_state)->unk_9B;
    is_special = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 7:
                is_special = 1;
            case 3:
                action_data = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
            case 2:
                action_data = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
            case 1:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                action_data = (u8 *)actor + 0xE;
                break;
            case 2:
                action_data = (u8 *)actor + 0xB;
                break;
            case 1:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {
            x = ((S_80172834_0 *)action_state)->unk_98;
            x &= 0xFF7F;
            ((S_80172834_0 *)action_state)->unk_98 = x;
            x = is_special;
            if (x != 0) {
                target = primary_actor_record;
                actor->target = target;
                phase = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                actor->target_tile_x = ((S_80172834_3 *)phase)->unk_24;
                actor->target_tile_y = ((S_80172834_3 *)phase)->unk_25;
            } else if (item_action_definitions[*action_data].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    phase = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80172834_3 *)phase)->unk_24;
                    actor->target_tile_y = ((S_80172834_3 *)phase)->unk_25;
                }
            } else {
                actor->target =
                    scan_actor_along_heading(actor,
                                  sprite->unk_24,
                                  sprite->unk_25,
                                  actor->facing, 0x10);
                {
                    s32 abs_x = abs(actor->target_tile_x);
                    s32 abs_y = abs(actor->target_tile_y);
                    actor->target_tile_x = abs_x;
                    actor->target_tile_y = abs_y;
                }
            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, action_data, is_special,
                              (u16 *)((u8 *)action_state + 0x98)) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            create_two_row_object_group(position, (s16)(((s32)*action_data - 1) % 3));
            play_sound_if_enabled(0x703);
            ((S_80172834_0 *)action_state)->unk_9B++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        ((S_80172834_0 *)action_state)->unk_8C = D_80171058;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80172834_0 *)action_state)->unk_9B++;

    case 2:
        if (!((sprite->unk_04 == 3) &&
              (sprite->flags & 0x1000)) &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        ((S_80172834_0 *)action_state)->unk_98 |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        if (*(u8 * *)&sprite->frameTable != D_80174888) {
            sprite->frameTable = D_80174888;
            select_sprite_entry(
                sprite,
                D_80174888[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        sprite->flags &= 0xF7FF;
        ((S_80172834_0 *)action_state)->unk_8C = D_80171058;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(0xB4);

        return;
    default:
        return;
    }
}
