#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

/* extern */

typedef struct GapPlayerSlot {
    u8 pad_00[0x40];
    s32 unk_40;
} GapPlayerSlot;   /* arg0 in func_8009A5C0 */


void townInitializeTargetAndHandlerTable(GapPlayerSlot *, s32);
/* Clear the indexed table entry and call townInitializeTargetAndHandlerTable. */
void func_8009A5C0(GapPlayerSlot *object, s32 value) {
    D_80082660[object->unk_40].unk_00 = 0;
    townInitializeTargetAndHandlerTable(object, value);
}
