#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970[];
extern M2C_UNK D_800E2C40[];

typedef struct S_800177D8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    void * unk_10;
} S_800177D8_0;   /* temp_t0 in func_800177D8 */

typedef struct S_800177D8_1 {
    s8 unk_00;
    s8 unk_01;
    s16 unk_02;
} S_800177D8_1;   /* temp_v0_2 in func_800177D8 */

/* Appends two bytes and a value to the selected row if it is enabled. */
void func_800177D8(s16 row_index, s8 first_byte, s8 second_byte, s16 value) {
    register s32 row_offset ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 entry_count;
    void *rows_base;
    void *entries_base;
    S_800177D8_0 *row;
    S_800177D8_1 *entry;

    rows_base = (void *)D_800E2970;
    row = (row_index * 0x14) + rows_base;
    if (row->unk_0A != 0) {
        row_offset = row_index << 6;
        entries_base = (void *)D_800E2C40;
        do { entry_count = row->unk_0E; } while (0);
        row->unk_10 = row_offset + entries_base;
        entry = ((s32)(entry_count << 0x10) >> 0xE) + row_offset + entries_base;
        row->unk_0E = (u16)(entry_count + 1);
        entry->unk_02 = value;
        entry->unk_00 = first_byte;
        entry->unk_01 = second_byte;
    }
}
