#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002546C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8002546C_0;   /* arg0 in func_8002546C; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80025398;

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void func_8002546C(void *record_data) {
    s32 counter;

    counter = ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_4C = counter;
    if (counter < 0) {
        ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80025398;
    }
}
