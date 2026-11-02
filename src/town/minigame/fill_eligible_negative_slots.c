#include "shared/game_work.h"
#include "town/minigame/entry_state.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

/* Fill negative slots when eligibility is at least four, then clear a duplicate second slot. */
void fill_eligible_negative_slots(void *record, s16 *eligibility, s16 new_value)
{
    s32 slot_index;
    s16 *slot_cursor;
    slot_index = 0;
    slot_cursor = record;
    do {
        if (((slot_cursor[0x22]) < 0) && ((*eligibility) >= 4)) {
            slot_cursor[0x22] = new_value;
        }
        if (record) {
            slot_index += 1;
            slot_cursor += 1;
        }
        else {
            slot_index += 1;
            slot_cursor += 1;
        }
    }
    while (slot_index < 2);
    if ((*((s16 *) (((s8 *) record) + 0x44))) == (*((s16 *) (((s8 *) record) + 0x46)))) {
        *((s16 *) (((s8 *) record) + 0x46)) = -1;
    }
}
