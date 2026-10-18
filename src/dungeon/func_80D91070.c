#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);

typedef struct S_80172870_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172870_0;   /* arg0 in advance_actor_motion_and_reset_action */

typedef struct S_80172870_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172870_2_pre;   /* the 0x14 bytes before obj in advance_actor_motion_and_reset_action, addressed as obj[-1] */

typedef struct S_80172870_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172870_3;   /* rec in advance_actor_motion_and_reset_action */

   /* arg2 in advance_actor_motion_and_reset_action */


typedef struct S_80172870_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172870_7;   /* block in advance_actor_motion_and_reset_action */


extern s32 get_cd_command_queue_depth(void);
extern void func_80047784(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_80170E68[];
extern u8 D_8017386C[];

/* Advances actor motion, waits for completion, and resets the action state. */
void advance_actor_motion_and_reset_action(void *action_state, void *position, void *sprite, EntityRec *actor)
{
    u16 saved_position[3];
    u8 *motion;
    s16 special_mode;
    void *target;
    s32 wait_frames;
    u8 *action_counters;

    special_mode = 0;
    switch (((S_80172870_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                special_mode = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                special_mode = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                special_mode = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
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
            ((S_80172870_0 *)action_state)->unk_98 &= 0xFF7F;
            if (special_mode != 0) {
                target = D_800814A8;
                actor->target = target;
                action_counters = ((S_80172870_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172870_3 *)action_counters)->unk_24;
                actor->unk_73 = ((S_80172870_3 *)action_counters)->unk_25;
            } else if (D_8006DE24[*motion].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    action_counters = ((S_80172870_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((S_80172870_3 *)action_counters)->unk_24;
                    actor->unk_73 = ((S_80172870_3 *)action_counters)->unk_25;
                }
            } else {
                actor->target =
                    scan_monster_along_heading(actor, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25,
                                  actor->facing, 0x10);
                actor->unk_72 = abs(actor->unk_72);
                actor->unk_73 = abs(actor->unk_73);
            }
            saved_position[0] = ((u16)((EntityRec *)position)->x.w.i);
            saved_position[1] = ((u16)((EntityRec *)position)->y.w.i);
            saved_position[2] = ((u16)((EntityRec *)position)->z.w.i);
            position = (void *)create_actor_spell_effect(actor, motion, special_mode, (u8 *)action_state + 0x98);
            if (position == 0) {
                return;
            }
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            ((S_80172870_0 *)action_state)->unk_9B = ((S_80172870_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        set_record_integer_tile_center(position, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25);
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172870_0 *)action_state)->unk_8C = D_80170E68;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172870_0 *)action_state)->unk_9B = ((S_80172870_0 *)action_state)->unk_9B + 1;
                        /* fallthrough */
    case 2:
        if ((((SpriteAnimationTableView *)sprite)->unk_04 == 5 && (((SpriteAnimationTableView *)sprite)->unk_14 & 0x1000)) ||
            (((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            ((S_80172870_0 *)action_state)->unk_96 = 0x20;
            ((S_80172870_0 *)action_state)->unk_98 |= 0x80;
        }
        wait_frames = ((S_80172870_0 *)action_state)->unk_96 - 1;
        ((S_80172870_0 *)action_state)->unk_96 = wait_frames;
        if ((s16)wait_frames <= 0) {
            ((S_80172870_0 *)action_state)->unk_96 = 0;
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        set_record_integer_tile_center(position, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25);
        {
            u8 *direction_anims = D_8017386C;

            if (((SpriteAnimationTableView *)sprite)->unk_2C != direction_anims) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_anims;
                func_80047784(sprite,
                    direction_anims[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_counters = (u8 *)&g_dungeon_status.unk_00;
        if (((S_80172870_7 *)action_counters)->unk_0C != 0) {
            return;
        }
        ((S_80172870_7 *)action_counters)->unk_0A = ((S_80172870_7 *)action_counters)->unk_0A - 1;
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172870_0 *)action_state)->unk_8C = D_80170E68;
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}
