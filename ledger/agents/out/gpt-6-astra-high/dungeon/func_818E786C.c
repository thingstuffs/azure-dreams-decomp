#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002506C_0 {
    void * unk_00;
} S_8002506C_0;   /* arg0 in func_8002506C; pointer addresses record offset 0x14 */

typedef struct S_8002506C_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8002506C_1;   /* temp_a0 in func_8002506C */

typedef struct S_8002506C_2 {
    u16 unk_00;
    u16 unk_02;
} S_8002506C_2;   /* temp_v1 in func_8002506C */


extern u8 D_80024004[24];

/* Copy the selected pair of table values into the linked record. */
void func_8002506C(void *record_field, s32 pair_index) {
    u16 value_pairs[12];
    s32 shifted_index;
    S_8002506C_1 *linked_record;
    S_8002506C_2 *pair;

    __builtin_memcpy(value_pairs, D_80024004, 24);
    if ((u32)(pair_index & 0xFFFF) >= 6U) {
        pair_index = 0;
    }
    shifted_index = pair_index << 0x10;
    pair = (u8 *)value_pairs + (shifted_index >> 0xE);
    linked_record = ((S_8002506C_0 *)((u8 *)record_field - 0x14))->unk_00;
    linked_record->unk_1C = (u16)pair->unk_00;
    linked_record->unk_1E = (u16)pair->unk_02;
}
