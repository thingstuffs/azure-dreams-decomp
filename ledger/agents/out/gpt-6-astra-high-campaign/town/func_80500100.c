#include "common.h"

extern void *D_80016000[];
extern u8 D_80017478[];
extern void *D_80017548[];
extern void func_80017350();

/* Selects the default data, enforces a minimum field value of 20, and triggers 0x552 and 0x553. */
void func_80500100(void) {
    void *town_state;
    void *field_base;
    s32 field_value;

    town_state = D_80016000[0];
    field_base = *(void **)((u8 *)town_state + 0x38);
    field_value = *(s16 *)((u8 *)field_base + 0x35BC);
    D_80017548[0] = D_80017478;
    if (field_value < 20) {
        *(s16 *)((u8 *)field_base + 0x35BC) = 20;
    }
    func_80017350(0x552, field_base);
    func_80017350(0x553);
}

/* MECHANISM: The retail frame is 24 bytes with only ra saved.
   Preserve the two-load D_80016000 -> +0x38 object chain so a1 holds the field base.
   Hold the signed-halfword read in s32 before the independent global store: this selects
   a direct lh, lets its low-half address fill the delay, and puts sw in the branch slot. */
