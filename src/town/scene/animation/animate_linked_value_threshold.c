#include "common.h"
#include "shared/object_links.h"
#include "town/scene/animation.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

   /* the 0x2 bytes before arg0 in animate_linked_value_threshold, addressed as arg0[-1] */

typedef struct S_808127A4_0 {
    u16 unk_00;
    s16 unk_02;
    s32 unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
} S_808127A4_0;   /* arg0 in animate_linked_value_threshold */

typedef struct S_808127A4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_808127A4_1;



/* Passes the linked value times 1000 to func_80058588, then moves field +0x16 until removal. */
void animate_linked_value_threshold(void *record_ptr_arg) {
    S_808127A4_0 *record_ptr = record_ptr_arg;
    u16 *flags;
    s16 state;
    u16 threshold_value;
    S_808127A4_1 *related_record;

    state = ((s16)record_ptr->unk_00);
    related_record = record_ptr->unk_0C;
    switch (state) {
    case 0:
        func_80058588(*record_ptr->unk_08 * 0x3E8, 5, record_ptr->unk_04 + 4);
        if (related_record->unk_5C != 3) {
            break;
        }
        if (((s16)record_ptr->unk_16) >= 0x78) {
            record_ptr->unk_02 = 8;
        } else {
            record_ptr->unk_02 = -8;
        }
        record_ptr->unk_00++;
        break;
    case 1:
        record_ptr->unk_16 += ((u16)record_ptr->unk_02);
        record_ptr->unk_16 += record_ptr->unk_02 >> 2;
        threshold_value = (record_ptr->unk_16 + 8) & 0xFFFF;
        if (threshold_value >= 0xF9U) {
            flags = &((ObjectStatusPrefix16 *)record_ptr)[-1].flags;
            *flags = (u16) (((ObjectStatusPrefix16 *)record_ptr)[-1].flags | 0x8000);
            *(s32 *) 0x80084D5C = scene_object_flags | 0x8000;
        }
    }
}

/* MECHANISM: Retail-order state cases preserve the 0x20 s0/s1 frame and CFG. Split predicate/read
   lifetimes and signed s16 arm stores recover a0/v1/v0 roles. Symbolic load plus literal store forces
   independent global load/store bases. */
