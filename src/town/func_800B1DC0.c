/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF520_3 {
    void * unk_00;
} S_800AF520_3;   /* ctx in func_800AF520 */

typedef struct S_800AF520_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800AF520_4;   /* ((S_800AF520_3 *)ctx)->unk_00 in func_800AF520 */

extern s32 func_8004A658();

typedef struct S_800AF520_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    s32 unk_A8;
} S_800AF520_0;   /* ctx in func_800AF520 */

typedef struct S_800AF520_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_800AF520_1;   /* temp_struct in func_800AF520 */

typedef struct S_800AF520_2 {
    u8 unk_00;
    u8 unk_01;
} S_800AF520_2;   /* temp_v0 in func_800AF520 */

/* Fill slots 6 through 15 from the current page of entries, then clear unused slots. */
void func_800AF520(void *context) {
    s32 *empty_slot;
    void *slots;
    register s32 entry_index;
    s32 page_index;
    s32 index_offset;
    s32 value;
    register s32 has_entry;
    s32 slot_index;
    s32 slot_offset;
    s32 has_slot;
    S_800AF520_2 *entry;
    s32 *slot;
    void *slot_addr;
    S_800AF520_1 *entries;
    S_800AF520_0 *ctx = context;

    page_index = ((S_800AF520_4 *)(((S_800AF520_3 *)ctx)->unk_00))->unk_10;
    slot_index = 6;
    index_offset = page_index << 2;
    index_offset += page_index;
    entry_index = index_offset << 1;
    for (;;) {
        entries = ctx->unk_00;
        has_entry = entry_index < entries->unk_1C;
        if (has_entry == 0) {
            goto check_slots;
        }
        slot_addr = (void *)((entry_index << 2) + entries->unk_20);
        entry = *(void **)slot_addr;
        value = func_8004A658(entry->unk_01, entry->unk_00);
        entry_index += 1;
        slots = (void *)ctx->unk_A8;
        slot = *((s32 **)((slot_index * 4) + (u8 *)slots));
        slot_index += 1;
        *slot = value;
        do {
            has_slot = slot_index < 0x10;
        } while (0);
        if (has_slot == 0) {
            goto check_slots;
        }
    }
clear_slot:
    slot_offset = slot_index << 2;
    do {
        slot_addr = (void *)(slot_offset + ctx->unk_A8);
    } while (0);
    empty_slot = *(s32 **)slot_addr;
    slot_index += 1;
    *empty_slot = 0;
check_slots:
    has_slot = slot_index < 0x10;
clear_remaining:
    if (has_slot != 0) {
        goto clear_slot;
    }
    return;
}
