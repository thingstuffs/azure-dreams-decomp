#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036988_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
} S_80036988_0;   /* arg0 in func_80036988 */

typedef struct S_80036988_1 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
} S_80036988_1;   /* arg1 in func_80036988 */


/* Copy four fields, adding the source offsets to the first two. */
void func_80036988(S_80036988_0 *destination, S_80036988_1 *source) {
    destination->unk_08 = (s16) (source->unk_00 + source->unk_08);
    destination->unk_0A = (s16) (source->unk_02 + source->unk_0A);
    destination->unk_0C = (u16) source->unk_0C;
    destination->unk_0E = (u16) source->unk_0E;
}
