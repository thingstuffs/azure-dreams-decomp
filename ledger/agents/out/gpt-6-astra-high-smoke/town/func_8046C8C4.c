#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E578();                 /* extern */

typedef struct S_8046C8C4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8046C8C4_0;   /* arg0 in func_8046C8C4 */

typedef struct S_8046C8C4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8046C8C4_1;   /* temp_a1 in func_8046C8C4 */

/* Passes the indexed record and its signed field to func_8001E578. */
void func_8046C8C4(S_8046C8C4_0 *record_table, s32 record_index) {
    S_8046C8C4_1 *record;

    record = (record_index * 0x10) + record_table->unk_10;
    func_8001E578(record->unk_0C, record);
}
