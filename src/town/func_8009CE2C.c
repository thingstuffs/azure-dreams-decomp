#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_8009A58C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A58C_0;   /* arg0 in townClearPlayerMotionEntry */


void townInitializeTargetAndHandlerTable(S_8009A58C_0 *, s32);
/* Clear the indexed table entry and call townInitializeTargetAndHandlerTable. */
void townClearPlayerMotionEntry(S_8009A58C_0 *object, s32 value) {
    D_80082660[object->unk_40].unk_00 = 0;
    townInitializeTargetAndHandlerTable(object, value);
}
