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

s16 *func_800C1034(s32 unused, s32 index) {
    s32 saved_index;
    s16 code;
    s16 *output;
    TownEntry *copy_base;
    u16 *copy_output;

    D_80113200[0] = -1;
    output = D_80113200;
    output[1] = -1;
    output[2] = -1;
    output[3] = -1;

    if (D_8006ADD4 != 12) {
        saved_index = index;
        goto fallback;
    }

    saved_index = func_800C0F60(index);
    {
        TownEntry *base;
        TownEntry *entry;

        base = (TownEntry *)&D_800D4094;
        
        entry = (TownEntry *)((u32)(saved_index * 10) + (u32)base);
        if (entry->unk0 == 0) {
            goto fallback;
        }
        D_80113200[0] = entry->unk2;
        output[1] = entry->unk4;
        code = entry->unk8;
    }

    switch (code) {
    case -4:
        output[2] = D_800D4268[2];
        output[3] = D_800D4268[3];
        goto done;
    case -2:
        ASM_KEEP_NV(code);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        break;
    default:
        goto copy_entry;
    }
    goto fallback;
copy_entry:
    {
        TownEntry *entry;

        copy_output = (u16 *)&D_80110004[0x31FC];
        copy_base = (TownEntry *)&D_800D0004[0x4090];
        entry = (TownEntry *)((u8 *)copy_base + saved_index * 10);
        copy_output[2] = entry->unk6;
        copy_output[3] = entry->unk8;
    }
    goto done;
fallback:
    
    func_800C0FE4(output, saved_index);
done:
    return D_80113200;
}

/* MECHANISM: A direct first store plus a named output pointer induces retail's
   held 0x8011 page in s1 and D_80113200 base in s0.  Typed 10-byte TownEntry
   indexing preserves the halfword widths and the two retail copy paths. */
