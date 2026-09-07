#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A1B44_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800A1B44_0;   /* D_800E3D7C in func_800A1B44 */

typedef struct S_800A1B44_1 {
    s32 unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
} S_800A1B44_1;   /* var_s0 in func_800A1B44; pointer addresses record offset 0x14 */


M2C_UNK func_800A19E4(); /* extern */
extern S_800A1B44_0 *D_800E3D7C;

/* Update proximity state for each actor in the list. */
void func_800A1B44(s16 near_limit, s16 far_limit) {
    void *actor;

    actor = (void *) (D_800E3D7C->unk_5C + 0x20);
    if (actor != D_800E3D7C) {
        do {
            func_800A19E4(((S_800A1B44_1 *)((u8 *)actor - 0x14))->unk_00, actor, near_limit, far_limit, (void *) ((s32) actor + 0x9C));
            actor = (void *) (((S_800A1B44_1 *)((u8 *)actor - 0x14))->unk_70 + 0x20);
        } while (actor != D_800E3D7C);
    }
}
