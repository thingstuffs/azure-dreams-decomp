#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
        FIELD(arg0, s32, 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800BDC80();
        return 0;
    }

    if ((s32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[FIELD(arg0, u8, 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BDC80();
            return 1;
        }
    }

    func_800C4AFC(FIELD(arg0, s32, -0x18), 0x40C040, arg0);
    FIELD(arg0, u8, 0x27) = FIELD(arg0, u8, 0x69);
    if (FIELD(arg0, s32, 0x14) & 0x4000) {
        func_80099844(arg0, D_800E0F07);
    }
    func_80098B38(arg1);
    D_80083460.counter = (u16)(D_80083460.counter - 1);
    return 1;
}
