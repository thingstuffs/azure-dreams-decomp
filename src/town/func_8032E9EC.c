#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001ACE8();                     /* extern */

typedef struct S_800191EC_0 {
    u8 unk_00;
    u8 unk_01;
} S_800191EC_0;   /* arg0 in func_800191EC */

void func_800191EC(S_800191EC_0 *arg0) {
    if ((arg0->unk_01 == 0xD) && (arg0->unk_00 == 2)) {
        func_8001ACE8(0x11F8);
    }
}
