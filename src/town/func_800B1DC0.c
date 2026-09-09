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
    register s32 index_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 value;
    register s32 has_entry;
    s32 slot_index;
    s32 slot_offset;
    s32 has_slot;
    S_800AF520_2 *entry;
    s32 *slot;
    register void *slot_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_800AF520_1 *entries;
    S_800AF520_0 *ctx = context;

    page_index = ((S_800AF520_4 *)(((S_800AF520_3 *)ctx)->unk_00))->unk_10;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    slot_index = 6;
    ASM_KEEP(slot_index);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    index_offset = page_index << 2;
    index_offset += page_index;
    entry_index = index_offset << 1;
    for (;;) {
        entries = ctx->unk_00;
        has_entry = entry_index < entries->unk_1C;
        if (has_entry == 0) {
            goto check_slots;
        }
        index_offset = entry_index << 2;
        slot_addr = (void *)(index_offset + entries->unk_20);
        entry = *(void **)slot_addr;
        value = func_8004A658(entry->unk_01, entry->unk_00);
        entry_index += 1;
        slots = (void *)ctx->unk_A8;
        slot = *((s32 **)((slot_index * 4) + (u8 *)slots));
        slot_index += 1;
        *slot = value;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        has_slot = slot_index < 0x10;
        if (has_slot == 0) {
            goto check_slots;
        }
    }
clear_slot:
    slot_offset = slot_index << 2;
    slot_addr = (void *)(slot_offset + ctx->unk_A8);
    ASM_KEEP(slot_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
