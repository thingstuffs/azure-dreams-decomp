#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A8B98_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x78];
    s16 unk_7C;
    u8 pad_7E[0x28];
    s8 unk_A6;
} S_800A8B98_0;   /* arg0 in func_800A8B98; pointer addresses record offset 0x10 */

typedef struct S_800A8B98_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A8B98_1;   /* arg1 in func_800A8B98 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800A8ADC;

/* Sets the record's pointer and state and copies its signed byte to the output's high half. */
void func_800A8B98(void *record_data, S_800A8B98_1 *output) {
    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A8ADC;
    output->unk_08 = (s32) (((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_A6 << 0x10);
    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_7C = 5;
}
