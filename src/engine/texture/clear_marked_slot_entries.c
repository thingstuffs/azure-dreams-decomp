#include "common.h"

typedef struct S_80083D08 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u16 flags;
    /* 0x6 */ u16 unk6;
} S_80083D08;

extern S_80083D08 sprite_resource_slots[6];
extern void bzero(void *ptr, s32 n);

/* Clears each of the six entries whose flags have bit 0 set. */
void clear_marked_slot_entries(void) {
    s32 slot_index;
    S_80083D08 *slot;

    slot_index = 0;
    slot = sprite_resource_slots;
    do {
        if (slot->flags & 1) {
            bzero(slot, 8);
        }
        slot_index++;
        slot++;
    } while (slot_index < 6);
}
