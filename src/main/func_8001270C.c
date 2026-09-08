#include "common.h"

extern void func_800250E8(void *arg0, s32 arg1);
extern void func_80025770(void) __attribute__((noreturn));
extern void func_800230A4(void *arg0, s32 arg1);

extern s32 D_8002593C;
extern s32 D_80024FAC;

#ifndef NON_MATCHING
register u8 *match_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

void func_8002570C(void *arg0) {
#ifndef NON_MATCHING
    s32 temp_a1;
    s32 idx;
    void *call_arg;

    match_v0 = (u8 *)0x80080000;
    __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
    temp_a1 = *(s32 *)((u8 *)arg0 + 0x28);
    match_v0 += 0x3E98;
    idx = temp_a1 << 7;
    idx += (u32)match_v0;
    match_v0 = (u8 *)*(u32 *)idx;

    if (match_v0 != 0) {
        *(s32 *)((u8 *)arg0 + 0x2C) = temp_a1;
        func_800250E8(arg0, temp_a1);
        match_v0 = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
        match_v0 += 0x5584;
        func_80025770();
        return;
    }
    call_arg = (u8 *)arg0 - 0x20;
    ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    match_v0 = (u8 *)0x80020000;
    __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
    match_v0 += 0x593C;
    *(u8 **)((u8 *)arg0 + 0x34) = match_v0;
    func_800230A4(call_arg, temp_a1);
    match_v0 = (u8 *)0x80020000;
    __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
    match_v0 += 0x4FAC;
    *(u8 **)((u8 *)arg0 - 0x10) = match_v0;
#else
    extern s32 D_80083E98[];
    s32 temp_a1 = *(s32 *)((u8 *)arg0 + 0x28);

    if (D_80083E98[temp_a1 * 32] != 0) {
        *(s32 *)((u8 *)arg0 + 0x2C) = temp_a1;
        func_800250E8(arg0, temp_a1);
        func_80025770();
        return;
    }
    *(s32 **)((u8 *)arg0 + 0x34) = &D_8002593C;
    func_800230A4((u8 *)arg0 - 0x20, temp_a1);
    *(s32 **)((u8 *)arg0 - 0x10) = &D_80024FAC;
#endif
}
