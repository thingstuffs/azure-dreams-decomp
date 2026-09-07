#include "common.h"

extern void *D_80016000[];
extern u8 D_80017478[];
extern void *D_80017548[];
extern void func_80017350();

void func_80500100(void) {
    void *temp_v0;
    void *temp_a1;
    s32 temp_v1;

    temp_v0 = D_80016000[0];
    temp_a1 = *(void **)((u8 *)temp_v0 + 0x38);
    temp_v1 = *(s16 *)((u8 *)temp_a1 + 0x35BC);
    D_80017548[0] = D_80017478;
    if (temp_v1 < 20) {
        *(s16 *)((u8 *)temp_a1 + 0x35BC) = 20;
    }
    func_80017350(0x552, temp_a1);
    func_80017350(0x553);
}

/* MECHANISM: The retail frame is 24 bytes with only ra saved.
   Preserve the two-load D_80016000 -> +0x38 object chain so a1 holds the field base.
   Hold the signed-halfword read in s32 before the independent global store: this selects
   a direct lh, lets its low-half address fill the delay, and puts sw in the branch slot. */
