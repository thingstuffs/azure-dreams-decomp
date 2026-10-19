#include "modules/dungeon_resource10_slot0.h"

void advance_actor_spell_effect_sequence(void *actor, EntityRec *motion, void *tile_arg, EntityRec *action)
{
    s16 particle_index;
    s32 offset_y;
    s32 offset_x;
    void *target_obj;
    u8 *kind_data;
    s32 state;
    s16 effect_flags;
    s16 action_dep;

    state = ((R10_80173280_S_80173280_0 *)actor)->unk_9B;
    effect_flags = 0;
    switch (state) {
    case 0:
    if (action->flags1C & 0x2000) {
        u32 kind = (action->unk_46 & 0x3FFF) - 1;

        switch (kind) {
        case 6:
            effect_flags = 1;
        case 2:
            goto kind_3;
        case 5:
            effect_flags = 1;
        case 1:
            goto kind_2;
        case 4:
            effect_flags = 1;
        case 0:
            goto kind_1;
        case 3:
        default:
            goto kind_default;
        }
    } else {
        switch (action->unk_46 & 0x3FFF) {
        case 2:
            goto kind_2;
        case 1:
            goto kind_1;
        case 3:
            goto kind_3;
        default:
            goto kind_default;
        }
    }

kind_3:
    kind_data = (u8 *)action + 0xE;
    goto use_kind;
kind_2:
    kind_data = (u8 *)action + 0xB;
    goto use_kind;
kind_1:
    kind_data = (u8 *)action + 8;
    goto use_kind;
kind_default:
    kind_data = 0;

use_kind:
    if (*kind_data != 0) {
        ((R10_80173280_S_80173280_0 *)actor)->unk_98 =
            ((R10_80173280_S_80173280_0 *)actor)->unk_98 & 0xFF7F;
        if (effect_flags) {
            target_obj = D_800814A8;
            action->target = target_obj;
            state = (s32)((R10_80173280_S_80173280_2 *)((u8 *)target_obj - 0x14))->unk_00;
            action->unk_72 = ((u8 *)state)[0x24];
            action->unk_73 = ((u8 *)state)[0x25];
        } else {
            u8 *kind_table;
            u8 kind;
            u8 *kind_entry;

            kind = *kind_data;
            kind_table = (u8 *)D_8006DE24;
            kind_entry = (u8 *)((u32)(kind * 20) + (u32)kind_table);

            if (kind_entry[0x12] == 2) {
                target_obj = action->target;
                if (target_obj != 0) {
                    state = (s32)((R10_80173280_S_80173280_2 *)((u8 *)target_obj - 0x14))->unk_00;
                    action->unk_72 = ((u8 *)state)[0x24];
                    action->unk_73 = ((u8 *)state)[0x25];
                }
            } else {
                s8 x;
                s8 y;

                action->target = (void *)scan_monster_along_heading(action, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_24, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_25,
                              action->facing, 0x10);
                x = action->unk_72;
                y = action->unk_73;
                x = abs(x);
                y = abs(y);
                action->unk_72 = x;
                action->unk_73 = y;
            }
        }
        if (create_actor_spell_effect(action, kind_data,(s16)(effect_flags), (u8 *)actor + 0x98)) {
            ((R10_80173280_S_80173280_0 *)actor)->unk_96.s = 0x18;
            ((R10_80173280_S_80173280_0 *)actor)->unk_9E = 4;
            ((R10_80173280_S_80173280_0 *)actor)->unk_9B++;
            return;
        }
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    set_record_integer_tile_center(motion, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_24, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_25);
    {
        u8 *active_actor = D_800814A8;
        ((Rec_D_80083460 *)((u8 *)(&g_dungeon_status)))->unk_0C = 0;
        ((R10_80173280_S_80173280_6 *)active_actor)->unk_A6--;
    }
    advance_status_timers(action);
    (*(u8 *)&action->unk_6D)--;
    ((R10_80173280_S_80173280_0 *)actor)->unk_8C = ((u8 *)func_801717F4);
    action->unk_73 = 0;
    action->unk_72 = 0;
    action->unk_46 &= 0x7FFF;
    return;

case 1:
    if (get_cd_command_queue_depth()) {
        ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
        return;
    }
    ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    ((R10_80173280_S_80173280_0 *)actor)->unk_9B++;
    play_sound_if_enabled(0x703);

case 2:
    particle_index = 0;
    do {
        effect_flags = func_80069EF8() & 0xFF;
        effect_flags |= 0x80;
        offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
        offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
        func_80170CF8((u8 *)actor - 0x20, 0, 0x00808080, effect_flags, offset_x, offset_y,
                   (s16)((func_80069EF8() & 0x7F) - 0x40));
        particle_index++;
    } while (particle_index < 5);

    ((R10_80173280_S_80173280_0 *)actor)->unk_9E--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->unk_9E == 1) {
        ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
    }
    if (((R10_80173280_S_80173280_0 *)actor)->unk_96.u == 5) {
        ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    ((R10_80173280_S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->unk_96.s > 0 &&
        !(((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 & 0xE000)) {
        return;
    }
    ((R10_80173280_S_80173280_0 *)actor)->unk_98 |= 0x80;
    ((R10_80173280_S_80173280_0 *)actor)->unk_9B++;
    ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
    ((R10_80173280_S_80173280_0 *)actor)->unk_96.s = 0x14;
    return;

case 3:
    kind_data = ((u8 *)(&g_dungeon_status));
    if (((R10_80173280_S_80173280_7 *)kind_data)->unk_0C == 0) {
        ((R10_80173280_S_80173280_0 *)actor)->unk_96.s = 0;
    }
    ((R10_80173280_S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->unk_96.s <= 0) {
        *(u16 *)((u8 *)actor + 0x96) = 0;
        ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    if (!(((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 & 0xE000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    set_record_integer_tile_center(motion, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_24, ((R10_80173280_S_80173280_3 *)tile_arg)->unk_25);
    if (((R10_80173280_S_80173280_3 *)tile_arg)->unk_2C != ((u8 *)D_80175988)) {
        u8 *frame_table = ((u8 *)D_80175988);
        (*(u8 * *)((u8 *)tile_arg + 0x2C)) = frame_table;
        func_80047784(tile_arg,
            frame_table[((g_game_work.view.viewAngle + action->facing + 0x100) >> 9) & 7],
            0);
        ((R10_80173280_S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    if (((R10_80173280_S_80173280_7 *)kind_data)->unk_0C != 0) {
        return;
    }
    ((R10_80173280_S_80173280_7 *)kind_data)->unk_0A--;
    ((R10_80173280_S_80173280_0 *)actor)->unk_8C = ((u8 *)func_801717F4);
    advance_status_timers(action);
    action->unk_73 = 0;
    action->unk_72 = 0;
    (*(u8 *)&action->unk_6D)--;
    action->unk_46 &= 0x7FFF;
    play_sound_if_enabled(0xB4);
        return;
    default:
        return;
    }
}
