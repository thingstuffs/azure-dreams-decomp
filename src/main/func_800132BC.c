#include "common.h"

typedef s32 M2C_UNK;

extern void *func_80020984(void);
extern s32 func_80021F18(s32, s32);
extern M2C_UNK func_80022EEC(void *);
extern M2C_UNK func_800241D4(s32, s32);
extern M2C_UNK func_80024F3C(s32, s32, s32);
extern M2C_UNK func_80026128(s32, s32, s32);
extern M2C_UNK func_80026270(void *);
#ifndef NON_MATCHING
extern void func_80026378(void);
#else
extern void func_80026378(void *);
#endif
extern M2C_UNK SD_Call(s32);
extern M2C_UNK func_800A6104(void);

extern s16 D_80010208[];
extern M2C_UNK D_800261C0[];
extern M2C_UNK D_80026240[];
extern M2C_UNK D_800265B8[];

#ifndef NON_MATCHING
register u8 * volatile call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

void *func_800262BC(void *arg0) {
#ifndef NON_MATCHING
    register u8 *dead_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#endif
    void *result;

    func_80026128(0x80010000, *(s32 *)((s8 *)arg0 + 0x2C), *(s32 *)((s8 *)arg0 + 0x24));
    if (func_80021F18(*(s32 *)((s8 *)arg0 + 0x2C), 0x80010000) == 0) {
#ifndef NON_MATCHING
        call_a0 = (u8 *)arg0 - 0x20;
        dead_v0 = (u8 *)D_800265B8;
        *(u8 **)((s8 *)arg0 + 0x34) = dead_v0;
        func_80022EEC(call_a0);
#else
        *(void **)((s8 *)arg0 + 0x34) = D_800265B8;
        func_80022EEC((s8 *)arg0 - 0x20);
#endif
#ifndef NON_MATCHING
        dead_v0 = (u8 *)0x80020000;
        ASM_KEEP(dead_v0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_80026378();
        return dead_v0 + 0x61C0;
#else
        func_80026378(D_800261C0);
        return D_800261C0;
#endif
    }
    func_80024F3C(*(s32 *)((s8 *)arg0 + 4), *(s32 *)((s8 *)arg0 + 0x2C), 3);
    func_80026270(arg0);
#ifndef NON_MATCHING
    dead_v0 = (u8 *)(u32)*(s32 *)((s8 *)arg0 + 0x2C);
    dead_v0 = (u8 *)((u32)dead_v0 << 2);
    dead_v0 = (u8 *)((u32)dead_v0 + (u32)arg0);
    func_800241D4(*(s32 *)(dead_v0 + 0xC), 1);
    dead_v0 = (u8 *)0x80010000;
    __asm__ __volatile__("" : "=r"(dead_v0) : "0"(dead_v0));
    dead_v0 = (u8 *)(s32)*(s16 *)(dead_v0 + 0x208);
    if (dead_v0 == 0) {
#else
    func_800241D4(*(s32 *)((s8 *)arg0 + *(s32 *)((s8 *)arg0 + 0x2C) * 4 + 0xC), 1);
    if (D_80010208[0] == 0) {
#endif
        SD_Call(0x503);
#ifndef NON_MATCHING
        dead_v0 = (u8 *)0x80020000;
        ASM_KEEP(dead_v0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        dead_v0 += 0x65B8;
        *(u8 **)((s8 *)arg0 - 0x10) = dead_v0;
#else
        *(void **)((s8 *)arg0 - 0x10) = D_800265B8;
#endif
        result = func_80020984();
        *(s32 *)((s8 *)arg0 + 0x40) = 0;
        return result;
    }

    func_800A6104();
#ifndef NON_MATCHING
    dead_v0 = (u8 *)0x80020000;
    ASM_KEEP(dead_v0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    func_80026378();
    return dead_v0 + 0x6240;
#else
    func_80026378(D_80026240);
    return D_80026240;
#endif
}
