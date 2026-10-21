#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);

typedef struct S_80172AB4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172AB4_0;   /* arg0 in update_actor_move_animation_and_recovery */

typedef struct S_80172AB4_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172AB4_1;   /* arg3 in update_actor_move_animation_and_recovery */

typedef struct S_80172AB4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172AB4_2_pre;   /* the 0x14 bytes before object in update_actor_move_animation_and_recovery, addressed as object[-1] */

typedef struct S_80172AB4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AB4_3;   /* record in update_actor_move_animation_and_recovery */

   /* arg2 in update_actor_move_animation_and_recovery */

typedef struct S_80172AB4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172AB4_5;   /* arg1 in update_actor_move_animation_and_recovery */

typedef struct S_80172AB4_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172AB4_6;   /* globals in update_actor_move_animation_and_recovery */


extern s32 get_cd_command_queue_depth();
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_two_row_object_group(void *payload, s16 value_scale);

extern u8 D_80170E7C;
extern u8 D_80174D4C[];
extern u8 D_80174D94[];
extern u8 D_80174D9C[];
extern u8 D_80174DA4[];

/* Updates the actor's move, animation, and recovery state. */
void update_actor_move_animation_and_recovery(void *action, void *motion, void *sprite, void *actor)
{
    u8 *move_id;
    s32 state;
    s16 use_player;
    s32 move_kind;
    void *target;
    s32 target_x;
    u16 position[3];
    u16 ticks_left;


    state = ((S_80172AB4_0 *)action)->unk_9B;
    use_player = 0;
    switch (state) {
    case 0:
        if (((S_80172AB4_1 *)actor)->unk_1C & 0x2000) {
            move_kind = (((S_80172AB4_1 *)actor)->unk_46 & 0x3FFF) - 1;
            switch (move_kind) {
            case 6:
                use_player = 1;
            case 2:
                move_id = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                move_id = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                move_id = (u8 *)actor + 8;
                break;
            default:
                move_id = 0;
                break;
            }
        } else {
            move_kind = ((S_80172AB4_1 *)actor)->unk_46 & 0x3FFF;
            switch (move_kind) {
            case 3:
                move_id = (u8 *)actor + 0xE;
                break;
            case 2:
                move_id = (u8 *)actor + 0xB;
                break;
            case 1:
                move_id = (u8 *)actor + 8;
                break;
            default:
                move_id = 0;
                break;
            }
        }
        if (*move_id != 0) {
            ((S_80172AB4_0 *)action)->unk_98 &= 0xFF7F;
            if (use_player != 0) {
                target = primary_actor_record;
                ((S_80172AB4_1 *)actor)->unk_60 = target;
                move_kind = (s32)((S_80172AB4_2_pre *)target)[-1].unk_00;
                ((S_80172AB4_1 *)actor)->unk_72.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_24;
                ((S_80172AB4_1 *)actor)->unk_73.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_25;
            } else if (item_action_definitions[*move_id].kind == 2) {
                target = ((S_80172AB4_1 *)actor)->unk_60;
                if (target != 0) {
                    move_kind = (s32)((S_80172AB4_2_pre *)target)[-1].unk_00;
                    ((S_80172AB4_1 *)actor)->unk_72.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_24;
                    ((S_80172AB4_1 *)actor)->unk_73.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_25;
                }
            } else {
                ((S_80172AB4_1 *)actor)->unk_60 =
                    scan_monster_along_heading(actor,
                                  ((SpriteAnimationTableView *)sprite)->unk_24,
                                  ((SpriteAnimationTableView *)sprite)->unk_25,
                                  ((S_80172AB4_1 *)actor)->unk_2A, 0x10);
                ((S_80172AB4_1 *)actor)->unk_72.s = abs(((S_80172AB4_1 *)actor)->unk_72.u);
                ((S_80172AB4_1 *)actor)->unk_73.s = abs(((S_80172AB4_1 *)actor)->unk_73.u);
            }

            position[0] = ((S_80172AB4_5 *)motion)->unk_02;
            position[1] = ((S_80172AB4_5 *)motion)->unk_06;
            position[2] = ((S_80172AB4_5 *)motion)->unk_0A;
            if (create_actor_spell_effect(actor, move_id, use_player,
                              (u16 *)((u8 *)action + 0x98)) == 0) {
                return;
            }
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(position, (s16)(((s32)*move_id - 1) % 3));
            ((S_80172AB4_0 *)action)->unk_9B++;
            return;
        }

        ((S_80172AB4_5 *)motion)->unk_14 = 0;
        ((S_80172AB4_5 *)motion)->unk_10 = 0;
        ((S_80172AB4_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        ((S_80172AB4_1 *)actor)->unk_6D.s--;
        ((S_80172AB4_0 *)action)->unk_8C = &D_80170E7C;
        ((S_80172AB4_1 *)actor)->unk_73.s = 0;
        ((S_80172AB4_1 *)actor)->unk_72.s = 0;
        ((S_80172AB4_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (((SpriteAnimationTableView *)sprite)->unk_14 & 0x8000) {
            ((S_80172AB4_0 *)action)->unk_9B = 3;
            return;
        }
        if (!(((SpriteAnimationTableView *)sprite)->unk_14 & 0x6000)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D9C;
        select_sprite_entry(
            sprite,
            D_80174D9C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172AB4_0 *)action)->unk_98 |= 8;
        ((S_80172AB4_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        ((S_80172AB4_0 *)action)->unk_96 = 8;
        ((S_80172AB4_5 *)motion)->unk_14 = 0xFFF00000;
        ((S_80172AB4_0 *)action)->unk_9B++;
        return;

    case 2:
        ((S_80172AB4_5 *)motion)->unk_14 += 0x10000;
        ticks_left = ((S_80172AB4_0 *)action)->unk_96 - 1;
        ((S_80172AB4_0 *)action)->unk_96 = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174DA4;
        select_sprite_entry(
            sprite,
            D_80174DA4[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172AB4_5 *)motion)->unk_14 = 0;
        ((S_80172AB4_0 *)action)->unk_9B++;
        return;

    case 3:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172AB4_0 *)action)->unk_9B++;

    case 4:
        if (!(((((SpriteAnimationTableView *)sprite)->unk_04 == 1) &&
               (((SpriteAnimationTableView *)sprite)->unk_14 & 0x1000)) ||
              (((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000))) {
            return;
        }
        ((S_80172AB4_0 *)action)->unk_96 = 3;
        ((S_80172AB4_0 *)action)->unk_98 |= 0x80;
        if (!(((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D9C;
        select_sprite_entry(
            sprite,
            D_80174D9C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172AB4_0 *)action)->unk_98 &= 0xFFF7;
        ((S_80172AB4_1 *)actor)->unk_1C |= 0x08000000;

        ((S_80172AB4_0 *)action)->unk_9B++;
        return;

    case 5:
        if (!(((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D94;
        select_sprite_entry(
            sprite,
            D_80174D94[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172AB4_0 *)action)->unk_9B = 0xFF;
        return;

    case 0xFF:
        if (!(((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_80172AB4_5 *)motion)->unk_14 = 0;
        ((S_80172AB4_5 *)motion)->unk_10 = 0;
        ((S_80172AB4_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteAnimationTableView *)sprite)->unk_24, ((SpriteAnimationTableView *)sprite)->unk_25);
        if (((SpriteAnimationTableView *)sprite)->unk_2C != D_80174D4C) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D4C;
            select_sprite_entry(
                sprite,
                D_80174D4C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172AB4_0 *)action)->unk_8C = &D_80170E7C;
        advance_status_timers(actor);
        if (((S_80172AB4_1 *)actor)->unk_6D.u > 0) {
            ((S_80172AB4_1 *)actor)->unk_6D.s--;
        }
        ((S_80172AB4_1 *)actor)->unk_73.s = 0;
        ((S_80172AB4_1 *)actor)->unk_72.s = 0;
        ((S_80172AB4_1 *)actor)->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    }
}
