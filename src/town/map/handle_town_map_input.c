#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "slus.h"
#include "engine/script.h"
#include "town/map.h"
#include "town/map/body.h"
#include "town/menu/window.h"
#include "slus/town_map_selection_data.h"

void write_town_map_resource_command(s32);

extern u8 D_80072210[];
extern u8 D_80072214[];
extern u8 D_8008BED8[];
extern u8 town_map_status;

/* Handle input and update the object display position for its current state. */
void handle_town_map_input(TownMapBody *object, ObjectPosition *transform, SpriteFrameState *context) {
    GameWork *input = &g_game_work;
    u8 *entries = object->entries;
    s16 state;

    if (town_map_status != 0) {
        object->update = D_8008BED8;
        return;
    }

    state = object->type_id;
    if (state == 0) {
        u16 timer = object->timer.as_u16 - 1;

        object->timer.as_u16 = timer;
        if ((timer << 16) <= 0) {
            s32 buttons;

            object->timer.as_u16 = 0;
            if ((input->pressed_buttons) & 0x10000000) {
                transform->z.unsigned_parts.integer += 0x10;
            }
            if ((input->pressed_buttons) & 0x40000000) {
                transform->z.unsigned_parts.integer -= 0x10;
            }

            buttons = (input->pressed_buttons);
            if (buttons & 0x40) {
                town_map_status = 1;
                call_script((s32)(D_80072214));
                return;
            }
            if (buttons & 0x20) {
                town_map_status = 1;
                call_script((s32)(D_80072210));
                return;
            }
        }
    } else if (state == 9) {

        advance_sprite_animation_and_textures(context);
        object->context->unk_30 = view_reference_entity.x.w.i / 64 - 0x18;
        object->context->unk_34 = view_reference_entity.y.w.i / 64 - 0x40;
        return;
    } else if (state == 10) {
        s32 buttons;
        s32 entry_index;
        u8 entry_id;
        u8 *positions;

        advance_sprite_animation_and_textures(context);
        buttons = (input->pressed_buttons);
        if (buttons & 0x6000) {
            if (++object->selection >= object->entry_count) {
                object->selection = 0;
            }
            write_town_map_resource_command(entries[object->selection]);
        } else if (buttons & 0x9000) {
            if (--object->selection < 0) {
                object->selection = object->entry_count - 1;
            }
            write_town_map_resource_command(entries[object->selection]);
        }
        entry_index = object->selection;
        positions = town_building_slot_rectangles;
        entry_id = entries[entry_index];
        object->context->unk_30 = positions[entry_id * 8] - 0x18;

        entry_index = object->selection;
        entry_id = entries[entry_index];
        object->context->unk_34 = positions[entry_id * 8 + 1] - 0x40;

        entry_index = object->selection;
        town_map_selection = entries[entry_index];
    }
}
