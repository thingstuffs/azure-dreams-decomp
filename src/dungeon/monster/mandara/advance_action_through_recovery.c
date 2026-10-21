#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172DEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172DEC_0;   /* arg0 in advance_action_through_recovery */

typedef struct S_80172DEC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172DEC_2_pre;   /* the 0x14 bytes before obj in advance_action_through_recovery, addressed as obj[-1] */

typedef struct S_80172DEC_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172DEC_3;   /* rec in advance_action_through_recovery */

extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_effect_groups(void *, void *, void *, s32);

extern u8 D_80170F6C[];
extern u8 D_80175258[];

/* Advances an actor action through motion selection, execution, and recovery. */
void advance_action_through_recovery(void *action_state, ObjectPosition *transform, void *sprite, ActorRecord *actor)
{
    u16 saved_position[3];
    u8 *motion;
    s32 use_global_target;
    void *target;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    s32 ticks_left;

    use_global_target = 0;
    switch (((S_80172DEC_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                use_global_target = 1;
                /* fall through */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                use_global_target = 1;
                /* fall through */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                use_global_target = 1;
                /* fall through */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
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
            ((S_80172DEC_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 global_target_flag = use_global_target;

                if (global_target_flag != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    target_y = ((S_80172DEC_2_pre *)target)[-1].unk_00;
                    actor->target_tile_x = ((S_80172DEC_3 *)target_y)->unk_24;
                    actor->target_tile_y = ((S_80172DEC_3 *)target_y)->unk_25;
                } else if (D_8006DE24[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        target_y = ((S_80172DEC_2_pre *)target)[-1].unk_00;
                        actor->target_tile_x = ((S_80172DEC_3 *)target_y)->unk_24;
                        actor->target_tile_y = ((S_80172DEC_3 *)target_y)->unk_25;
                    }
                } else {
                    actor->target =
                        scan_monster_along_heading(actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                                      actor->facing, 0x10);
                    abs_x = abs(actor->target_tile_x);
                    abs_y = abs(actor->target_tile_y);
                    actor->target_tile_x = abs_x;
                    actor->target_tile_y = abs_y;
                }
            }
            saved_position[0] = ((u16)transform->x.w.i);
            saved_position[1] = ((u16)transform->y.w.i);
            saved_position[2] = ((u16)transform->z.w.i);
            if (create_actor_spell_effect(actor, motion, use_global_target, (u8 *)action_state + 0x98) == 0) {
                return;
            }
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_effect_groups(transform, sprite, actor, 0x10);
            ((S_80172DEC_0 *)action_state)->unk_9B = ((S_80172DEC_0 *)action_state)->unk_9B + 1;
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_80172DEC_0 *)action_state)->unk_9B = ((S_80172DEC_0 *)action_state)->unk_9B + 1;
                                        /* fallthrough */
    case 2:
        if ((((SpriteFrameState *)sprite)->unk_04 == 3 && (((SpriteFrameState *)sprite)->flags & 0x1000))
            ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((S_80172DEC_0 *)action_state)->unk_96 = 0xE;
            ((S_80172DEC_0 *)action_state)->unk_98 |= 0x80;
        }
        ticks_left = ((S_80172DEC_0 *)action_state)->unk_96 - 1;
        ((S_80172DEC_0 *)action_state)->unk_96 = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((S_80172DEC_0 *)action_state)->unk_96 = 0;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        }
        if ((((SpriteFrameState *)sprite)->flags & 0xE000) == 0) {
            return;
        }
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        {
            u8 *direction_table = D_80175258;

            if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != direction_table) {
                ((SpriteFrameState *)sprite)->frameTable = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_80172DEC_0 *)action_state)->unk_8C = D_80170F6C;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}
