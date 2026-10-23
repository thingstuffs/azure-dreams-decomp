#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 (*Callback)(s32, void *);

extern s32 count_enabled_town_entries(void);
extern void *D_80018094[];
extern void *D_800180B4[];
extern s16 D_80018074[];
extern u8 D_8001914C[];
extern u8 D_80020F85[];
extern u8 D_80020FC7[];

/* Resolve the key to its table entry, using the slot-4 special case or the paged lookup table. */
void *resolve_event_response_key(s32 unused_a, s32 unused_b, s32 key)
{
    s32 index;
    TownEventState *state0;
    void **table;
    s16 *entry;

    state0 = town_event_state;
    if (state0->response_latch == 0) {
        state0->response_latch = 1;
        table = D_80018094;
    } else {
        table = D_800180B4;
    }

    if (key == 1) {
        TownEventState *state1;

        state1 = town_event_state;
        if (state1->selected_entry == 4) {
            if (town_scene_root->services->callback_2D4(0, table) == 2) {
                if (count_enabled_town_entries() >= 3) {
                    return D_80020F85;
                }
            }
            return D_80020FC7;
        }
        return table[state1->selected_entry];
    }

    for (index = 0; D_80018074[index] != 0; index += 2) {
        entry = &D_80018074[index];
        if (*entry == key)
            return table[entry[1]];
    }
    return D_8001914C;
}
