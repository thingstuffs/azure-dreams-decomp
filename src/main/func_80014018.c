#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80077EF0;
extern M2C_UNK D_80077EFC;

typedef struct S_80027018_0 {
    u8 pad_00[0xF0];
    M2C_UNK ** unk_F0;
    M2C_UNK ** unk_F4;
    void ** unk_F8;
    void ** unk_FC;
} S_80027018_0;   /* arg0 in func_80027018 */

void func_80027018(void *arg0) {
    *((S_80027018_0 *)arg0)->unk_F0 = &D_80077EF0;
    *((S_80027018_0 *)arg0)->unk_F4 = &D_80077EFC;
    *((S_80027018_0 *)arg0)->unk_F8 = arg0 + 4;
    *((S_80027018_0 *)arg0)->unk_FC = arg0 + 0x7C;
}
