#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378(void *, s32, s32, s32);
s32 func_800AD9B4(s32, s32);
extern u8 D_80170F20;
extern u8 D_80173B98;

typedef struct S_80172538_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x17];
    u8 unk_A7;
} S_80172538_0;   /* object in func_80172538 */

/* Selects the object's data pointer by its flag after both update checks succeed. */
void func_80172538(void *state, s32 motion, s32 entity, s32 actor) {
    S_80172538_0 *object = state;

    if ((func_800AB378(state, motion, entity, actor) != 0) &&
        ((func_800AD9B4(entity, actor) << 0x10) > 0)) {
        if (object->unk_A7 != 0) {
            object->unk_8C = &D_80173B98;
        } else {
            object->unk_8C = &D_80170F20;
        }
    }
}
