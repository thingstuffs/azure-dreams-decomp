#include "common.h"
#include "frontend/libcard.h"

typedef struct S_80023F94_0 {
    s32 unk_00;
    s32 unk_04;
} S_80023F94_0;   /* arg0 in card_boot_set_slot_index_and_owner */

/* Sets both values in the pair. */
void card_boot_set_slot_index_and_owner(S_80023F94_0 *pair, s32 second, s32 first) {
    pair->unk_00 = first;
    pair->unk_04 = second;
}
