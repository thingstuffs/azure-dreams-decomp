#include "modules/dungeon_resource12_slot0.h"

void advance_entity_fade_effect(R12_801732EC_EffectState *effect, void *unused, R12_801732EC_Entity *entity, R12_801732EC_Object *object) {
    s32 state;
    s32 object_status;
    s32 status_mask;
    s32 direction_index;
    s32 fade_delta;
    s32 strength;
    s16 countdown;
    u16 timer;
    u8 x;
    u8 y;

    state = effect->state;
    switch (state) {
    case 0:
        if (*(s16 *)(((u8 *)(&g_dungeon_status)) + 0xA) != 0) {
            return;
        }
        effect->state = 1;
                        /* fallthrough */
    case 1:
        object_status = object->field14;
        if (object_status & 0x4000) {
            status_mask = object_status & 0x20000000;
            if (status_mask == 0) {
                announce_familiar_defeat(object);
            }
        }
        play_sound_if_enabled(0x805);
        entity->field10 = 0x20;
        entity->flags |= 0xC;
        entity->field12 -= 0x80;
        object->flags |= 0x10000000;
        entity->value = 0x808080;
        effect->state++;
        return;
    case 2:
        entity->value += 0xFFF7F7F8;
        if (!(entity->flags & 0x6000)) {
            return;
        }
        object->flags |= 0x10000000;
        entity->table = ((u8 *)D_80175AA4);
        effect->timer = 0x80;
        effect->countdown = 0;
        direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + object->angle + 0x100) >> 9) & 7;
        select_sprite_entry(entity,(u8)(entity->table[direction_index]), 0);
        effect->state++;
        return;
    case 3:
        fade_delta = 0xFFF7F7F8;
        object->flags |= 0x10000000;
        entity->value += fade_delta;
        if ((entity->field10 == 0x20) && ((u8)entity->value < 0x40)) {
            entity->field10 = 0x60;
            entity->value = 0xF0F0F0;
        }
        countdown = effect->countdown - 1;
        effect->countdown = countdown;
        if (countdown >= 0) {
            entity->flags |= 0x800;
        } else {
            entity->flags &= 0xF7FF;
            timer = effect->timer + 0x60;
            effect->timer = timer;
            effect->countdown = (u16)((s32)(timer << 16) >> 24);
        }
        if ((entity->type == 2) && (entity->flags & 0x1000)) {
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + object->angle + 0x100) >> 9) & 7;
            select_sprite_entry(entity,(u8)(entity->table[direction_index]), 0);
        }
        if ((u8)entity->value < 0x11) {
            if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)object - 0x20)) {
                *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
            }
            distribute_experience_and_report_gains(object);
            detach_record_and_update_slot_state(object);
            x = entity->x;
            y = entity->y;
            strength = 0x3000;
            if (object->flags & 0x2000) {
                strength = 0x300;
            }
            update_map_cell_flags_with_item_limit((u8)(x),(u8)(y), strength);
            unlink_entity_node(object);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        return;
    default:
        return;
    }
}
