#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void setResidentBitmapBit();                     /* extern */
void townUnlinkSceneListNode();                      /* extern */
void townClearObjectSlotAndMarkRemoved();                      /* extern */

typedef struct S_800C56A8_0 {
    s32 unk_00;
    s32 unk_04;
} S_800C56A8_0;   /* arg1 in func_800C56A8 */


/* Adjust the two state values and run completion actions when the countdown expires. */
void func_800C56A8(Rec_func_80094268_arg0 *object, S_800C56A8_0 *state) {
    u16 ticks_left;

    state->unk_00 = (s32) (state->unk_00 + 0xFFFEAAAB);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    ticks_left = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        setResidentBitmapBit(0x54);
        townUnlinkSceneListNode(object);
        townClearObjectSlotAndMarkRemoved(object);
    }
}
