#include "common.h"

typedef struct S_8001BEA4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x8];
    s32 unk_20;
} S_8001BEA4_0;   /* arg0 in func_8001BEA4 */

/* Sets four record fields to the supplied values. */
void func_8001BEA4(S_8001BEA4_0 *record, s32 value_14, s32 value_08, s32 value_0c, s32 value_20) {
    record->unk_14 = value_14;
    record->unk_08 = value_08;
    record->unk_0C = value_0c;
    record->unk_20 = value_20;
}
