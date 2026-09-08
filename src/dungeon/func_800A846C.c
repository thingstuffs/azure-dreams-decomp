#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

typedef struct {
    u8 pad[0x13C];
    s32 flag;
} Scratchpad;

extern void func_800453E0(void *arg0, s32 arg1, Entry *arg2, s16 arg3);
#ifndef NON_MATCHING
extern void func_800ADBE4(void);
#else
extern void func_800ADBE4(void) __attribute__((noreturn));
#endif

s32 func_800ADBCC(void *arg0, s32 arg1, Entry *arg2)
{
    void *state = arg0;
    Scratchpad *scratch =
        (Scratchpad *)0x1F800000;

    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    scratch->flag = *(s16 *)((u8 *)state + 8);
    if (!(arg2->unk14 & 0x80)) {
        func_800453E0(state, arg1, arg2, arg2->unk06);
    }

    arg2 = *(Entry **)((u8 *)state - 8);
    if (arg2 != 0) {
        state = (u8 *)arg2 + 0x20;
        arg1 = (s32)arg2->unk08;
        arg2 = arg2->unk0C;
        ASM_USE(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_USE(arg1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_USE(arg2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_USE(scratch);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_800ADBE4();
    }
    return 0;
}
