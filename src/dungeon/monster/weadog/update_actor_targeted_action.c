#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
#include "shared/dungeon_moving_views.h"
extern int abs(int);

typedef s32 Any;

typedef struct S_801737B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737B0_0;   /* arg0 in update_actor_targeted_action */

   /* the 0x14 bytes before ptr in update_actor_targeted_action, addressed as ptr[-1] */

   /* desc in update_actor_targeted_action */

extern u8 D_80171CE8[];
extern u8 D_80174EB8[];

extern s32 get_cd_command_queue_depth();
extern Any select_sprite_entry();
extern s32 func_80069EF8();
extern void *scan_monster_along_heading();
extern Any set_record_integer_tile_center();
extern Any advance_status_timers();
extern Any play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern Any create_random_color_offset_effect();

/* Updates an actor action through targeting, particle effects, and recovery. */
/* Starts a targeted spell, emits three randomly colored offset effects per casting tick, then restores
 * idle and status. */
void update_actor_targeted_action(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor) {
    s32 use_player_target;
    s32 particle_count;
    s32 offset_z;
    s32 direction;
    s32 action_kind;
    s32 particle_zero;
    s32 particle_color;
    s32 offset_x;
    s32 offset_y;
    u16 timer;
    u16 sprite_flags;
    u16 raw_kind;
    u32 kind_index;
    u8 state;
    u8 *action_data;
    u8 *particle_origin;

    state = ((S_801737B0_0 *)action)->unk_9B;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            raw_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            kind_index = raw_kind - 1;
            switch (kind_index) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                action_data = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                action_data = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            action_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action_kind) {
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

            direction = ((S_801737B0_0 *)action)->unk_98;
            direction &= 0xFF7F;
            ((S_801737B0_0 *)action)->unk_98 = direction;
            direction = use_player_target;
            if (((void *)direction) != 0) {
                direction = (s32)primary_actor_record;
                actor->target = (void *)direction;
                {
                    u8 facing;

                    action_kind = (s32)(((ActorLinkPrefixView *)((void *)direction))[-1].unk_00);
                    facing = ((MovingTile *)((u8 *)action_kind))->unk_24;
                    actor->target_tile_x = facing;
                    facing = ((MovingTile *)((u8 *)action_kind))->unk_25;
                    actor->target_tile_y = facing;
                }
            } else if (item_action_definitions[*action_data].kind == 2) {
                direction = (s32)(actor->target);
                if (((void *)direction) != 0) {
                    {
                        u8 facing;

                        action_kind = (s32)(((ActorLinkPrefixView *)((void *)direction))[-1].unk_00);
                        facing = ((MovingTile *)((u8 *)action_kind))->unk_24;
                        actor->target_tile_x = facing;
                        facing = ((MovingTile *)((u8 *)action_kind))->unk_25;
                        actor->target_tile_y = facing;
                    }
                }
            } else {

                actor->target = scan_monster_along_heading(
                    actor,
                    ((SpriteFrameState *)sprite)->unk_24,
                    ((SpriteFrameState *)sprite)->unk_25,
                    actor->facing,
                    0x10);

                actor->target_tile_x = abs(actor->target_tile_x);
                actor->target_tile_y = abs(actor->target_tile_y);
            }

            if (create_actor_spell_effect(actor, action_data, use_player_target, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_801737B0_0 *)action)->unk_9B++;
            return;

        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        actor->pending_turn_updates--;
        ((S_801737B0_0 *)action)->unk_8C = D_80171CE8;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_801737B0_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        sprite_flags = ((SpriteFrameState *)sprite)->flags;
        if (sprite_flags & 0x8000) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((S_801737B0_0 *)action)->unk_9B++;
            ((S_801737B0_0 *)action)->unk_98 |= 0x80;
            return;
        }

        if ((((SpriteFrameState *)sprite)->unk_04 == 2) && (sprite_flags & 0x1000)) {
            ((SpriteFrameState *)sprite)->flags = sprite_flags | 0x800;
            ((S_801737B0_0 *)action)->unk_96.s = 0x16;
        }
        if (((SpriteFrameState *)sprite)->unk_04 < 2) {
            return;
        }

        timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
        ((S_801737B0_0 *)action)->unk_96.s = timer;
        if ((s16)timer <= 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((S_801737B0_0 *)action)->unk_9B++;
        }
        if (((S_801737B0_0 *)action)->unk_96.u == 2) {
            ((S_801737B0_0 *)action)->unk_98 |= 0x80;
        }
        if (((S_801737B0_0 *)action)->unk_96.u < 0xA) {
            return;
        }

        particle_count = 0;
        do {
            particle_count++;
            offset_x = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_y = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_z = func_80069EF8();
            particle_origin = (u8 *)action - 0x20;
            particle_zero = 0;
            particle_color = 0xC0C0C0;
            offset_z = (s16)((offset_z & 0x3F) - 0x20);
            create_random_color_offset_effect(
                particle_origin,
                particle_zero,
                particle_color,
                (s16)(((S_801737B0_0 *)action)->unk_96.s - 2),
                offset_x,
                offset_y,
                offset_z);
            if ((u32)(particle_count & 0xFFFF) >= 3U) {
                return;
            }
        } while (1);

    case 3:
        ((S_801737B0_0 *)action)->unk_96.s = 0x14;
        ((S_801737B0_0 *)action)->unk_9B++;

    case 4:
        if (((s32)g_dungeon_status.active_actor) == 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
        }
        timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
        ((S_801737B0_0 *)action)->unk_96.s = timer;
        if ((s16)timer <= 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        }
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);

        if (((SpriteFrameState *)sprite)->frameTable != D_80174EB8) {
            ((SpriteFrameState *)sprite)->frameTable = D_80174EB8;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, D_80174EB8[direction], 0);
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((S_801737B0_0 *)action)->unk_8C = D_80171CE8;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates--;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(0xB4);
    }
}
