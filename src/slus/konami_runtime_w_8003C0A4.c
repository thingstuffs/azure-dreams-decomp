#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003C0A4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8003C0A4_0;   /* arg1 in runtime_set_destination_flag_from_source */

typedef struct S_8003C0A4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_8003C0A4_1;   /* arg0 in runtime_set_destination_flag_from_source */


/* Set the destination flag when the source value is nonzero. */
void runtime_set_destination_flag_from_source(S_8003C0A4_1 *dest, S_8003C0A4_0 *source) {
    if (source->unk_08 != 0) {
        dest->unk_04 = 1;
    }
}
