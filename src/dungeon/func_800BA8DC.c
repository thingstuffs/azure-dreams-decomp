#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A48F0();    /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800C0168();                               /* extern */
M2C_UNK func_800D4FC8();    /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E206A;
extern void *D_800E3D7C[];

typedef struct S_800C003C_0 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 pad_03[0x10];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0xF8];
    s32 unk_110;
} S_800C003C_0;   /* arg0 in func_800C003C */

typedef struct S_800C003C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C003C_1;   /* global_base in func_800C003C */

s32 func_800C003C(void *arg0, s32 arg1, s16 arg2) {
    u8 temp_v1;
    s8 *global_base;

    if (arg0 == D_800E3D7C[0]) {
        ((S_800C003C_0 *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((S_800C003C_0 *)arg0)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }
    temp_v1 = ((S_800C003C_0 *)arg0)->unk_02;
    if (temp_v1 < 0xFFU) {
        ((S_800C003C_0 *)arg0)->unk_02 = (u8) (temp_v1 + 1);
    }
    func_800A48F0(arg0, 7, 8);
    if (((S_800C003C_0 *)arg0)->unk_14 & 0x4000) {
        func_80099844(arg0, &D_800E206A);
    }
    func_800D4FC8(arg0 - 0x20, 0xF02020, 0x616);
    func_80098B38(arg1);
    global_base = (s8 *) &D_80083460;
    ((S_800C003C_1 *)global_base)->unk_0A = (u16) (((S_800C003C_1 *)global_base)->unk_0A - 1);
    return 1;
}

/* MECHANISM: Natural long-lived arguments produce retail's 0x20 frame and s0/s1 saves.
   A byte-pointer held base forces the final global's explicit lui/addiu pair and +0xA accesses.
   Typed u16 table indexing fixes scale-by-two; void tails expose 0/1 jump-delay constants. */
