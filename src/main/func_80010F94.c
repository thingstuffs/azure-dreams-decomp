#include "common.h"

typedef struct S_80023F94_0 {
    s32 unk_00;
    s32 unk_04;
} S_80023F94_0;   /* arg0 in cardBootSetSlotIndexAndOwner */

/* Sets both values in the pair. */
void cardBootSetSlotIndexAndOwner(S_80023F94_0 *pair, s32 second, s32 first) {
    pair->unk_00 = first;
    pair->unk_04 = second;
}
