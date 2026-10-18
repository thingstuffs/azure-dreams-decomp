#include "modules/dungeon_ovl_7f511800_p03.h"

/* Fade the entity sprite, then remove the entity and update its tile flags. */
void fade_and_remove_entity_sprite(void *action, void *unused, void *sprite, void *entity)
{
    s32 state;
    s32 entity_flags;
    u16 fade_delay;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;

    state = ((T_80173450_S_80173450_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (*(s16 *)((u8 *)&g_dungeon_status.unk_0A) != 0) {
            return;
        }
        ((T_80173450_S_80173450_0 *)action)->unk_9B = 1;
                        /* fallthrough */
    case 1:
        entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_s32.v;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);
        ((T_80173450_S_80173450_0 *)action)->unk_96 = 4;
        ((T_80173450_S_80173450_0 *)action)->unk_9B++;
        ((T_80173450_S_80173450_2 *)sprite)->unk_12 -= 0x80;
                        /* fallthrough */
    case 2:
        break;
    default:
        return;
    }

    ((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v |= 0x10000000;
    fade_delay = ((T_80173450_S_80173450_0 *)action)->unk_96 - 1;
    ((T_80173450_S_80173450_0 *)action)->unk_96 = fade_delay;
    if ((s16)fade_delay <= 0) {
        if (((T_80173450_S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            ((T_80173450_S_80173450_2 *)sprite)->unk_0C.s32 += 0xFFEFEFF0;
        }
        ((T_80173450_S_80173450_2 *)sprite)->unk_10 = 0x20;
        ((T_80173450_S_80173450_2 *)sprite)->unk_14 |= 0xC;
    } else {
        ((T_80173450_S_80173450_2 *)sprite)->unk_0C.s32 = 0x808080;
    }

    if (!(((T_80173450_S_80173450_2 *)sprite)->unk_14 & 0x8000)) {
        if (((T_80173450_S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            return;
        }
    }

    tracked_entity = ((s32)g_dungeon_status.unk_10);
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        g_dungeon_status.unk_10 = tracked_entity & 0x7FFFFFFF;
    }
    distribute_experience_and_report_gains(entity);
    detach_record_and_update_slot_state(entity);

    tile_x = ((T_80173450_S_80173450_2 *)sprite)->unk_24;
    tile_y = ((T_80173450_S_80173450_2 *)sprite)->unk_25;
    tile_mask = 0x3000;
    if (((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
    unlink_entity_node(entity);
    (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
    object_flag_block.flags |= 0x8000;

    return;
}
