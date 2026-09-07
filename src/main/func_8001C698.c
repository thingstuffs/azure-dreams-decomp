#include "common.h"
#include "m2c_compat.h"

s32 func_80056F14();
extern M2C_UNK D_80082FF4;
extern M2C_UNK D_80083060;
extern M2C_UNK D_8008306C;

typedef struct S_8001C698_0 {
    u8 pad_00[0x1B8];
    s32 * unk_1B8;
    M2C_UNK ** unk_1BC;
} S_8001C698_0;   /* arg0 in func_8001C698 */

typedef struct S_8001C698_1 {
    u8 pad_00[0x1C0];
    void ** unk_1C0;
    u8 pad_1C4[0xC];
    void ** unk_1D0;
    u8 pad_1D4[0xC];
    void ** unk_1E0;
    u8 pad_1E4[0xC];
    void ** unk_1F0;
} S_8001C698_1;   /* var_a0 in func_8001C698 */

void func_8001C698(void *arg0) {
    s32 var_a1;
    s32 var_a2;
    void *g1;
    void *g2;
    void *base4;
    void *var_a0;

    *((S_8001C698_0 *)arg0)->unk_1B8 = func_80056F14(4);
    *((S_8001C698_0 *)arg0)->unk_1BC = &D_80082FF4;
    var_a2 = 0;
    g1 = &D_80083060;
    g2 = &D_8008306C;
    base4 = arg0 + 4;
    var_a1 = 0x90;
    var_a0 = arg0;
    do {
        *((S_8001C698_1 *)var_a0)->unk_1C0 = g1;
        *((S_8001C698_1 *)var_a0)->unk_1D0 = g2;
        *((S_8001C698_1 *)var_a0)->unk_1E0 = base4;
        *((S_8001C698_1 *)var_a0)->unk_1F0 = arg0 + var_a1;
        var_a1 += 0x3C;
        var_a2 += 1;
        var_a0 += 4;
    } while (var_a2 < 4);
}
