#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9858_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    M2C_UNK * unk_60;
} S_800A9858_0;   /* arg0 in func_800A9858; pointer addresses record offset 0x10 */

typedef struct S_800A9858_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A9858_1;   /* arg1 in func_800A9858 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800A97F8;
extern M2C_UNK D_800A6CF0;

/* Initialize the record's pointers and clear the associated state field. */
void func_800A9858(void *record_data, S_800A9858_1 *state) {
    ((S_800A9858_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A9858_0 *)((u8 *)record_data - 0x10))->unk_60 = &D_800A97F8;
    state->unk_08 = 0;
}
