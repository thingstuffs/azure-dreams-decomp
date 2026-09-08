#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A24A8_1 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800A24A8_1;   /* arg0 in func_800A24A8 */

typedef struct S_800A24A8_2 {
    u8 pad_00[0x6E];
    u16 unk_6E;
} S_800A24A8_2;   /* ((S_800A24A8_1 *)arg0)->unk_10 in func_800A24A8 */




typedef struct S_800A24A8_0 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_800A24A8_0;   /* arg2 in func_800A24A8 */

/* Store the negated value from the source's linked data in the destination. */
void func_800A24A8(S_800A24A8_1 *source, M2C_UNK unused, S_800A24A8_0 *dest) {
    dest->unk_1A = (s16) (0 - ((S_800A24A8_2 *)(source->unk_10))->unk_6E);
}
