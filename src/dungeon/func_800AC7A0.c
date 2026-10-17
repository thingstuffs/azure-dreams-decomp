#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
struct S_800B1E80_0;
extern void dungeonAdvanceCyclicPanelEntry(struct S_800B1E80_0 *state);

typedef struct S_800B1F00_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B1F00_0;

/* Create an object and assign dungeonAdvanceCyclicPanelEntry to its data pointer. */
void dungeonCreateEntityPanelObject(void) {
    S_800B1F00_0 *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = dungeonAdvanceCyclicPanelEntry;
    }
}
