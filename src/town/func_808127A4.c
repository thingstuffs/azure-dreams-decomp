#include "common.h"
#include "shared/types3b_types.h"

   /* the 0x2 bytes before arg0 in animate_linked_value_threshold, addressed as arg0[-1] */

typedef struct S_808127A4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    s32 unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    union { s16 s; u16 u; } unk_16;   /* accessed as both */
} S_808127A4_0;   /* arg0 in animate_linked_value_threshold */

typedef struct S_808127A4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_808127A4_1;


s32 func_80058588(s32, s32, s32);
extern s32 D_80084D5C;

void animate_linked_value_threshold(void *record_ptr) {
    u16 *flags;
    s16 state;
    u16 threshold_value;
    void *related_record;

    state = ((S_808127A4_0 *)record_ptr)->unk_00.s;
    related_record = ((S_808127A4_0 *)record_ptr)->unk_0C;
    switch (state) {
    case 0:
        func_80058588(*((S_808127A4_0 *)record_ptr)->unk_08 * 0x3E8, 5, ((S_808127A4_0 *)record_ptr)->unk_04 + 4);
        if (((S_808127A4_1 *)related_record)->unk_5C != 3) {
            break;
        }
        if (((S_808127A4_0 *)record_ptr)->unk_16.s >= 0x78) {
            ((S_808127A4_0 *)record_ptr)->unk_02.s = 8;
        } else {
            ((S_808127A4_0 *)record_ptr)->unk_02.s = -8;
        }
        ((S_808127A4_0 *)record_ptr)->unk_00.u++;
        break;
    case 1:
        ((S_808127A4_0 *)record_ptr)->unk_16.u += ((S_808127A4_0 *)record_ptr)->unk_02.u;
        ((S_808127A4_0 *)record_ptr)->unk_16.u += ((S_808127A4_0 *)record_ptr)->unk_02.s >> 2;
        threshold_value = (((S_808127A4_0 *)record_ptr)->unk_16.u + 8) & 0xFFFF;
        if (threshold_value >= 0xF9U) {
            flags = &((ObjectStatusPrefix16 *)record_ptr)[-1].unk_00;
            *flags = (u16) (((ObjectStatusPrefix16 *)record_ptr)[-1].unk_00 | 0x8000);
            *(s32 *) 0x80084D5C = D_80084D5C | 0x8000;
        }
    }
}

/* MECHANISM: Retail-order state cases preserve the 0x20 s0/s1 frame and CFG.
   Noreturn tails plus named fences hold both RMW and delay-slot store shapes.
   Split predicate/read lifetimes and signed s16 arm stores recover a0/v1/v0 roles.
   Symbolic load plus literal store forces independent global load/store bases. */
