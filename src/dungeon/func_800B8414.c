#include "common.h"

typedef struct S_800BDB74_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BDB74_0_pre;   /* the 0x18 bytes before arg0 in func_800BDB74, addressed as arg0[-1] */

typedef struct S_800BDB74_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0xF];
    u8 unk_27;
    u8 pad_28[0x41];
    u8 unk_69;
    u8 pad_6A[0xA6];
    s32 unk_110;
} S_800BDB74_0;   /* arg0 in func_800BDB74 */



extern void func_8008D330();
extern void func_80098B38();
extern void func_80099844();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800BDC80();
extern void func_800C4AFC();

typedef struct {
    u8 pad[0xA];
    u16 counter;
} DungeonState;

extern u8 D_80082E80[];
extern DungeonState D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E0F07[];
extern void *D_800E3D7C;

s32 func_800BDB74(void *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        ((S_800BDB74_0 *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((s32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((S_800BDB74_0 *)arg0)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }

    func_800C4AFC(((S_800BDB74_0_pre *)arg0)[-1].unk_00, 0x40C040, arg0);
    ((S_800BDB74_0 *)arg0)->unk_27 = ((S_800BDB74_0 *)arg0)->unk_69;
    if (((S_800BDB74_0 *)arg0)->unk_14 & 0x4000) {
        func_80099844(arg0, D_800E0F07);
    }
    func_80098B38(arg1);
    D_80083460.counter = (u16)(D_80083460.counter - 1);
    return 1;
}
