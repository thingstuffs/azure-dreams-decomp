#include "common.h"
#include "records/Rec_D_80016000.h"


typedef s32 (*TownCallback)(void *, void *, s32);

typedef struct S_8001A044_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001A044_0;   /* page in func_8001A044 */

typedef struct S_8001A044_1 {
    void * unk_00;
} S_8001A044_1;   /* l1_v0 in func_8001A044 */

typedef struct S_8001A044_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001A044_2;   /* l1_v1 in func_8001A044 */

typedef struct S_8001A044_3 {
    s32 unk_00;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_8001A044_3;   /* temp_s0 in func_8001A044 */

typedef struct S_8001A044_4 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8001A044_4;   /* temp_v0_2_ptr in func_8001A044 */


typedef struct S_8001A044_6 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001A044_6;   /* page2 in func_8001A044 */

typedef struct S_8001A044_7 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    s32 unk_04;
} S_8001A044_7;   /* temp_v0_4 in func_8001A044 */

typedef struct S_8001A044_8 {
    u8 pad_00[0x18];
    s32 * unk_18;
} S_8001A044_8;   /* temp_v0_3 in func_8001A044 */

typedef struct S_8001A044_9 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A044_9;   /* var_v1 in func_8001A044 */

typedef struct S_8001A044_10 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x18];
    void * unk_30;
} S_8001A044_10;   /* ((S_8001A044_0 *)page)->unk_6000 in func_8001A044 */

typedef struct S_8001A044_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001A044_11;   /* (temp_v0_2 * 0x10) +
                                    (u8 *)((S_8001A044_3 *)temp_s0)->unk_10 in func_8001A044 */

typedef struct S_8001A044_12 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001A044_12;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_8001A044 */

typedef struct S_8001A044_13 {
    u8 pad_00[0x30];
    void * unk_30;
} S_8001A044_13;   /* ((S_8001A044_6 *)page2)->unk_6000 in func_8001A044 */


extern void *func_800196E4(void *, void *);
extern void *func_8001976C(void *, void *, s32, s32);
extern s32 func_80019F94(void *, s32);

extern u8 D_80016000[];
extern u8 D_80016094[];
extern u8 D_800160A0[];
extern u8 D_800160CC[];
extern u8 D_800160FC[];
extern u8 D_8001DC10[];

