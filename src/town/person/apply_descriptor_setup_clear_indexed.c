#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void initialize_object_entries(void *state, s32 output, void *entries);
extern void apply_object_setup_update(void);

/* Apply descriptor setup, clear the indexed flag, and reset the object callback and state. */
void apply_descriptor_setup_clear_indexed(void *object, s32 unused, s32 setup_context) {
    initialize_object_entries(object, setup_context, *(void **) ((u8 *) *(void **) ((u8 *) object + 0x80) + 0x14));
    object_index_slots[*(s32 *) ((u8 *) object + 0x60)].unk_00 = 0;
    *(void **) ((u8 *) object + 0x54) = (void *) apply_object_setup_update;
    *(s16 *) ((u8 *) object + 0x72) = 0;
}
