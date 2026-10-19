#include "modules/dungeon_resource17_slot0.h"

void advance_familiar_defeat_sequence(R17_80173614_S_func_80C17E14_0 *action, MotionDeltaView *motion, R17_80173614_S_func_80C17E14_2 *sprite,
    R17_80173614_S_func_80C17E14_3 *entity) {
    s32 direction_offset;
    s32 offset_x;
    s32 offset_y;
    s32 state;

    direction_offset = (entity->unk_6A >> 8) & 0xE;
    offset_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    offset_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    state = action->unk_9B;

    switch (state) {
    case 0:
        *(s32 *)((u8 *)motion + 0xC) = offset_x << 16;
        *(s32 *)((u8 *)motion + 0x10) = offset_y << 16;
        *(s32 *)((u8 *)motion + 0x14) = 0x8000;
        if (g_dungeon_status.unk_0A != 0) {
            return;
        }
        action->unk_9B = action->unk_9B + 1;
    case 1:
    {
        s32 entity_status;
        u32 entity_flags;
        u32 clear_bit_27;
        u32 clear_bit_18;
        u16 action_flags;

        entity_status = entity->unk_14;
        if (entity_status & 0x4000) {
            if (!(entity_status & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);

        clear_bit_27 = 0xF7FFFFFF;
        action_flags = action->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        action_flags |= 8;
        action->unk_98 = action_flags;
        entity_flags = entity->unk_1C;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        entity->unk_1C = entity_flags;
        sprite->unk_10 = 0x60;
        sprite->unk_12 = 0xFF80;
        sprite->unk_14 |= 0xC;
        action->unk_9B = action->unk_9B + 1;
        return;
    }
    case 2:
        if (!(sprite->unk_14 & 0x6000)) {
            return;
        }
        action->unk_96.unk_00_u16 = 0x80;
        action->unk_9B = action->unk_9B + 1;
        return;
    case 3:
    {
        s32 sound_kind;
        u32 entity_flags;
        u32 sound_x;
        u32 sound_y;
        u16 next_brightness;
        u8 brightness;

        entity->unk_1C |= 0x10000000;
        brightness = action->unk_96.unk_00_u8;
        sprite->unk_0E = brightness;
        sprite->unk_0D = brightness;
        sprite->unk_0C = brightness;
        next_brightness = action->unk_96.unk_00_u16 - 0x10;
        action->unk_96.unk_00_u16 = next_brightness;
        if ((s16)next_brightness >= 0x10) {
            return;
        }

        if (((s32)g_dungeon_status.unk_10) == (s32)((u8 *)entity - 0x20)) {
            *(s32 *)&g_dungeon_status.unk_10 &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);

        entity_flags = entity->unk_1C;
        sound_x = sprite->unk_24;
        sound_y = sprite->unk_25;
        sound_kind = 0x3000;
        if (entity_flags & 0x2000) {
            sound_kind = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_kind);
        unlink_entity_node(entity);
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
        break;
    }
}
