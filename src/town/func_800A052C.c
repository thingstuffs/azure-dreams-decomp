#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_80047784();        /* extern */
extern s32 D_80081458[];
extern M2C_UNK D_800D07A4[];
extern s16 D_800D07AC;




void func_8009DC8C(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    if (arg2 == 2) {
        ((Rec_func_80094268_arg0 *)arg0)->unk_93 = 1;
        (*(s32 *)((u8 *)arg1 + (0x28))) = D_80081458[0];
        func_80047784(arg1, D_800D07AC, 0);
        return;
    }
    func_8003DB94(arg1, D_800D07A4[arg2], 0);
    if (arg3 & 2) {
        ((Rec_D_80082E80 *)arg1)->unk_12.at00_s16.v = 0x100;
        return;
        ASM_MEM_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
        return;
    }
    if (arg3 & 4) {
        ((Rec_D_80082E80 *)arg1)->unk_12.at00_s16.v = 0x200;
        return;
    }
    ((Rec_D_80082E80 *)arg1)->unk_12.at00_s16.v = 0;
}

/* MECHANISM: Void tail-call ABI preserves the three retail jumps and their delay slots.
   A one-sided ASM_MEM_BARRIER prevents merging the twin flag-store tails.
   Word-array indexing emits sll(a2,2); natural liveness yields the 0x20 s0/s1 frame. */
