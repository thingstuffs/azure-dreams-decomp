#include "common.h"
#include "m2c_compat.h"

typedef struct S_801724A8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801724A8_0;   /* arg0 in func_801724A8 */


M2C_UNK func_800A4ACC();                     /* extern */
s32 func_800AB1C0(arg0, arg1, arg2, arg3);                                /* extern */
M2C_UNK func_800AD594();            /* extern */
s32 func_800AD9B4();                /* extern */
extern u16 D_80083462;
extern M2C_UNK D_801710F4;

/* Updates the target and conditionally resets the caller state. */
void func_801724A8(S_801724A8_0 *state, M2C_UNK context, M2C_UNK source, M2C_UNK target) {
    if (func_800AB1C0(state, context, source, target) != 0) {
        func_800AD594(target, 3);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 0x10) > 0) {
            state->unk_8C = &D_801710F4;
            state->unk_90.at00.v = 0;
            goto check_reset;
        }
    } else {
check_reset:
        if (D_80083462 & 0x80) {
            state->unk_90.at02.v = 0;
        }
    }
}
