#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef void (*TownCallback)(void *, s32, s32);


typedef struct S_8001A3FC_1 {
    u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_8001A3FC_1;   /* entry in func_8001A3FC */


extern s32 D_8001C370;
extern s32 D_8001C374;

/* Save the current context value and dispatch the selected entry's type callback. */
void func_8001A3FC(void) {
    s32 *entry_base;
    S_8001A3FC_1 *entry;
    s32 type;
    s32 entry_index;
    s32 entry_offset;

    entry_base = &D_8001C370;
    entry_index = D_80016000->unk_14;
    entry_offset = entry_index * 0x1C;
    entry = (void *)(entry_offset + *entry_base);
    type = entry->unk_00;
    D_8001C374 = ((s32)D_80016000->unk_00);
    (*(TownCallback *)((u8 *)((entry->unk_00 * 0x10) +
              entry->unk_10) + 4))(entry, type,
                           ((s32)D_80016000->unk_00));
}
