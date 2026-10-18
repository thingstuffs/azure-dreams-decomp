#include "shared/object_node.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
struct S_800B1E80_0;
extern void advance_cyclic_panel_entry(struct S_800B1E80_0 *state);

typedef struct S_800B1F00_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B1F00_0;

/* Create an object and assign advance_cyclic_panel_entry to its data pointer. */
void create_entity_panel_object(void) {
    S_800B1F00_0 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        object->unk_10 = advance_cyclic_panel_entry;
    }
}
