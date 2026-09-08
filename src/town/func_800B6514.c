/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

void func_800B3B18(u8 *arg0);                    /* extern */

typedef struct S_800B3C74_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B3C74_0;   /* var_s0 in func_800B3C74 */

typedef struct S_800B3C74_1 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B3C74_1;   /* var_s2 in func_800B3C74 */

typedef struct S_800B3C74_2 {
    u8 pad_00[0x4];
    u8 * unk_04;
} S_800B3C74_2;   /* (s32 *)temp_v0 in func_800B3C74 */

/* Decrement countdowns for slots 2 through 4, processing resources whose countdown is zero. */
void func_800B3C74(void *state) {
    s32 countdown;
    s32 resource_addr;
    s32 slot_offset;
    s32 *table;
    s32 *entry;
    s32 slot;
    void *owner;
    void *count_cursor;

    owner = state;
    slot = 2;
    count_cursor = owner + 8;
next_slot:
    countdown = ((S_800B3C74_0 *)count_cursor)->unk_0C;
    if (countdown != 0) {
        goto nonzero_count;
    }
    slot_offset = slot << 2;
    table = ((S_800B3C74_1 *)owner)->unk_5C;
    entry = (s32 *)(slot_offset + (s32)table);
    resource_addr = *entry;
    ASM_USE(slot_offset);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    count_cursor += 4;
    func_800B3B18(((S_800B3C74_2 *)((s32 *)resource_addr))->unk_04);
    ASM_USE(owner);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    slot += 1;
    goto check_done;

nonzero_count:
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    countdown--;
    ((S_800B3C74_0 *)count_cursor)->unk_0C = countdown;
    count_cursor += 4;
    slot += 1;
check_done:
    if (slot >= 5) {
        return;
    }
    goto next_slot;
}
