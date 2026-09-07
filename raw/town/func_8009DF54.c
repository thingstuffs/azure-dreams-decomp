#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80095388(void *);
extern void func_8009539C(void *);
extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern s32 func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern void func_8009B778(void *, void *);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(u16);
extern void func_80053DA8(u32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];
extern u8 D_800FE488[];

void func_8009B6B4(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s16 result;
    s32 signed_result;

    func_80095388(arg2);
    if (FIELD(arg2, s32, 0x14) > 0x200000) {
        FIELD(arg2, s32, 0x14) = 0x200000;
    }
    func_8009539C(arg2);
    result = func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    signed_result = result;
    if (FIELD(arg2, s16, 0xA) >= signed_result) {
        func_8008F27C(arg1, arg2, signed_result);
        func_8009B778(arg0, arg1);
        return;
    }
    if (FIELD(arg1, u8, 0x3B) != 0) {
        FIELD(arg2, s32, 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)arg0 + 0x58)))[1](arg0, arg1, arg2, arg3);
    }
    if ((FIELD(arg0, u16, -2) & 0x8000) == 0 &&
        D_8009B454 == FIELD(arg0, void *, 0x50)) {
        s32 index;

        index = func_800C1D44((u16)func_8008C180(
            FIELD(arg2, s16, 2), FIELD(arg2, s16, 6)));
        if (index != 0) {
            s16 *thresholds = D_800D45AA;
            s16 height = FIELD(arg2, s16, 0xA);
            s16 threshold = thresholds[index];

            if (height > threshold) {
                func_80053DA8(0x517);
            }
        }
    }
}
