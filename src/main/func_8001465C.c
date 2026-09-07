#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002765C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x4C];
    s32 unk_50;
} S_8002765C_0;   /* arg0 in func_8002765C; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80027584;

void func_8002765C(void *arg0) {
    s32 temp_v0;

    temp_v0 = ((S_8002765C_0 *)((u8 *)arg0 - 0x10))->unk_50 - 1;
    ((S_8002765C_0 *)((u8 *)arg0 - 0x10))->unk_50 = temp_v0;
    if (temp_v0 < 0) {
        ((S_8002765C_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80027584;
    }
}
