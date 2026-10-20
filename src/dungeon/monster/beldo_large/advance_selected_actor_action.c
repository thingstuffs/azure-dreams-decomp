#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_links.h"

typedef struct S_8016C190_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016C190_0;   /* arg0 in advance_selected_actor_action */

   /* the 0x14 bytes before v0 in advance_selected_actor_action, addressed as v0[-1] */

typedef struct S_8016C190_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016C190_3;   /* arg2 in advance_selected_actor_action */


typedef struct S_8016C190_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8016C190_5;   /* control in advance_selected_actor_action */


extern s32 get_cd_command_queue_depth();
extern s32 abs(s32);
extern void select_sprite_entry(void *, u8, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_8016A36C[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];

/* Advances the selected actor action through targeting, animation, and cleanup. */
void advance_selected_actor_action(void *action, EntityRec *transform, void *sprite, EntityRec *actor)
{
    u8 action_state;
    u8 *action_slot;
    u8 *direction_table;
    u8 *action_control;
    s32 target_mode;
    s32 flagged_action;
    s32 action_kind;
    s32 action_value;
    s32 target_y;
    s32 magnitude_x;
    s16 mode_copy;
    void *current_table;

    action_state = ((S_8016C190_0 *)action)->unk_9B;
    target_mode = 0;

    switch (action_state) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            flagged_action = actor->unk_46 & 0x3FFF;
            switch (flagged_action) {
            case 7:
                target_mode = 1;
                /* fall through */
            case 3:
                action_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                target_mode = 1;
                /* fall through */
            case 2:
                action_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                target_mode = 1;
                /* fall through */
            case 1:
                action_slot = (u8 *)actor + 8;
                break;
            default:
                action_slot = 0;
                break;
            }
        } else {
            action_kind = actor->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                action_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                action_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                action_slot = (u8 *)actor + 8;
                break;
            default:
                action_slot = 0;
                break;
            }
        }
        if (*action_slot != 0) {
            action_value = ((S_8016C190_0 *)action)->unk_98 & 0xFF7F;
            ((S_8016C190_0 *)action)->unk_98 = action_value;
            mode_copy = target_mode;
            if (mode_copy != 0) {
                action_value = (s32)D_800814A8;
                actor->target = (void *)action_value;
                action_control = (u8 *)((SpriteLinkPrefixView *)action_value)[-1].unk_00;
                actor->unk_72 = action_control[0x24];
                actor->unk_73 = action_control[0x25];
            } else {
                u8 *action_defs = D_8006DE24;
                action_value = (s32)(action_defs + *action_slot * 20);
                if (((u8 *)action_value)[0x12] == 2) {
                    action_value = (s32)actor->target;
                    if (action_value != 0) {
                        action_control = (u8 *)((SpriteLinkPrefixView *)action_value)[-1].unk_00;
                        actor->unk_72 = action_control[0x24];
                        actor->unk_73 = action_control[0x25];
                    }
                } else {
                    actor->target = scan_monster_along_heading(
                        actor,
                        ((S_8016C190_3 *)sprite)->unk_24,
                        ((S_8016C190_3 *)sprite)->unk_25,
                        actor->facing,
                        0x10);
                    magnitude_x = abs(actor->unk_72);
                    target_y = abs(actor->unk_73);
                    actor->unk_72 = magnitude_x;
                    actor->unk_73 = target_y;
                }
            }

            if (create_actor_spell_effect(actor, action_slot, target_mode,
                              (u16 *)((u8 *)action + 0x98)) != 0) {
                ((S_8016C190_0 *)action)->unk_96.s = 8;
                ((S_8016C190_0 *)action)->unk_9B++;
            }
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, ((S_8016C190_3 *)sprite)->unk_24, ((S_8016C190_3 *)sprite)->unk_25);
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_8016C190_0 *)action)->unk_8C = D_8016A36C;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((S_8016C190_3 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_8016C190_3 *)sprite)->unk_14 &= 0xF7FF;
        ((S_8016C190_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);
                        /* fall through */

    case 2:
        ((S_8016C190_0 *)action)->unk_96.u--;
        if ((s16)((S_8016C190_0 *)action)->unk_96.u > 0 &&
            !(((S_8016C190_3 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_8016C190_0 *)action)->unk_98 |= 0x80;
        ((S_8016C190_0 *)action)->unk_9B++;
        return;

    case 3:
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            ((S_8016C190_0 *)action)->unk_96.s = 0;
        }
        if (!(((S_8016C190_3 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, ((S_8016C190_3 *)sprite)->unk_24, ((S_8016C190_3 *)sprite)->unk_25);

        switch (((S_8016C190_0 *)action)->unk_AC) {
        case 0:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739A0;
            if ((u8 *)current_table != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 1:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739A8;
            if ((u8 *)current_table != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 2:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739B0;
            if ((u8 *)current_table != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 3:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739B8;
            if ((u8 *)current_table != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        default:
            break;
        }

        action_control = (u8 *)&g_dungeon_status.unk_00;
        if (((S_8016C190_5 *)action_control)->unk_0C != 0) {
            return;
        }
        ((S_8016C190_5 *)action_control)->unk_0A--;
        ((S_8016C190_0 *)action)->unk_8C = D_8016A36C;
        advance_status_timers(actor);
        (*(u8 *)&actor->unk_6D)--;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;

    default:
        return;
    }
}
