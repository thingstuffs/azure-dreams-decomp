#include "common.h"

extern u8 D_8006DE24[];
extern u16 D_8008347E;

s32 func_800A35D8(u8 arg0, u16 arg1);

/* Selects the highest-value nonempty item among three slots, breaking ties by kind score. */
s16 func_800A40AC(s32 records_addr, s32 item_kind)
{
    s32 kind;
    s16 result;
    s32 best_score;
    s32 best_value;
    register s32 count ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *item_data ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 index ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 value ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register u16 raw_index ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 item_page ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 loop_index ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 tripled_index ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 item;
    register s32 item_offset ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 records;
    u8 *record;

    records = records_addr;
    kind = item_kind;
    result = -1;
    best_score = -4;
    best_value = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    count = hard_zero;
    raw_index = D_8008347E;
    item_page = 0x80070000;
    ASM_KEEP_NV(item_page);   /* MATCH pin: retail immediate-load split depends on it */
    item_data = (u8 *)(item_page - 0x21DC);
    index = raw_index & 3;
loop:
    loop_index = index;
    if (loop_index == 3) {
        index = 0;
    }
    loop_index = index;
    tripled_index = loop_index * 3;
    record = (u8 *)records + tripled_index;
    item = record[8];
    if (item != 0) {
        register s32 score ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register s32 prior_value ASM_REG("$4");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 candidate_value ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

        value = record[9];
        item_offset = item * 20;
        score = func_800A35D8(item_data[item_offset + 16], (u16)kind);
        prior_value = best_value;
        candidate_value = value;
        if (prior_value < candidate_value) {
            best_value = value;
            result = index + 5;
            best_score = score;
        } else if (prior_value == candidate_value) {
            if ((best_score << 16) < (score << 16)) {
                best_score = score;
                result = index + 5;
            }
        }
    }
    count++;
    index++;
    if (count < 3) {
        goto loop;
    }
    return result;
}

