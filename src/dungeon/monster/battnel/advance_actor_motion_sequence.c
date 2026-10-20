#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);

typedef struct S_80172A04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A04_0;   /* arg0 in advance_actor_motion_sequence */

typedef struct S_80172A04_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A04_2_pre;   /* the 0x14 bytes before obj in advance_actor_motion_sequence, addressed as obj[-1] */

typedef struct S_80172A04_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A04_3;   /* rec in advance_actor_motion_sequence */

   /* arg2 in advance_actor_motion_sequence */


typedef struct S_80172A04_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A04_7;   /* block in advance_actor_motion_sequence */


extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_row_object_group(void *, s16);

extern u8 D_80170E5C[];
extern u8 D_80173D0C[];

/* Advances an actor motion through setup, playback, and completion. */
void advance_actor_motion_sequence(void *state, void *position, void *sprite, EntityRec *actor)
{
    u16 effect_pos[4];
    u8 *motion;
    s16 special_motion;
    void *target;
    s32 ticks_left;
    u8 *action_state;

    special_motion = 0;
    switch (((S_80172A04_0 *)state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                special_motion = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                special_motion = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                special_motion = 1;
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
            ((S_80172A04_0 *)state)->unk_98 &= 0xFF7F;
            {
                s16 use_special = special_motion;
                if (use_special != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    action_state = ((S_80172A04_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((S_80172A04_3 *)action_state)->unk_24;
                    actor->unk_73 = ((S_80172A04_3 *)action_state)->unk_25;
                } else if (D_8006DE24[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_state = ((S_80172A04_2_pre *)target)[-1].unk_00;
                        actor->unk_72 = ((S_80172A04_3 *)action_state)->unk_24;
                        actor->unk_73 = ((S_80172A04_3 *)action_state)->unk_25;
                    }
                } else {
                    actor->target =
                        scan_monster_along_heading(actor, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25,
                                      actor->facing, 0x10);
                    actor->unk_72 = abs(actor->unk_72);
                    actor->unk_73 = abs(actor->unk_73);
                }
            }
            effect_pos[0] = ((u16)((EntityRec *)position)->x.w.i);
            effect_pos[1] = ((u16)((EntityRec *)position)->y.w.i);
            effect_pos[2] = ((u16)((EntityRec *)position)->z.w.i);
            position = (void *)create_actor_spell_effect(actor, motion, special_motion, (u8 *)state + 0x98);
            if (position == 0) {
                return;
            }
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(effect_pos, (*motion - 1) % 3);
            ((S_80172A04_0 *)state)->unk_9B = ((S_80172A04_0 *)state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        set_record_integer_tile_center(position, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172A04_0 *)state)->unk_8C = D_80170E5C;
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
        ((S_80172A04_0 *)state)->unk_9B = ((S_80172A04_0 *)state)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((SpriteAnimationTableView *)sprite)->unk_04 == 4 && (((SpriteAnimationTableView *)sprite)->unk_14 & 0x1000)) ||
            (((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            ((S_80172A04_0 *)state)->unk_96 = 0x6;
            ((S_80172A04_0 *)state)->unk_98 |= 0x80;
        }
        ticks_left = ((S_80172A04_0 *)state)->unk_96 - 1;
        ((S_80172A04_0 *)state)->unk_96 = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((S_80172A04_0 *)state)->unk_96 = 0;
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
            u8 *direction_table = D_80173D0C;

            if (((SpriteAnimationTableView *)sprite)->unk_2C != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&g_dungeon_status.turn_scale;
        if (((S_80172A04_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((S_80172A04_7 *)action_state)->unk_0A = ((S_80172A04_7 *)action_state)->unk_0A - 1;
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172A04_0 *)state)->unk_8C = D_80170E5C;
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
