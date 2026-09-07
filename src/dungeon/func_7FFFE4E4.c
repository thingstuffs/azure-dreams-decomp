#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

extern void func_80095388(void *);
extern void func_8009539C(void *);
extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(u16);
extern void func_80053DA8(s32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];
extern u8 D_800FE488[];

void func_7FFFE4E4(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s16 result;
    s32 signed_result;

    func_80095388(arg2);
    if (*(s32 *)((u8 *)arg2 + 0x14) > 0x200000) {
        *(s32 *)((u8 *)arg2 + 0x14) = 0x200000;
    }
    func_8009539C(arg2);
    result = func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    signed_result = result;
    if (*(s16 *)((u8 *)arg2 + 0xA) >= signed_result) {
        func_8008F27C(arg1, arg2, signed_result);
        ((Callback *)(*(void **)((u8 *)arg0 + 0x58)))[1](arg0, arg1, arg2, arg3);
    } else if (*(u8 *)((u8 *)arg1 + 0x3B) != 0) {
        *(s32 *)((u8 *)arg2 + 0xC) = 0;
        *(s32 *)((u8 *)arg2 + 0x10) = 0;
        *(s32 *)((u8 *)arg2 + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)arg0 + 0x58)))[1](arg0, arg1, arg2, arg3);
    }
    if ((*(u16 *)((u8 *)arg0 - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)arg0 + 0x50) == D_8009B454) {
        s32 index;

        index = func_800C1D44((u16)func_8008C180(
            *(s16 *)((u8 *)arg2 + 2), *(s16 *)((u8 *)arg2 + 6)));
        if (index != 0) {
            s16 height = *(s16 *)((u8 *)arg2 + 0xA);
            s16 threshold = D_800D45AA[index];

            if (height > threshold) {
                func_80053DA8(0x517);
            }
        }
    }
}
