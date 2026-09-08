#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0824_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xCC];
    void * unk_D0;
} S_800B0824_0;   /* arg0 in func_800B0824; pointer addresses record offset 0x10 */

typedef struct S_800B0824_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B0824_1;   /* temp_v0 in func_800B0824 */

typedef struct S_800B0824_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B0824_2;   /* temp_v1 in func_800B0824 */


extern M2C_UNK D_800B07D0;

/* Increase the subrecord value by 0x200, clamp it to 0x1000, and switch handlers at the limit. */
void func_800B0824(void *record_data) {
    S_800B0824_1 *subrecord;
    S_800B0824_2 *updated_subrecord;

    subrecord = ((S_800B0824_0 *)((u8 *)record_data - 0x10))->unk_D0;
    subrecord->unk_06 = (u16) (subrecord->unk_06 + 0x200);
    updated_subrecord = ((S_800B0824_0 *)((u8 *)record_data - 0x10))->unk_D0;
    if ((s16) updated_subrecord->unk_06 >= 0x1000) {
        updated_subrecord->unk_06 = 0x1000U;
        ((S_800B0824_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800B07D0;
    }
}
