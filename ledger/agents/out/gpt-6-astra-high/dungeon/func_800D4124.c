#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D9884_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_800D9884_0;   /* arg0 in func_800D9884 */


M2C_UNK func_800A4ACC();                     /* extern */
s32 func_800AB1C0();                                /* extern */
M2C_UNK func_800AD594();            /* extern */
s32 func_800AD9B4();                /* extern */
extern u16 D_80083462;
extern M2C_UNK D_800D8C64;

/* Updates the target and resets state after a successful check or a reset flag. */
void func_800D9884(S_800D9884_0 *state, M2C_UNK unused, M2C_UNK source, M2C_UNK target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 0x10) > 0) {
            state->unk_8C = &D_800D8C64;
            state->unk_90.at00.v = 0;
            goto check_reset_flag;
        }
    } else {
check_reset_flag:
        if (D_80083462 & 0x80) {
            state->unk_90.at02.v = 0;
        }
    }
}
