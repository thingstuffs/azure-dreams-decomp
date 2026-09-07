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


void func_80036988(S_80036988_0 *arg0, S_80036988_1 *arg1) {
    arg0->unk_08 = (s16) (arg1->unk_00 + arg1->unk_08);
    arg0->unk_0A = (s16) (arg1->unk_02 + arg1->unk_0A);
    arg0->unk_0C = (u16) arg1->unk_0C;
    arg0->unk_0E = (u16) arg1->unk_0E;
}
