#include "common.h"
#include "m2c_compat.h"

typedef struct S_801721C0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801721C0_0;   /* arg0 in func_801721C0 */


M2C_UNK func_800A4ACC();                     /* extern */
s32 func_800AB1C0();                                /* extern */
M2C_UNK func_800AD594();            /* extern */
s32 func_800AD9B4();                /* extern */
extern u16 D_80083462;
extern M2C_UNK D_80170E54;

/* Updates object state after checking the target and conditionally clears its value. */
void func_801721C0(S_801721C0_0 *object, M2C_UNK unused, M2C_UNK check_data, M2C_UNK target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(check_data, target) << 0x10) > 0) {
            object->unk_8C = &D_80170E54;
            goto check_reset;
        }
    } else {
check_reset:
        if (D_80083462 & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}
