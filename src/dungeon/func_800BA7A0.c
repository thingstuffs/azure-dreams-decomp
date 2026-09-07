#include "common.h"
#include "m2c_compat.h"

s32 func_8004383C();                 /* extern */
void func_8008D330(void *, void *, void *, void *); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800C0024(void);                                /* extern */
M2C_UNK func_800D4FC8();    /* extern */
typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern s32 D_800E296C;
extern u8 *D_800E3D7C;

typedef struct S_800BFF00_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x25];
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0xCD];
    s32 unk_110;
} S_800BFF00_0;   /* arg0 in func_800BFF00 */

s32 func_800BFF00(void *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        ((S_800BFF00_0 *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((S_800BFF00_0 *)arg0)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }
    if ((u8) ((S_800BFF00_0 *)arg0)->unk_11 < 0x63U) {
        ((S_800BFF00_0 *)arg0)->unk_18 = func_8004383C(arg0, 0);
        ((S_800BFF00_0 *)arg0)->unk_42 = 0;
        ((S_800BFF00_0 *)arg0)->unk_41 = 0;
        D_800E296C |= 0x100000;
    }
    func_800D4FC8(arg0 - 0x20, 0x20F0F0, 0x616);
    func_80098B38(arg1);
    D_80083460.field_A--;
    return 1;
}
/* MECHANISM: The seed already had retail's 0x20 frame and s0/s1/ra save contract.
   Restoring the four-argument callee ABI and explicit 0/1 tail returns fixed both dispatcher paths.
   u16 table indexing plus direct global/struct RMW forms closed the scale/addressing residue. */
