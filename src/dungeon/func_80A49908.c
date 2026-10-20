#include "modules/dungeon_resource06_slot0.h"

void fade_sprites_and_remove_entity(void *actor, s32 unused, void *sprite, void *entity)
{
    u8 state;
    u8 *sprite_group;
    s32 sprite_index;
    s32 group_index;

    state = U8(actor, 0x9B);
    sprite_group = 0;
    switch (state) {
    case 0:
        if (S16(&g_dungeon_status.unk_00, 0xA) != 0) {
            break;
        }
        U8(actor, 0x9B) = 1;
                        /* fallthrough */
    case 1:
    {
        s32 entity_flags;
        s32 sprite_offset;
        u8 *group_cursor;
        u32 white_rgb;
        u8 *group_sprite;

        entity_flags = S32(entity, 0x14);
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);

        group_index = 0;
        S16(sprite, 0x10) = 0x60;
        U16(sprite, 0x14) |= 0xC;
        U16(actor, 0x98) &= 0xDFFF;
        if (S16(actor, 0x9E) > 0) {
            white_rgb = 0xFFFFFF;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    sprite_offset = 8;
                    do {
                        group_sprite = sprite_group + sprite_offset;
                        U32(group_sprite, 0xC) = white_rgb;
                        select_sprite_entry(group_sprite,(u8)(0x23), 0);
                        sprite_offset += 0x30;
                        sprite_index++;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        break;
    }

    case 2:
    {
        u8 *group_cursor;
        s32 fade_delta;

        group_index = 0;
        if ((s32)sprite_group < S16(actor, 0x9E)) {
            fade_delta = 0xFFEFEFF0;
            group_cursor = actor;
            do {
                sprite_group = (u8 *)PTR(group_cursor, 0xA4) + 0x20;
                sprite_index = 0;
                if (S16(sprite_group, 2) > 0) {
                    do {
                        (*(u32 *)((u8 *)sprite_group + sprite_index * 0x30 + 0x14)) += fade_delta;
                        sprite_index++;
                    } while (sprite_index < S16(sprite_group, 2));
                }
                group_cursor += 4;
                group_index++;
            } while (group_index < S16(actor, 0x9E));
        }
        if (U16(sprite_group, 0x1C) & 0x6000) {
            PTR(sprite, 0x2C) = ((u8 *)D_8017588C);
            select_sprite_entry(sprite,(u8)(((u8 *)D_8017588C)[((g_game_work.view.viewAngle + S16(entity, 0x2A) + 0x100) >> 9) & 7]),
                0);
            U16(actor, 0x96) = 0x80;
            U8(actor, 0x9B) = U8(actor, 0x9B) + 1;
        }
        break;
    }

    case 3:
    {
        u8 brightness;
        u8 tile_x;
        u8 tile_y;
        s32 effect_id;
        DungeonGlobalStatus *dungeon_state;

        U32(entity, 0x1C) |= 0x10000000;
        brightness = U8(actor, 0x96);
        U8(sprite, 0xE) = brightness;
        U8(sprite, 0xD) = brightness;
        U8(sprite, 0xC) = brightness;
        U16(actor, 0x96) -= 0x10;
        if (U8(sprite, 0xC) != 0) {
            break;
        }
        dungeon_state = &g_dungeon_status;
        if (U32(dungeon_state, 0x10) == (u32)((u8 *)entity - 0x20)) {
            U32(dungeon_state, 0x10) &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        tile_x = U8(sprite, 0x24);
        tile_y = U8(sprite, 0x25);
        effect_id = 0x3000;
        if (U32(entity, 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        update_map_cell_flags_with_item_limit((u8)(tile_x),(u8)(tile_y), effect_id);
        unlink_entity_node(entity);
        U16(entity, -2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;
    }
    }
}
