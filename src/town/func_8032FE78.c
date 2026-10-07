#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_8001A678_1 {
    void * unk_00;
} S_8001A678_1;   /* entry_ptr in func_8001A678 */

typedef struct S_8001A678_2 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A678_2;   /* (void *)index in func_8001A678 */


/* Set the position from coordinates scaled by 64 and the selected entry offsets. */
void func_8001A678(s32 unused, u32 x, u32 y)
{
    u8 *root = ((u8 *)D_80016000);
    S_8001A678_1 *entry_table;
    TownPositionState *position;
    u32 entry_address;
    s32 x_offset;
    s32 y_offset;

    entry_table = ((Rec_D_80016000 *)root)->unk_30;
    entry_address = ((u32)((Rec_D_80016000 *)root)->unk_08);
    {
        entry_address <<= 5;
    }
    {
        entry_table = entry_table->unk_00;
    }
    entry_address += (u32)entry_table;
    position = ((Rec_D_80016000 *)root)->unk_1C;
    {
        x <<= 6;
    }
    x_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0C;
    x_offset += 0x20;
    x += x_offset;
    position->x = x;
    root = ((Rec_D_80016000 *)root)->unk_1C;
    {
        y <<= 6;
    }
    y_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0E;
    y_offset += 0x20;
    y += y_offset;
    ((TownPositionState *)root)->y = y;
}
