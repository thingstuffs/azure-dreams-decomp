#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 rand();                             /* extern */
M2C_UNK func_800A48F0();        /* extern */

typedef struct S_81832FE8_0 {
    u8 pad_00[0x60];
    void * unk_60;
} S_81832FE8_0;   /* arg0 in func_81832FE8 */

typedef struct S_81832FE8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81832FE8_1;   /* temp_v1 in func_81832FE8 */

/* Set flag 0x20 and apply a randomized effect to an eligible attached object. */
void func_81832FE8(S_81832FE8_0 *owner) {
    s32 flags;
    S_81832FE8_1 *object;

    object = owner->unk_60;
    if (object != NULL) {
        flags = object->unk_14;
        if (!(flags & 0x20) && (flags & 1)) {
            object->unk_1C = (s32) (object->unk_1C | 0x20);
            func_800A48F0(owner->unk_60, 4, (rand(flags) & 0x3F) | 0x20);
        }
    }
}
