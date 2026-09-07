#include "common.h"


typedef void (*TownCallback)(void *, u8, s32);

typedef struct S_8001A3FC_0 {
    volatile s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_8001A3FC_0;   /* D_80016000 in func_8001A3FC */

typedef struct S_8001A3FC_1 {
    volatile u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_8001A3FC_1;   /* entry in func_8001A3FC */


extern void *D_80016000;
extern s32 D_8001C370;
extern s32 D_8001C374;

/* Save the current context value and dispatch the selected entry's type callback. */
void func_8001A3FC(void) {
    s32 *entry_base;
    S_8001A3FC_1 *entry;
    u8 type;
    s32 entry_index;
    s32 entry_offset;

    do {
        entry_base = &D_8001C370;
    } while (0);
    entry_index = ((S_8001A3FC_0 *)D_80016000)->unk_14;
    entry_offset = entry_index * 0x1C;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    entry = (void *)(entry_offset + *entry_base);
    do {
        type = entry->unk_00;
    } while (0);
    D_8001C374 = ((S_8001A3FC_0 *)D_80016000)->unk_00;
    (*(TownCallback *)((u8 *)((entry->unk_00 * 0x10) +
              entry->unk_10) + 4))(entry, type,
                           ((S_8001A3FC_0 *)D_80016000)->unk_00);
}
