#include "common.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"
extern s32 D_800D6AA8[];

/* Initializes object entries from D_800D6AA8 and increments the state halfword at offset 0x68. */
void initialize_object_and_advance(void *object, s32 unused, void *context) {
    initialize_object_entries(object, context, D_800D6AA8);
    *(u16 *)((u8 *)object + 0x68) += 1;
}
