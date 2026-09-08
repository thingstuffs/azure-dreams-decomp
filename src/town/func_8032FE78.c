#include "common.h"

typedef struct S_8001A678_0 {
    u8 pad_00[0x8];
    union { u32 s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x10];
    void * unk_30;
} S_8001A678_0;   /* root in func_8001A678 */

typedef struct S_8001A678_1 {
    void * unk_00;
} S_8001A678_1;   /* entry_ptr in func_8001A678 */

typedef struct S_8001A678_2 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A678_2;   /* (void *)index in func_8001A678 */

typedef struct S_8001A678_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A678_3;   /* position in func_8001A678 */



extern u8 *D_80016000;

/* Set the position from coordinates scaled by 64 and the selected entry offsets. */
void func_8001A678(s32 unused, u32 x, u32 y)
{
    u8 *root = D_80016000;
    S_8001A678_1 *entry_table;
    S_8001A678_3 *position;
    u32 entry_address;
    s32 x_offset;
    s32 y_offset;

    entry_table = ((S_8001A678_0 *)root)->unk_30;
    entry_address = ((S_8001A678_0 *)root)->unk_08.s;
    do {
        entry_address <<= 5;
    } while (0);
    do {
        entry_table = entry_table->unk_00;
    } while (0);
    entry_address += (u32)entry_table;
    position = ((S_8001A678_0 *)root)->unk_1C;
    do {
        x <<= 6;
    } while (0);
    x_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0C;
    x_offset += 0x20;
    x += x_offset;
    position->unk_04 = x;
    root = ((S_8001A678_0 *)root)->unk_1C;
    do {
        y <<= 6;
    } while (0);
    y_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0E;
    y_offset += 0x20;
    y += y_offset;
    ((S_8001A678_0 *)root)->unk_08.u = y;
}
