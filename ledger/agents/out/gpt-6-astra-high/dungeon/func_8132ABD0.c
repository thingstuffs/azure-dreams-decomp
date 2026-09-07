#include "common.h"
#include "m2c_compat.h"

typedef struct S_801723D0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801723D0_0;   /* arg1 in func_801723D0 */

typedef struct S_801723D0_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_801723D0_1;   /* arg2 in func_801723D0 */

typedef struct S_801723D0_2 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801723D0_2;   /* arg0 in func_801723D0; pointer addresses record offset 0x2 */


M2C_UNK func_80171F30(); /* extern */
extern s32 D_800814A0[3];

/* Advance record values, perform six updates, and flag an expired counter. */
void func_801723D0(void *record_data, S_801723D0_0 *offset_record, S_801723D0_1 *value_record) {
    s32 base_addr;
    u16 remaining;

    base_addr = record_data - 0x20;
    offset_record->unk_02 = (u16) (offset_record->unk_02 + 0x10);
    value_record->unk_1A = (u16) (value_record->unk_1A + 0x1F4);
    func_80171F30(base_addr, 0x8080, 0x1C, 1);
    func_80171F30(base_addr, 0x8080, 0x1C, 1);
    func_80171F30(base_addr, 0x8080, 0x1C, 1);
    func_80171F30(base_addr, 0x8080, 0x1C, 2);
    func_80171F30(base_addr, 0x8080, 0x1C, 2);
    func_80171F30(base_addr, 0x8080, 0x1C, 2);
    remaining = ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_18 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
