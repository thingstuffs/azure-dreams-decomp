#include "shared/town_event_state.h"
#include "common.h"

typedef struct S_8001B960_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001B960_0;   /* obj in townStoreCurrentValueIfStateZero */

typedef struct S_8001B960_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001B960_1;   /* (index * 0x10) + ((S_8001B960_0 *)obj)->unk_10 in townStoreCurrentValueIfStateZero */


extern s32 townBuildThreeValueBlock(void);

/* Store the current handler in the object's table slot unless the global gate is set. */
s32 townStoreCurrentValueIfStateZero(S_8001B960_0 *obj, s32 index) {
    if (D_8001E950->unk_05 == 0) {
        ((S_8001B960_1 *)((index * 0x10) + obj->unk_10))->unk_08 =
            townBuildThreeValueBlock();
        return 0;
    }
    return 1;
}
