#include "common.h"

extern void initialize_object_entries(void *state, s32 output, void *entries);
extern u8 D_800D6AA8;

/* Initializes object entries from D_800D6AA8 and increments the state halfword at offset 0x68. */
void initialize_object_and_advance(void *object, s32 unused, s32 context) {
    initialize_object_entries(object, context, &D_800D6AA8);
    *(u16 *)((u8 *)object + 0x68) += 1;
}
