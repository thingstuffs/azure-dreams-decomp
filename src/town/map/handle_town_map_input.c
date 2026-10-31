#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "slus.h"
#include "engine/script.h"
#include "town/map.h"

void send_resource_command_23(s32);

extern u8 D_80072210[];
extern u8 D_80072214[];
extern s32 town_map_selection;
extern u8 D_8008BED8[];
extern u8 town_map_status;
extern u8 town_building_slot_rectangles;

/* Handle input and update the object display position for its current state. */
void handle_town_map_input(u8 *object, void *transform, void *context) {
    GameWork *input = &g_game_work;
    u8 *entries = *(u8 **)(object + 0x7C);
    s16 state;

    if (town_map_status != 0) {
        *(void **)(object + 0x68) = D_8008BED8;
        return;
    }

    state = *(s16 *)(object + 0x66);
    if (state == 0) {
        u16 timer = *(u16 *)(object + 0x64) - 1;

        *(u16 *)(object + 0x64) = timer;
        if ((timer << 16) <= 0) {
            s32 buttons;

            *(u16 *)(object + 0x64) = 0;
            if ((input->pressed_buttons) & 0x10000000) {
                *(u16 *)((u8 *)transform + 0xA) += 0x10;
            }
            if ((input->pressed_buttons) & 0x40000000) {
                *(u16 *)((u8 *)transform + 0xA) -= 0x10;
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
        *(s32 *)(*(u8 **)object + 0x30) = view_reference_entity.x.w.i / 64 - 0x18;
        *(s32 *)(*(u8 **)object + 0x34) = view_reference_entity.y.w.i / 64 - 0x40;
        return;
    } else if (state == 10) {
        s32 buttons;
        s32 entry_index;
        u8 entry_id;
        u8 *positions;

        advance_sprite_animation_and_textures(context);
        buttons = (input->pressed_buttons);
        if (buttons & 0x6000) {
            if (++*(s32 *)(object + 0x74) >= *(s32 *)(object + 0x78)) {
                *(s32 *)(object + 0x74) = 0;
            }
            send_resource_command_23(entries[*(s32 *)(object + 0x74)]);
        } else if (buttons & 0x9000) {
            if (--*(s32 *)(object + 0x74) < 0) {
                *(s32 *)(object + 0x74) = *(s32 *)(object + 0x78) - 1;
            }
            send_resource_command_23(entries[*(s32 *)(object + 0x74)]);
        }
        entry_index = *(s32 *)(object + 0x74);
        positions = &town_building_slot_rectangles;
        entry_id = entries[entry_index];
        *(s32 *)(*(u8 **)object + 0x30) = positions[entry_id * 8] - 0x18;

        entry_index = *(s32 *)(object + 0x74);
        entry_id = entries[entry_index];
        *(s32 *)(*(u8 **)object + 0x34) = positions[entry_id * 8 + 1] - 0x40;

        entry_index = *(s32 *)(object + 0x74);
        town_map_selection = entries[entry_index];
    }
}
