#include "common.h"

typedef struct Scratch {
    u8 pad0[0x18];
    u8 *current;
    u8 pad1c[4];
    u32 *table;
    u8 pad24[0x4c];
    u32 value70;
    u16 half74;
    u8 pad76[2];
    u32 value78;
    u16 half7c;
    u8 pad7e[2];
    u32 value80;
    u16 half84;
    u8 pad86[2];
    u32 value88;
    u16 half8c;
    u8 pad8e[2];
    u32 out90;
    u32 out94;
    u8 pad98[0x28];
    u32 index;
} Scratch;

typedef struct Entry {
    u8 bytes[0x24];
} Entry;

typedef struct EmptyCallArg {
} EmptyCallArg;

extern u8 *D_80083160;
extern s16 D_80026476;
extern u32 D_800265C0;
extern u32 D_800265C4;
extern u32 D_800265C8[];

extern u32 func_800654B0(
    u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *,
    EmptyCallArg);
extern void func_80066708(Entry *);
extern void func_8006658C(u32 *, Entry *);
extern u32 func_80066460(u32, u32, u32, u32);
extern void func_80067F20(Entry *, u32, u32, u32, u32);

s32 func_80024A68(void)
{
    s32 index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *state = D_80083160;
    u8 *initial_current = *(u8 **)(state + 0x8D0);
    u32 *table_base;
    u8 *record;

    scratch->table = (u32 *)(state + 0xB0);
    scratch->current = initial_current;

    /* This address is needed only by the loop's terminal writeback. */
    {
        u8 **state_slot = &D_80083160;

        if (D_80026476 <= 0)
            goto done;

        table_base = D_800265C8;
        record = (u8 *)table_base;

loop:
        {
        Entry *entry;
        u32 *call0;
        u32 *call1;
        register u32 *call2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u32 *call3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u32 *upper_table;
        u32 value88;
        s32 masked_index;
        s32 neighbor_index;
        u16 record_half;
        u16 neighbor_half;
        EmptyCallArg late_stores;

        ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call0 = &scratch->value70;
        masked_index = index & ~0xF;
        entry = (Entry *)scratch->current;
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call1 = &scratch->value78;
        ASM_KEEP(call1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call2 = &scratch->value80;
        scratch->current = (u8 *)entry + 0x24;
        scratch->value70 = *(u32 *)record;
        upper_table = table_base + 0x20;
        scratch->value78 = table_base[
            ((u32)masked_index + (u32)((index + 1) & 0xF)) * 2];
        scratch->value80 = upper_table[index * 2];
        value88 = upper_table[
            ((u32)masked_index + (u32)((index + 1) & 0xF)) * 2];
        call3 = &scratch->value88;
        record_half = *(u16 *)(record + 4);
        scratch->half74 = record_half;
        scratch->half7c = record_half;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        neighbor_index = index + 16;
        neighbor_half = ((u16 *)table_base)[(neighbor_index * 4) + 2];

        scratch->index = func_800654B0(
            call0, call1, call2, call3,
            (u32 *)((u8 *)entry + 8), (u32 *)((u8 *)entry + 16),
            (u32 *)((u8 *)entry + 24), (u32 *)((u8 *)entry + 32),
            &scratch->out90, &scratch->out94,
            (scratch->value88 = value88,
             scratch->half84 = neighbor_half,
             scratch->half8c = neighbor_half,
             late_stores));
        scratch->index -= 8;

        if (scratch->index < 0x1E0U) {
            if ((index % 32) < 16) {
                *(u32 *)((u8 *)entry + 12) = D_800265C0;
                *(u32 *)((u8 *)entry + 4) = D_800265C0;
                *(u32 *)((u8 *)entry + 28) = D_800265C4;
                *(u32 *)((u8 *)entry + 20) = D_800265C4;
            } else {
                *(u32 *)((u8 *)entry + 28) = D_800265C0;
                *(u32 *)((u8 *)entry + 20) = D_800265C0;
                *(u32 *)((u8 *)entry + 12) = D_800265C4;
                *(u32 *)((u8 *)entry + 4) = D_800265C4;
            }

            func_80066708(entry);
            entry->bytes[7] |= 2;
            func_8006658C(scratch->table + scratch->index, entry);

            {
                u8 *next_entry = scratch->current;
                scratch->current = next_entry + 0x0C;
                func_80067F20(next_entry, 0, 0,
                              (u16)func_80066460(0, 1, 0, 0), 0);
                func_8006658C(scratch->table + scratch->index,
                              (Entry *)next_entry);
            }
        }

            record += 8;
        }

        {
            s32 count = D_80026476;
            index++;
            if (index < count)
                goto loop;
        }

done:
        *(u8 **)(*state_slot + 0x8D0) = scratch->current;
    }
    return 0;
}
