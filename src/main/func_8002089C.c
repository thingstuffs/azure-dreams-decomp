#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80083060;
extern M2C_UNK D_8008306C;

typedef struct S_8002089C_0 {
    u8 pad_00[0xF0];
    M2C_UNK ** unk_F0;
    M2C_UNK ** unk_F4;
    void ** unk_F8;
    void ** unk_FC;
} S_8002089C_0;   /* arg0 in func_8002089C */

void func_8002089C(void *arg0) {
    *((S_8002089C_0 *)arg0)->unk_F0 = &D_80083060;
    *((S_8002089C_0 *)arg0)->unk_F4 = &D_8008306C;
    *((S_8002089C_0 *)arg0)->unk_F8 = arg0 + 4;
    *((S_8002089C_0 *)arg0)->unk_FC = arg0 + 0x7C;
}
