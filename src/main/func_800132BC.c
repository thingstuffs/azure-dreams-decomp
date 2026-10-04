#include "common.h"

typedef s32 M2C_UNK;

extern void *func_80020984(void);
extern s32 func_80021F18(s32, s32);
extern void func_80022EEC(void *);
extern void func_800241D4(s32, s32);
extern void func_80024F3C(s32, s32, s32);
extern void func_80026128(s32, s32, s32);
extern void func_80026270(void *);
extern M2C_UNK SD_Call(s32);
extern M2C_UNK func_800A6104(void);

extern s16 D_80010208[];
extern M2C_UNK D_800261C0[];
extern M2C_UNK D_80026240[];
extern M2C_UNK D_800265B8[];


/* Processes the current selection and stores the next state. */
void *func_800262BC(void *context) {
    void *result;

    func_80026128(0x80010000, *(s32 *)((s8 *)context + 0x2C), *(s32 *)((s8 *)context + 0x24));
    if (func_80021F18(*(s32 *)((s8 *)context + 0x2C), 0x80010000) == 0) {
        *(u8 **)((s8 *)context + 0x34) = (u8 *)D_800265B8;
        func_80022EEC((u8 *)context - 0x20);
        *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800261C0;
    } else {
        func_80024F3C(*(s32 *)((s8 *)context + 4), *(s32 *)((s8 *)context + 0x2C), 3);
        func_80026270(context);
        func_800241D4(*(s32 *)((s8 *)context + *(s32 *)((s8 *)context + 0x2C) * 4 + 0xC), 1);
        if (D_80010208[0] != 0) {
            func_800A6104();
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_80026240;
        } else {
            SD_Call(0x503);
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800265B8;
        }
    }
    result = func_80020984();
    *(s32 *)((s8 *)context + 0x40) = 0;
    return result;
}
