#include "shared/runtime_dispatch.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u8 town_map_selection_state[12];
extern u8 town_building_slot_rectangles[];

extern s8 town_map_variant;
extern void request_scene_state_with_parameters(s32 notify_value, s16 state_10, s16 state_12, s16 state_14, s32 state_16);
/*
 * Requests scene state 0xB at the selected building rectangle bottom center and clears the
 * selection. Uses rectangle zero and clears town_map_variant when no match is found.
 */
void clear_selected_entry_at_bottom_center(void)
{
    s32 entry_index = 0x20;
    u8 *selection_state = town_map_selection_state;
    u8 *shared_state = ((u8 *)&runtime_dispatch_state);
    u8 *entries = town_building_slot_rectangles;
    u8 *page = (u8 *) 0x80010000;
    u8 *entry;
    u8 *fallback_entries;

    for (; entry_index > 0; entry_index--) {
        entry = entries + entry_index * 8;
        if (page[0x33A4 + entry_index * 2] == selection_state[6]) {
            request_scene_state_with_parameters(0xB, ((entry[0] + (entry[2] >> 1)) << 6) | 0x20, ((entry[1] + entry[3]) << 6) | 0x20, 0,
                (*((u16 *) (&shared_state[0x16]))) ^ 1);
            selection_state[6] = 0;
            return;
        }
    }
    fallback_entries = town_building_slot_rectangles;
    entry = fallback_entries + entry_index * 8;
    request_scene_state_with_parameters(0xB, ((entry[0] + (entry[2] >> 1)) << 6) | 0x20,
        ((entry[1] + entry[3]) << 6) | 0x20, 0, runtime_dispatch_state.flags16 ^ 1);
    town_map_variant = 0;
}
