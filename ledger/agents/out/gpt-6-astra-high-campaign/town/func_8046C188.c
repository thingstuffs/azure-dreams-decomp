#include "common.h"

typedef struct S_8001D188_3 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001D188_3;   /* page in func_8001D188 */

typedef struct S_8001D188_4 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_8001D188_4;   /* ((S_8001D188_3 *)page)->unk_6000 in func_8001D188 */


typedef struct S_8001D188_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001D188_0;   /* page in func_8001D188 */

typedef struct S_8001D188_1 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x44];
    void * unk_6C;
    u8 pad_70[0x17C];
    s16 * unk_1EC;
} S_8001D188_1;   /* cursor in func_8001D188 */

typedef struct S_8001D188_2 {
    u8 pad_00[0x3700];
    union { u8 s; volatile u8 u; } unk_3700;   /* accessed as both */
} S_8001D188_2;   /* temp_a2 in func_8001D188 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001D414(s32, s32, s32, s32);
extern s8 D_80016000[];
extern s8 D_8001902C[];

/* Advance the group counter and prepend the entry to its twelve-entry history. */
void func_8001D188(s32 entry_index, s32 lookup_arg1, s32 lookup_arg2, s32 lookup_arg3) {
    s32 group_id;
    s32 state_base;
    s32 variant;
    s32 slot_index;
    u8 *slot;
    u8 *history;
    s32 old_entry;
    s32 entry_id;
    register S_8001D188_2 *group_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 *limits;
    u8 *page;
    S_8001D188_1 *cursor;
    s16 *entries;
    s32 next_count;
    u8 count;

    do { page = (u8 *)0x80010000; } while (0);
    state_base = ((S_8001D188_4 *)(((S_8001D188_3 *)page)->unk_6000))->unk_38;
    entry_id = entry_index;
    variant = func_8001D414(entry_index, lookup_arg1, lookup_arg2, lookup_arg3);
    cursor = ((S_8001D188_0 *)page)->unk_6000;
    cursor = cursor->unk_24;
    cursor = cursor->unk_6C;
    entries = cursor->unk_1EC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    group_id = *(s16 *)((u8 *)entries + (entry_id * 0x14));
    group_state = state_base + group_id;
    next_count = group_state->unk_3700.s;
    next_count += 1;
    group_state->unk_3700.s = next_count;
    count = group_state->unk_3700.u;
    ASM_USE(count);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    slot_index = 0;
    limits = D_8001902C;
    if (count >= *(s16 *)((u8 *)limits + (((group_id * 3) + variant) * 8))) {
        group_state->unk_3700.s = 0U;
    }
    ASM_KEEP_NV(group_id);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    history = (u8 *)(group_id * 0xC) + state_base + 0x3640;
    do {
        slot = history + slot_index;
        old_entry = *slot;
        *slot = entry_id;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        slot_index += 1;
        entry_id = old_entry;
    } while (slot_index < 0xC);
}
