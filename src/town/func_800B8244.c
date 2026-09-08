#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B59A4_3 {
    u8 pad_00[0x30];
    void * unk_30;
} S_800B59A4_3;   /* var_s1 in func_800B59A4 */

typedef struct S_800B59A4_4 {
    s32 unk_00;
    void * unk_04;
} S_800B59A4_4;   /* ((S_800B59A4_3 *)var_s1)->unk_30 in func_800B59A4 */

typedef struct S_800B59A4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B59A4_5;   /* ((S_800B59A4_4 *)(((S_800B59A4_3 *)var_s1)->unk_30))->unk_04 in func_800B59A4 */




s32 func_8004A658();
s32 func_8004AC3C();
M2C_UNK bzero(void **, M2C_UNK);
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
M2C_UNK func_800B58B8(void **, s32);
s32 func_800B5918();

typedef struct S_800B59A4_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
} S_800B59A4_0;   /* var_s1 in func_800B59A4 */

typedef struct S_800B59A4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B59A4_1;   /* temp_v0 in func_800B59A4 */

typedef struct S_800B59A4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B59A4_2;   /* temp_v0_2 in func_800B59A4 */

/* Populate up to three display rows with entry text and positioned icons. */
void func_800B59A4(s32 source_id, void *display) {
    s32 scratch[10];
    s16 icon_y;
    s32 text_y;
    s32 row_index;
    void **entry_slot;
    void *entry;
    S_800B59A4_1 *entry_info;
    S_800B59A4_2 *icon;
    void *row_display;

    row_display = display;
    bzero((void **) &scratch[0], 0xC);
    func_800B58B8((void **) &scratch[0], source_id);
    row_index = 0;
    icon_y = 0x66;
    text_y = 0xD8;
next_row:
    entry_slot = (void **)((s32)(row_index << 2) + (s32)&scratch[0]);
    entry = *entry_slot;
    if (entry != NULL) {
        func_800B5264(((S_800B59A4_0 *)row_display)->unk_18, func_8004AC3C(entry, &scratch[8]), scratch[8], 0x58, text_y);
        func_800B53BC(((S_800B59A4_0 *)row_display)->unk_24, func_800B5918(*entry_slot, &scratch[4]), 0, 0xA0, text_y);
        entry_info = *entry_slot;
        row_index += 1;
        ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_00 = func_8004A658(entry_info->unk_01, entry_info->unk_00);
        ((S_800B59A4_5 *)(((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04))->unk_08 = -0x30;
        text_y += 0x10;
        icon = ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04;
        row_display += 4;
        icon->unk_0A = icon_y;
        icon_y += 0x10;
        if (row_index < 3) {
            goto next_row;
        }
    }
}
