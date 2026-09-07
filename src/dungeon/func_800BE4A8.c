#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800C3D24();                               /* extern */
M2C_UNK func_800D4FC8();    /* extern */
extern M2C_UNK D_80082E80[];
extern s32 D_80083460;
extern M2C_UNK D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1843[];
extern s32 D_800E3D7C[];


typedef struct S_800C3C08_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0xF8];
    s32 unk_110;
} S_800C3C08_0;   /* arg0 in func_800C3C08 */

typedef struct S_800C3C08_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3C08_1;   /* global_base in func_800C3C08 */

s32 func_800C3C08(void *arg0, s32 arg1, s16 arg2) {
    u8 *global_base;
    u8 temp_v1;

    if (arg0 == D_800E3D7C[0]) {
        ((S_800C3C08_0 *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800C3D24();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((S_800C3C08_0 *)arg0)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C3D24();
            return 1;
        }
    }
    temp_v1 = ((S_800C3C08_0 *)arg0)->unk_03;
    if (temp_v1 < 0xFFU) {
        ((S_800C3C08_0 *)arg0)->unk_03 = (u8) (temp_v1 + 1);
        if (((S_800C3C08_0 *)arg0)->unk_14 & 0x4000) {
            func_80099844(arg0, D_800E1843);
        }
    }
    func_800D4FC8(arg0 - 0x20, 0x202020, 0x616);
    func_80098B38(arg1);
    global_base = (u8 *)&D_80083460;
    
    ((S_800C3C08_1 *)global_base)->unk_0A = (u16) (((S_800C3C08_1 *)global_base)->unk_0A - 1);
    return 1;
}
/* MECHANISM: The natural args produce the 0x20 frame and s0/s1 holds; the first callee needs four args.
   A void dispatcher plus explicit 0/1 returns gives the two LEAD-22 SHAPE-C jump delay values.
   ASM_KEEP holds &D_80083460 so its addiu base and 0xA lhu/sh displacements remain split. */
