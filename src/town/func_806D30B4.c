#include "common.h"
#include "records/Rec_D_80016000.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef void (*ReportFunc)(void *, void *, u32);

typedef struct S_800168B4_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800168B4_1;   /* (temp_a1 & 0x7E0) +
                          *((s32 *)((u8 *)D_80016000->unk_30.as_s32 +
                                    (temp_a3 * 4))) in func_800168B4 */


typedef struct S_800168B4_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800168B4_3;   /* var_v1 in func_800168B4 */


typedef struct TownEntry {
    s32 flags;
    s32 link;
    s32 active;
    s32 pad_c;
    u8 * volatile choices;
    s32 pad_14;
    s32 pad_18;
} TownEntry;

typedef struct TownBucket {
    u8 pad_0[0x18];
    s32 *out;
    u8 pad_1c[4];
} TownBucket;

extern s32 func_80016818(void *, s32);
extern s32 func_8001643C(s32, s32, s32, s32);
extern void func_800163B8(void *, void *);

extern Rec_D_80016000 *D_80016000;
extern u8 D_80016178[0x10];
extern u8 D_80016184[0x10];
extern u8 D_800161B0[0x10];
extern u8 D_800161E0[0x10];
extern u8 D_80016F88[];
extern s32 D_80016FC8;
extern s32 D_80016FCC;

/* Build town records and bucket link lists, then report their counts and the slot count. */
void func_800168B4(s32 *entries, s32 records_start, s32 *links_start)
{
    s32 records_end;
    s32 entry_index;
    s32 bucket_bits;
    s32 bank_bits;

    entry_index = 0;
    records_end = records_start;
    if (*entries != 0) {
        TownEntry *entry = (TownEntry *)entries;

        do {
            s32 flags = entry->flags;

            bucket_bits = flags >> 19;
            bank_bits = (flags >> 23) & 1;
            if ((((S_800168B4_1 *)((bucket_bits & 0x7E0) +
                          *((s32 *)((u8 *)D_80016000->unk_30.as_s32 +
                                    (bank_bits * 4)))))->unk_0A != 0) ||
                (bank_bits != 0)) {
                if (entry->active != 0) {
                    s32 choice_index = func_80016818(entry, bucket_bits);
                    s32 choice_flags =
                        (entry->flags & ~0xFF) | (choice_index & 0xFF);
                    s32 next_record;

                    entry->flags = choice_flags;
                    next_record = func_8001643C(
                        records_end,
                        ((s32 *)entry->choices)[(choice_index << 2) + 2],
                        choice_flags, entry_index);
                    if ((next_record - 0x14) == records_end) {
                        goto next_entry;
                    }
                    func_800163B8(&D_80016FC8, entry);
                    entry->link = records_end;
                    records_end = next_record;
                    goto next_entry;
                } else {
                    entry->link = records_end;
                    records_end = func_8001643C(
                        records_end, (s32)entry->choices, 0, entry_index);
                }
            }
next_entry:
            entry++;
            entry_index++;
        } while (entry->flags != 0);
    }

    (*(ReportFunc *)((u8 *)(((Rec_D_80016000 *)D_80016000)->unk_20) + 0x168))(
        D_80016178, D_80016184, ((u32)records_end - (u32)records_start) / 20U);

    {
        s32 bucket_id = 0;
        s32 *link_out = links_start - 1;

        if (*entries != 0) {
            TownEntry *entry = (TownEntry *)entries;

            do {
                s32 flags_or_link = entry->flags;

                bucket_bits = (flags_or_link >> 24) & 0x3F;
                bank_bits = flags_or_link >> 21;

                if (bucket_bits != bucket_id) {
                    s32 **bucket_banks;
                    s32 *bucket_base;

                    link_out++;
                    bucket_id = bucket_bits;
                    bucket_banks = (s32 **)D_80016000->unk_30.as_s32;
                    bucket_base = bucket_banks[(bank_bits & 4) >> 2];
                    ((TownBucket *)bucket_base)[bucket_id].out = link_out;
                    *link_out = 0;
                }
                flags_or_link = entry->link;
                if ((flags_or_link != 0) &&
                    (((entry->flags >> 15) & 1) == 0)) {
                    *link_out = flags_or_link;
                    link_out++;
                    *link_out = 0;
                }
                entry++;
            } while (entry->flags != 0);
        }

        (*(ReportFunc *)((u8 *)(((Rec_D_80016000 *)D_80016000)->unk_20) + 0x168))(
            D_80016178, D_800161B0,
            ((u32)link_out - (u32)links_start) >> 2);
    }

    {
        s32 has_slots = D_80016FCC;
        u8 *slot;
        s32 slot_count;

        if (has_slots != 0) {
            slot = D_80016F88 + 0x40;
            slot_count = 1;
        } else {
            slot = &D_80016F88[0x40];
            slot_count = 1;
        }
        if (has_slots != 0) {
            do {
                slot += 8;
                slot_count++;
            } while (((S_800168B4_3 *)slot)->unk_04 != 0);
        }

        (*(ReportFunc *)((u8 *)(((Rec_D_80016000 *)D_80016000)->unk_20) + 0x168))(
            D_80016178, D_800161E0, slot_count);
    }
}
