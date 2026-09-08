#include "common.h"

extern u8 D_8006DE24[];
extern u16 D_8008347E;

s32 func_800A35D8(u8 arg0, u16 arg1);

s16 func_800A40AC(s32 arg0, s32 arg1)
{
    s32 kind;
    s16 result;
    s32 best_score;
    s32 best_value;
    register s32 count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *item_data ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u16 raw_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u32 item_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 loop_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 tripled_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 item;
    register s32 item_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 records;
    u8 *record;

    records = arg0;
    kind = arg1;
    result = -1;
    best_score = -4;
    best_value = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    count = hard_zero;
    raw_index = D_8008347E;
    item_page = 0x80070000;
    ASM_KEEP_NV(item_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
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
        register s32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        value = record[9];
        item_offset = item * 20;
        temp_a1 = func_800A35D8(item_data[item_offset + 16], (u16)kind);
        temp_a0 = best_value;
        temp_v1 = value;
        if (temp_a0 < temp_v1) {
            best_value = value;
            result = index + 5;
            best_score = temp_a1;
        } else if (temp_a0 == temp_v1) {
            if ((best_score << 16) < (temp_a1 << 16)) {
                best_score = temp_a1;
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

/* MECHANISM: The loop keeps both arguments, the table base, index, count, best value,
   best score, and result live in distinct roles; the local join replaces the seed's
   false call at the rowbase alias, restoring the retail comparison CFG. */
