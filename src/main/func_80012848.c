#include "common.h"

extern void func_800230A4(void *arg0);
extern void func_80023144(void *arg0, void *arg1);
extern void func_800258AC(void) __attribute__((noreturn));

extern s32 D_80083E98[][32];
extern s32 D_80025788;
extern s32 D_8002593C;
extern s32 D_80024FAC;

#ifndef NON_MATCHING
register u8 *match_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

void func_80025848(void *arg0) {
#ifndef NON_MATCHING
    void *temp_a0;
    s32 idx;

    match_v0 = (u8 *)0x80080000;
    __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
    idx = *(s32 *)((u8 *)arg0 + 0x28);
    match_v0 += 0x3E98;
    idx <<= 7;
    idx += (u32)match_v0;
    match_v0 = (u8 *)*(u32 *)idx;
    temp_a0 = (u8 *)arg0 - 0x20;

    if (match_v0 != 0) {
        void *arg1;

        match_v0 = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
        match_v0 += 0x5788;
        arg1 = (u8 *)arg0 + 0x38;
        __asm__ __volatile__("" ::: "memory");
        *(u8 **)((u8 *)arg0 + 0x34) = match_v0;
        func_80023144(temp_a0, arg1);
        match_v0 = (u8 *)0x80020000;
        func_800258AC();
    } else {
        match_v0 = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
        match_v0 += 0x593C;
        *(u8 **)((u8 *)arg0 + 0x34) = match_v0;
        func_800230A4(temp_a0);
        match_v0 = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(match_v0) : "0"(match_v0));
        match_v0 += 0x4FAC;
        *(u8 **)((u8 *)arg0 - 0x10) = match_v0;
    }
#else
    void *a0 = (u8 *)arg0 - 0x20;
    s32 idx = *(s32 *)((u8 *)arg0 + 0x28);

    if (D_80083E98[idx][0] != 0) {
        s32 *v = &D_80025788;
        void *a1 = (u8 *)arg0 + 0x38;
        __asm__ __volatile__("" ::: "memory");
        *(s32 **)((u8 *)arg0 + 0x34) = v;
        func_80023144(a0, a1);
        func_800258AC();
    } else {
        *(s32 **)((u8 *)arg0 + 0x34) = &D_8002593C;
        func_800230A4(a0);
        *(s32 **)((u8 *)arg0 - 0x10) = &D_80024FAC;
    }
#endif
}
