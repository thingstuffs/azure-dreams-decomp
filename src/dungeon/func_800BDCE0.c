#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern void func_80042B68(void *, s32);
extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern s32 func_800AD6FC(void *, s32, s32);
extern s32 func_800C3674(void);
extern void func_800C4D78(s32, s32);

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1756[];
extern u8 D_800E176F[];
extern u8 D_800E1788[];
extern u8 *D_800E3D7C;

s32 func_800C3440(void *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    u8 *obj;
    s32 value;
    s32 active;

    if (arg2 == 13) {
        func_80098864(arg1, arg3);
        return func_800C3674();
    }

    if (arg0 == D_800E3D7C) {
        *(s32 *)((u8 *)arg0 + 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1);
        if (func_800AD6FC(arg0,
                          D_800DDE84[((u8 *)arg0)[0x13]] & 3,
                          arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        func_800C4D78(0xC0C0C0, 0);
        func_800A56E0(0x702);
        func_80042B68(arg0, 8);

        active = 0;
        obj = *(u8 **)(D_800E3D7C + 0x4C);
        if (obj[1] != 0 && (obj[3] & 0x40) != 0) {
            obj[3] &= 0xBF;
            value = func_800990FC();
            func_80099290(func_80099194(D_800E1756,
                                        func_80099368(obj, value)));
            func_800A5720(value);
            active = 1;
        }

        obj = *(u8 **)(D_800E3D7C + 0x50);
        if (obj[1] != 0 && (obj[3] & 0x40) != 0) {
            obj[3] &= 0xBF;
            value = func_800990FC();
            func_80099290(func_80099194(D_800E176F,
                                        func_80099368(obj, value)));
            func_800A5720(value);
            active = 1;
        }

        if (active == 0) {
            value = func_800990FC();
            func_80099290(func_80099194(D_800E1788, value));
            func_800A5720(value);
        }
    }

    D_80083460.fieldA--;
    func_80098B38(arg1);
    return 1;
}
