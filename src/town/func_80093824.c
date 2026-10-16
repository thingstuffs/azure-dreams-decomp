#include "common.h"
#include "m2c_compat.h"

/* extern */
void townInitializeSceneActionRecord();      /* extern */

typedef struct S_80090F84_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80090F84_0;   /* arg2 in townRunActionThenFallbackOnFlag */


void townDispatchActorInteractionActions(s32 *, s32, S_80090F84_0 *);
/* Run the fallback handler if the value stays unchanged and either 0x6000 flag is set. */
void townRunActionThenFallbackOnFlag(s32 *value, s32 context, S_80090F84_0 *record) {
    s32 previous_value;

    previous_value = *value;
    townDispatchActorInteractionActions(value, context, record);
    if ((previous_value == *value) && (record->unk_14 & 0x6000)) {
        townInitializeSceneActionRecord(value, context, record);
    }
}