/* Builds the object-set table and grouped object-select lists, then reports their counts and the CD-header count. */
void func_8001A044(s32 *records, void *ost_w, void *osel_w)
{
    register u8 *cd_header_entry;
    s32 *pp;
    s32 bank_bits;
    s32 group_bits;
    register s32 group_id;
    s32 updated_flags;
    s32 flag_bits;
    s32 variant_index;
    register s32 record_flags;
    s32 entry_address;
    register s32 previous_group;
    s32 cdhd_cnt;
    register s32 record_index;
    s32 scaled_index;
    S_8001A044_3 *record;
    S_8001A044_4 *direct_record;
    register void *group_data;
    register void *lookup_entry;
    register u8 *data_page;
    register u8 *list_page;
    register void *callbacks;
    TownCallback report_count;
    void *group_bank;
    void *group_entry;

    {
        u8 *next_object_set;
        u8 *p;

        record_index = 0;
        p = ost_w;
        if (*records != 0) {
            data_page = (u8 *)0x80010000;
            goto first_record;
    next_record:
            scaled_index = record_index * 8;
            goto read_record;
    first_record:
            scaled_index = record_index * 8;
    read_record:
            flag_bits = *(s32 *)(((scaled_index - record_index) * 4) + (u8 *)records);
            group_bits = flag_bits >> 0x13;
            flag_bits = flag_bits >> 0x17;
            bank_bits = flag_bits & 1;
            group_entry = ((S_8001A044_10 *)(((S_8001A044_0 *)data_page)->unk_6000))->unk_30;
            group_bank = (void *)(bank_bits * 4);
            group_bank = (void *)((u32)group_bank + (u32)group_entry);
            group_entry = (void *)(group_bits & 0x7E0);
            group_bank = ((S_8001A044_1 *)group_bank)->unk_00;
            group_entry = (void *)((u32)group_entry + (u32)group_bank);
            if (((S_8001A044_2 *)group_entry)->unk_0A != 0) {
                record = (void *)((u32)(record_index * 0x1C) + (u32)records);
                goto process_record;
            }
            if (bank_bits != 0) {
                record = (void *)((u32)(record_index * 0x1C) + (u32)records);
                goto process_record;
            }
            goto advance_record;
    process_record:
                if (record->unk_08 != 0) {
                    ((S_8001A044_10 *)(((S_8001A044_0 *)data_page)->unk_6000))->unk_14 = record_index;
                    variant_index = func_80019F94(record, group_bits);
                    updated_flags = (record->unk_00 & ~0xFF) |
                               (variant_index & 0xFF);
                    record->unk_00 = updated_flags;
                    next_object_set = func_8001976C(p,
                          (void *)((S_8001A044_11 *)((variant_index * 0x10) +
                                        (u8 *)record->unk_10))->unk_08,
                          updated_flags, record_index);
                    if ((next_object_set - 0x14) != p) {
                        func_800196E4(D_8001DC10, record);
                        record->unk_04 = p;
                        p = next_object_set;
                    }
                } else {
                    direct_record = (void *)((u32)(record_index * 0x1C) +
                                             (u32)records);
                    direct_record->unk_04 = p;
                    p = func_8001976C(p,
                        (void *)direct_record->unk_10, 0, record_index);
                }
    advance_record:
            record_index += 1;
            scaled_index = record_index * 8;
            if (*(s32 *)(((scaled_index - record_index) * 4) + (u8 *)records) != 0) {
                goto next_record;
            }
        }

        callbacks = ((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20;
        (*(TownCallback *)((u8 *)callbacks + 0x168))
            (D_80016094, D_800160A0,
             (u32)(p - (u8 *)ost_w) / 20);
    }

    previous_group = 0;
    pp = (s32 *)((u8 *)osel_w - 4);
    record_index = previous_group;
    if (*records != 0) {
        list_page = (u8 *)0x80010000;
build_group_list:
        record_flags = *(s32 *)((((record_index * 8) - record_index) * 4) + (u8 *)records);
        flag_bits = record_flags >> 0x18;
        group_id = flag_bits & 0x3F;
        if (group_id != previous_group) {
            bank_bits = record_flags >> 0x15;
            group_data = ((S_8001A044_13 *)(((S_8001A044_6 *)list_page)->unk_6000))->unk_30;
            flag_bits = bank_bits & 4;
            lookup_entry = (void *)((u32)flag_bits + (u32)group_data);
            entry_address = group_id << 5;
            lookup_entry = ((S_8001A044_7 *)lookup_entry)->unk_00.p;
            group_data = (void *)((u32)entry_address + (u32)lookup_entry);
            pp += 1;
            ((S_8001A044_8 *)group_data)->unk_18 = pp;
            *pp = 0;
            previous_group = group_id;
        }
        lookup_entry = (void *)((u32)(record_index * 0x1C) + (u32)records);
        entry_address = ((S_8001A044_7 *)lookup_entry)->unk_04;
        if ((entry_address != 0) &&
            !((((S_8001A044_7 *)lookup_entry)->unk_00.i >> 0xF) & 1)) {
            *pp = entry_address;
            pp += 1;
            *pp = 0;
        }
        record_index += 1;
        if (*(s32 *)((record_index * 0x1C) + (u8 *)records) != 0) {
            goto build_group_list;
        }
    }

    (*(TownCallback *)((u8 *)(((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x168))
        (D_80016094, D_800160CC, ((u32)pp - (u32)osel_w) >> 2);

    cd_header_entry = D_8001DC10;
    cdhd_cnt = 1;
    if (((S_8001A044_9 *)cd_header_entry)->unk_04 != 0) {
        do {
            cd_header_entry += 8;
            cdhd_cnt += 1;
        } while (((S_8001A044_9 *)cd_header_entry)->unk_04 != 0);
    }
    report_count = (*(TownCallback *)((u8 *)(((S_8001A044_12 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x168));
    report_count(D_80016094, D_800160FC, cdhd_cnt);
}
