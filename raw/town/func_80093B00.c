#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80033B2C();
extern void func_8008B158();
extern s32 func_8008C180();
extern void func_80091504();
extern void func_80093D48();
extern void func_80093E58();
extern void func_80093F48();
extern void func_80093FC8();
extern void func_80094088();
extern void func_800942B0();
extern void func_80094378();
extern void func_800943B8();
extern void func_800944BC();
extern void func_8009451C();
extern void func_80094944();
extern void func_80094C1C();
extern void func_80094C74();
extern void func_80094DA8();
extern void func_8009503C();
extern void func_800951B4();
extern s32 func_8009567C();
extern s32 func_80095840();
extern s16 func_80095978();
extern void func_80095A94();
extern void func_80095C80();
extern void func_80098868();
extern s32 func_800C1D44();

extern u8 D_80083160[];
extern s32 D_800CFCB4[];
extern u8 D_800CFCEF[];
extern u8 D_800FE488[];

void func_80091260(void *arg0, void *arg1, s32 arg2) {
    u8 *state = D_80083160;
    s32 result;
    s16 value;
    s32 *data;

    func_80095C80(arg1);
    func_800951B4(arg1);

    value = func_80095978(arg1, D_800FE488);
    if ((value - FIELD(arg1, s16, 0xA)) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(arg0, arg1, arg2);
            func_80091504();
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, value, D_800FE488);
    }

    result = FIELD(state, s32, 0x10);
    if (result & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        func_80091504();
        return;
    }

    if (result & 0x40) {
        result = func_80095840(arg0, D_800CFCB4);
        if (result != 0) {
            if (result == 2) {
                func_8009451C(arg0, arg1, arg2);
                func_80091504();
                return;
            } else {
                func_800944BC(arg0, arg1, arg2);
                func_80091504();
                return;
            }
        } else if (func_80033B2C(0xA4) != 0) {
            func_80094088(arg0, arg1, arg2);
            func_80091504();
            return;
        }
        return;
    }

    data = D_800CFCB4;
    result = func_8009567C(data);
    if (result != 0) {
        if (result == -1) {
            func_80094C1C(arg0);
            func_80098868(arg0, arg1, arg2);
            FIELD(arg0, s32, 0x2C) = 0;
            func_8008B158(data[4]);
            func_80091504();
            return;
        } else {
            func_800943B8(arg0, arg1, arg2);
            func_80091504();
            return;
        }
        return;
    }

    result = FIELD(state, s32, 8);
    if (result & 0x20) {
        if (FIELD(arg0, s16, 0x16) == 1) {
            result = func_8008C180(FIELD(arg1, s16, 2), FIELD(arg1, s16, 6));
            if (func_800C1D44((u16)result) != 0 && FIELD(arg1, s32, 8) > 0) {
                func_80093FC8(arg0, arg1, arg2);
                func_80091504();
                return;
            } else {
                func_80093E58(arg0, arg1, arg2);
                func_80091504();
                return;
            }
        } else {
            func_80093F48(arg0, arg1, arg2);
            func_80094C1C(arg0);
            func_8009503C(arg1);
            func_80091504();
            return;
        }
        return;
    }

    if (result & 0xF000) {
        value = FIELD(arg0, u16, 0x3E) - 1;
        FIELD(arg0, s16, 0x3E) = value;
        func_80094944(value, 12);
        func_80094C1C(arg0);
        func_80094C74(arg1);
        func_80094DA8(arg1);
        func_80091504();
        return;
    } else {
        func_80093D48(arg0, arg1, arg2);
    }
}
