#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"

typedef struct S_80172810_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172810_0;   /* arg0 in advance_actor_motion_action */

typedef struct S_80172810_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172810_3;   /* rec in advance_actor_motion_action */

   /* arg2 in advance_actor_motion_action */

typedef struct S_80172810_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172810_7;   /* block in advance_actor_motion_action */


extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_row_object_group(void *, s16);

extern int abs(int);
extern u8 D_80170E54[];
extern u8 D_801739C0[];

/* Advances an actor motion through selection, playback, and completion cleanup. */
void advance_actor_motion_action(void *action_state, void *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 saved_position[4];
    u8 *motion;
    s16 use_player;
    void *target;
    s32 offset_x;
    s32 offset_y;
    s32 wait_ticks;
    ObjectNodeHeader *action_globals;

    use_player = 0;
    switch (((S_80172810_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 7:
                use_player = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            ((S_80172810_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 player_target = use_player;
                if (player_target != 0) {
                    target = primary_actor_record;
                    actor->target = target;
                    action_globals = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80172810_3 *)action_globals)->unk_24;
                    actor->target_tile_y = ((S_80172810_3 *)action_globals)->unk_25;
                } else if (item_action_definitions[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_globals = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                        actor->target_tile_x = ((S_80172810_3 *)action_globals)->unk_24;
                        actor->target_tile_y = ((S_80172810_3 *)action_globals)->unk_25;
                    }
                } else {
                    actor->target =
                        scan_actor_along_heading(actor, sprite->unk_24, sprite->unk_25,
                                      actor->facing, 0x10);
                    offset_x = abs(actor->target_tile_x);
                    offset_y = abs(actor->target_tile_y);
                    actor->target_tile_x = offset_x;
                    actor->target_tile_y = offset_y;
                }
            }
            saved_position[0] = ((u16)((EntityRec *)position)->x.w.i);
            saved_position[1] = ((u16)((EntityRec *)position)->y.w.i);
            saved_position[2] = ((u16)((EntityRec *)position)->z.w.i);
            position = (void *)create_actor_spell_effect(actor, motion, use_player, (u8 *)action_state + 0x98);
            if (position == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(saved_position, (*motion - 1) % 3);
            ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        set_record_integer_tile_center(position, sprite->unk_24, sprite->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4 + 2)) = (*(u16 *)((u8 *)primary_actor_record + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
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
        ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((sprite->unk_04 == 14 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            ((S_80172810_0 *)action_state)->unk_96 = 0x3;
            ((S_80172810_0 *)action_state)->unk_98 |= 0x80;
        }
        wait_ticks = ((S_80172810_0 *)action_state)->unk_96 - 1;
        ((S_80172810_0 *)action_state)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((S_80172810_0 *)action_state)->unk_96 = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        set_record_integer_tile_center(position, sprite->unk_24, sprite->unk_25);
        {
            u8 *direction_frames = D_801739C0;

            if (*(unsigned char **)&sprite->frameTable != direction_frames) {
                (sprite->frameTable) = direction_frames;
                select_sprite_entry(sprite,
                    direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_globals = (u8 *)&g_dungeon_status.turn_scale;
        if (*(s32 *)&action_globals->sprite != 0) {
            return;
        }
        ((S_80172810_7 *)action_globals)->unk_0A = ((S_80172810_7 *)action_globals)->unk_0A - 1;
        sprite->flags &= 0xF7FF;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(0xB4);
        break;
    }
}
