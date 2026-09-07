#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A188_0 {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
} S_8001A188_0;   /* arg0 in func_8001A188 */

typedef struct S_8001A188_1 {
    u16 unk_00;
    u16 unk_02;
} S_8001A188_1;   /* arg1 in func_8001A188 */

void func_8001A188(S_8001A188_0 *arg0, S_8001A188_1 *arg1) {
    arg0->unk_10 = (u16) arg1->unk_00;
    arg0->unk_12 = (u16) arg1->unk_02;
}
