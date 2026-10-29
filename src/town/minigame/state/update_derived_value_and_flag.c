#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/state.h"

   /* the 0x2 bytes before arg0 in update_derived_value_and_flag, addressed as arg0[-1] */

typedef struct S_80021028_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x6];
    s16 unk_0E;
} S_80021028_0;   /* arg0 in update_derived_value_and_flag */

typedef struct S_80021028_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
} S_80021028_1;


/* Updates the object's derived value and propagates the linked data's 0x8000 flag. */
void update_derived_value_and_flag(void *object) {
    ObjectStatusPrefix16 *object_view = object;
    S_80021028_1 *objectData;

    objectData = ((S_80021028_0 *)object)->unk_04;
    ((S_80021028_0 *)object)->unk_0E = (s16) ((objectData->unk_06 * 0xC) + 0x1E);
    if (objectData->unk_04 & 0x8000) {
        object_view[-1].flags = (u16) (object_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
