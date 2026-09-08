#include "common.h"

typedef struct {
    s16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s16 unk8;
} TownEntry;

extern s16 D_8006ADD4;
extern u8 D_800D0004[];
extern u8 D_800D4094;
extern s16 D_800D4268[];
extern u8 D_80110004[];
extern s16 D_80113200[];

extern s32 func_800C0F60(s32 arg0);
extern void func_800C0FE4(s16 *arg0, s32 arg1);

/* Builds a four-value town entry result using table data or a fallback lookup. */
s16 *func_800C1034(s32 unused, s32 index) {
    s32 entry_index;
    s16 entry_code;
    s16 *output;
    TownEntry *copy_entries;
    u16 *copy_dest;

    D_80113200[0] = -1;
    output = D_80113200;
    output[1] = -1;
    output[2] = -1;
    output[3] = -1;

    if (D_8006ADD4 != 12) {
        entry_index = index;
        goto fallback;
    }

    entry_index = func_800C0F60(index);
    {
        TownEntry *entries;
        TownEntry *entry;

        entries = (TownEntry *)&D_800D4094;

        entry = (TownEntry *)((u32)(entry_index * 10) + (u32)entries);
        if (entry->unk0 == 0) {
            goto fallback;
        }
        D_80113200[0] = entry->unk2;
        output[1] = entry->unk4;
        entry_code = entry->unk8;
    }

    switch (entry_code) {
    case -4:
        output[2] = D_800D4268[2];
        output[3] = D_800D4268[3];
        goto done;
    case -2:
        ASM_KEEP_NV(entry_code);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        break;
    default:
        goto copy_entry;
    }
    goto fallback;
copy_entry:
    {
        TownEntry *entry;

        copy_dest = (u16 *)&D_80110004[0x31FC];
        copy_entries = (TownEntry *)&D_800D0004[0x4090];
        entry = (TownEntry *)((u8 *)copy_entries + entry_index * 10);
        copy_dest[2] = entry->unk6;
        copy_dest[3] = entry->unk8;
    }
    goto done;
fallback:

    func_800C0FE4(output, entry_index);
done:
    return D_80113200;
}

