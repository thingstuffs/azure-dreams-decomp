#include "common.h"

typedef s32 M2C_UNK;

extern void *func_80020984(void);
extern s32 func_80021F18(s32, s32);
extern M2C_UNK func_80022EEC(void *);
extern M2C_UNK func_800241D4(s32, s32);
extern M2C_UNK func_80024F3C(s32, s32, s32);
extern M2C_UNK func_80026128(s32, s32, s32);
extern M2C_UNK func_80026270(void *);
extern M2C_UNK SD_Call(s32);
extern M2C_UNK func_800A6104(void);

extern s16 D_80010208[];
extern M2C_UNK D_800261C0[];
extern M2C_UNK D_80026240[];
extern M2C_UNK D_800265B8[];

#ifndef NON_MATCHING
register u8 * volatile owner ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

/* Processes the current selection and stores the next state. */
void *func_800262BC(void *context) {
#ifndef NON_MATCHING
    u8 *next_state;
#endif
    void *result;

    func_80026128(0x80010000, *(s32 *)((s8 *)context + 0x2C), *(s32 *)((s8 *)context + 0x24));
    if (func_80021F18(*(s32 *)((s8 *)context + 0x2C), 0x80010000) == 0) {
#ifndef NON_MATCHING
        owner = (u8 *)context - 0x20;
        next_state = (u8 *)D_800265B8;
        *(u8 **)((s8 *)context + 0x34) = next_state;
        func_80022EEC(owner);
#else
        *(void **)((s8 *)context + 0x34) = D_800265B8;
        func_80022EEC((s8 *)context - 0x20);
#endif
#ifndef NON_MATCHING
        next_state = (u8 *)&D_800261C0;
#else
        result = D_800261C0;
#endif
    } else {
        func_80024F3C(*(s32 *)((s8 *)context + 4), *(s32 *)((s8 *)context + 0x2C), 3);
        func_80026270(context);
        func_800241D4(*(s32 *)((s8 *)context + *(s32 *)((s8 *)context + 0x2C) * 4 + 0xC), 1);
        if (D_80010208[0] != 0) {
            func_800A6104();
#ifndef NON_MATCHING
            next_state = (u8 *)&D_80026240;
#else
            result = D_80026240;
#endif
        } else {
            SD_Call(0x503);
#ifndef NON_MATCHING
            next_state = (u8 *)0x80020000;
            ASM_KEEP(next_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            next_state += 0x65B8;
#else
            result = D_800265B8;
#endif
        }
    }
#ifndef NON_MATCHING
    *(u8 **)((s8 *)context - 0x10) = next_state;
#else
    *(void **)((s8 *)context - 0x10) = result;
#endif
    result = func_80020984();
    *(s32 *)((s8 *)context + 0x40) = 0;
    return result;
}
