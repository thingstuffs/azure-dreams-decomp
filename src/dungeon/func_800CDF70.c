#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

#ifdef NON_MATCHING
#define ASM_CLOBBER_A0() ((void)0)
#else
#define ASM_CLOBBER_A0() ASM_CLOBBER("$4")
#endif

extern void func_800D3738(void *arg0, s32 arg1, Entry *arg2, s16 arg3);

s32 func_800D36D0(void *arg0, s32 arg1, Entry *arg2)
{
    register void *state ASM_REG("$16") = arg0;

    ASM_CLOBBER_A0();
    for (;;) {
        if (!(arg2->unk14 & 0x80)) {
            func_800D3738(state, arg1, arg2, arg2->unk06);
        }
        arg2 = *(Entry **)((u8 *)state - 8);
        if (arg2 == 0) {
            break;
        }
        state = (u8 *)arg2 + 0x20;
        arg1 = (s32)arg2->unk08;
        arg2 = arg2->unk0C;
    }
    return 0;
}
