#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A188_0 {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
} S_8001A188_0;   /* arg0 in copy_town_record_pair_fields */

typedef struct S_8001A188_1 {
    u16 unk_00;
    u16 unk_02;
} S_8001A188_1;   /* arg1 in copy_town_record_pair_fields */

/* Copies two 16-bit values into the destination's paired fields. */
void copy_town_record_pair_fields(S_8001A188_0 *dest, S_8001A188_1 *src) {
    dest->unk_10 = (u16) src->unk_00;
    dest->unk_12 = (u16) src->unk_02;
}
