#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_80047784();        /* extern */
void func_8009DD28();                                /* extern */
extern s32 D_80081458[];
extern M2C_UNK D_800D07A4[];
extern s16 D_800D07AC;


typedef struct S_8009DC8C_0 {
    u8 pad_00[0x93];
    s8 unk_93;
} S_8009DC8C_0;   /* arg0 in func_8009DC8C */

typedef struct S_8009DC8C_1 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_8009DC8C_1;   /* arg1 in func_8009DC8C */

void func_8009DC8C(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    if (arg2 == 2) {
        ((S_8009DC8C_0 *)arg0)->unk_93 = 1;
        (*(s32 *)((u8 *)arg1 + (0x28))) = D_80081458[0];
        func_80047784(arg1, D_800D07AC, 0);
        func_8009DD28();
        return;
    }
    func_8003DB94(arg1, D_800D07A4[arg2], 0);
    if (arg3 & 2) {
        ((S_8009DC8C_1 *)arg1)->unk_12 = 0x100;
        func_8009DD28();
        ASM_MEM_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
        return;
    }
    if (arg3 & 4) {
        ((S_8009DC8C_1 *)arg1)->unk_12 = 0x200;
        func_8009DD28();
        return;
    }
    ((S_8009DC8C_1 *)arg1)->unk_12 = 0;
}

/* MECHANISM: Void tail-call ABI preserves the three retail jumps and their delay slots.
   A one-sided ASM_MEM_BARRIER prevents merging the twin flag-store tails.
   Word-array indexing emits sll(a2,2); natural liveness yields the 0x20 s0/s1 frame. */
