#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800C8A3C();
extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern void *D_800E3D7C[];

typedef struct S_800C4220_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C4220_0;   /* arg0 in func_800C4220 */

s32 func_800C4220(S_800C4220_0 *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C[0]) {
        arg0->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((s32)arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0,
                         (D_800DDE84[arg0->unk_13] >> 6) & 3,
                         0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }
    if (func_800C8A3C(arg0, 0x400, 8) != 0) {
        func_800A56E0(0x520);
    }
    func_80098B38(arg1);
    D_80083460.fieldA--;
    return 1;
}
