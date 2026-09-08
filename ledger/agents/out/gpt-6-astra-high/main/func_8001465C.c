#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002765C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x4C];
    s32 unk_50;
} S_8002765C_0;   /* arg0 in func_8002765C; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80027584;

/* Decrement the record's countdown and switch its handler when it becomes negative. */
void func_8002765C(void *record_data) {
    s32 countdown;

    countdown = ((S_8002765C_0 *)((u8 *)record_data - 0x10))->unk_50 - 1;
    ((S_8002765C_0 *)((u8 *)record_data - 0x10))->unk_50 = countdown;
    if (countdown < 0) {
        ((S_8002765C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80027584;
    }
}
