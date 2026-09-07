#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_8002436C(void) __attribute__((noreturn));
extern void func_80024370(void) __attribute__((noreturn));
extern void func_800243A4(void) __attribute__((noreturn));
extern void func_800478B8(void *arg0);


typedef struct S_80024264_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    void * unk_08;
} S_80024264_0;   /* arg0 in func_80024264 */

typedef struct S_80024264_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024264_1;   /* owner in func_80024264 */


void func_80024264(S_80024264_0 *arg0, s32 arg1, Rec_D_80082E80 *arg2)
{
    s16 state;
    S_80024264_1 *owner;

    owner = arg0->unk_08;
    owner->unk_14++;
    arg0->unk_02.u++;
    func_800478B8(arg2);

    state = arg0->unk_00.s;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_800243A4();
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800243A4();

state_0: {
    u8 value;
    u16 upper;
    u16 lower;

    value = arg2->unk_0C.at02_u8.v;
    upper = arg2->unk_1C.at02_u16.v;
    value++;
    arg2->unk_0C.at02_u8.v = value;
    arg2->unk_0C.at01_u8.v = value;
    arg2->unk_0C.at00_u8.v = value;
    lower = arg2->unk_1C.at00_u16.v;
    upper += 0x10;
    arg2->unk_1C.at02_u16.v = upper;
    lower += 0x100;
    arg2->unk_1C.at00_u16.v = lower;
    func_80024370();
}

state_1: {
    u8 value;
    u16 lower;
    s32 tail_value;

    value = arg2->unk_0C.at02_u8.v;
    lower = arg2->unk_1C.at00_u16.v;
    value++;
    lower += 0x80;
    arg2->unk_0C.at02_u8.v = value;
    arg2->unk_0C.at01_u8.v = value;
    arg2->unk_0C.at00_u8.v = value;
    arg2->unk_1C.at00_u16.v = lower;
    tail_value = arg0->unk_02.s << 8;
    ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_8002436C();
}

state_2: {
    u8 value;
    s32 position;

    value = arg2->unk_0C.at02_u8.v + 6;
    arg2->unk_0C.at02_u8.v = value;
    arg2->unk_0C.at01_u8.v = value;
    arg2->unk_0C.at00_u8.v = value;
    position = arg0->unk_02.s;
    
    arg2->unk_1C.at02_u16.v = (position + 0x10) << 8;
    if (arg0->unk_02.s < arg0->unk_04) {
        goto done;
    }
    arg0->unk_02.u = 0;
    arg0->unk_00.u++;
    func_800243A4();
}

state_3:
    func_800478B8(arg2);

done:
    return;
}

/* MECHANISM: Forward labels recover the retail dispatch/body order while preserving the 0x20 frame and s1/s0 holds.
   Case-scoped sibling locals reproduce the interleaved RMW loads without merging allocator live ranges.
   A scoped tied v0 tail-slot pin exposes the state-1 lh/j/sll continuation contract to maspsx.
   ASM_KEEP preserves the signed state-2 lh, and its explicit done edge fixes the final branch displacement. */
