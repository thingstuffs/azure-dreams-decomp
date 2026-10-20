/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_8001A200_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_8001A200_1;

typedef struct S_8001A200_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8001A200_2;


void copy_town_record_pair_fields();     /* extern */
extern u8 D_8001791C[96];

/* Dispatches each record to the first matching kind-table entry. */
void dispatch_records_by_kind(void *records, s32 *value_sets) {
    u8 *kind_entry;
    s32 record_kind;
    s32 values_base;
    void *context;
    s32 slot_index;
    u8 *status_ptr;
    void *record;
    s32 next_status;

    context = D_80016000->unk_20;
    status_ptr = (u8 *)value_sets;
    values_base = *((((S_8001A200_1 *)context)->unk_2D4(0)) + (s32 *)status_ptr);
    for (record = records; (((S_8001A200_2 *)record)->unk_01 & 0xC0) != 0x80; record += 0x14) {
        for (slot_index = 1; slot_index < 8; slot_index++) {
            kind_entry = (u8 *)&D_8001791C + slot_index * 0xC;
            next_status = *(s32 *)kind_entry;
            record_kind = *(s32 *)((u8 *)record + 0xC);
            if ((next_status == record_kind) || ((next_status == 6) && (record_kind == 0x64))) {
                copy_town_record_pair_fields(record, values_base + slot_index * 4, kind_entry, slot_index);
                break;
            }
        }
    }
}
