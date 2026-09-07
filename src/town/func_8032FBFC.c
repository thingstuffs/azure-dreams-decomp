#include "common.h"
#include "records/Rec_D_80016000.h"


typedef void (*TownCallback)(void *, u8, s32);


typedef struct S_8001A3FC_1 {
    volatile u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_8001A3FC_1;   /* entry in func_8001A3FC */


extern void *D_80016000;
extern s32 D_8001C370;
extern s32 D_8001C374;

void func_8001A3FC(void) {
    s32 *entryBase;
    S_8001A3FC_1 *entry;
    u8 type;
    s32 index;
    s32 offset;

    do {
        entryBase = &D_8001C370;
    } while (0);
    index = ((Rec_D_80016000 *)D_80016000)->unk_14;
    offset = index * 0x1C;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    entry = (void *)(offset + *entryBase);
    do {
        type = entry->unk_00;
    } while (0);
    D_8001C374 = ((Rec_D_80016000 *)D_80016000)->unk_00.at00_vs32.v;
    (*(TownCallback *)((u8 *)((entry->unk_00 * 0x10) +
              entry->unk_10) + 4))(entry, type,
                           ((Rec_D_80016000 *)D_80016000)->unk_00.at00_vs32.v);
}
