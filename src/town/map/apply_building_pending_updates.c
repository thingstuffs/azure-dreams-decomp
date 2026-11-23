#include "common.h"
#include "shared/game_state.h"
#include "m2c_compat.h"
#include "town/map.h"

typedef struct S_800B8A40_0 {
    u8 pad_00[0x3608];
    u8 unk_3608;
    u8 pad_3609[0x1];
    u8 unk_360A;
} S_800B8A40_0;   /* temp_v0_2 in apply_building_pending_updates */

/* Apply and clear pending byte updates, then copy two additional state bytes. */
void apply_building_pending_updates(void) {
    s32 entry_index;
    s32 byte_index;
    u8 pending_value;
    u8 source_value;
    S_800B8A40_0 *byte_record;

    for (entry_index = 0; entry_index < 0x22; entry_index++) {
        pending_value = GAME_STATE->building_slots[entry_index][1];
        if (pending_value != 0) {
            GAME_STATE->building_slots[entry_index][0] = pending_value;
            GAME_STATE->building_slots[entry_index][1] = 0;
        }
    }
    byte_index = 0;
    do {
        byte_record = byte_index + 0x80010000;
        source_value = byte_record->unk_360A;
        byte_index += 1;
        byte_record->unk_3608 = source_value;
    } while (byte_index < 2);
}
