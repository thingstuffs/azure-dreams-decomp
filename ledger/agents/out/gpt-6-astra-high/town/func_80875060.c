/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*TownCallback)(s32, void *, s16 *, s32);

extern u8 D_80700000[];
extern u8 D_80700BB4[];
extern s32 D_80701968[];

/* Dispatch a callback based on the number of consecutive set flags in the list. */
void func_80875060(s32 unused_0, s32 unused_1, s16 *input_ids, s32 input_flags_base) {
    TownCallback callbacks[3];
    s16 *flag_cursor;
    register s32 flag_bits ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 matched_count;
    s32 flags_base;
    void *flag_id;
    s32 *flag_word;
    s32 bit_one;
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    flag_id = (void *)(D_80700000 + 0xBC8);
    ASM_KEEP(flag_id);   /* MATCH pin: keeps a constant in a register as retail does */
    flag_bits = ((s32 *)flag_id)[0];
    flag_word = ((s32 *)flag_id)[1];
    matched_count = ((s32 *)flag_id)[2];
    callbacks[0] = (TownCallback)flag_bits;
    callbacks[1] = (TownCallback)flag_word;
    callbacks[2] = (TownCallback)matched_count;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    flag_cursor = input_ids;
    flags_base = input_flags_base;
    flag_word = (s32 *)(D_80700BB4 + 8);
    matched_count = 0;
    if (*(s16 *)flag_word != 0) {
        flags_base = D_80701968[0];
        bit_one = zero | 1;
        flag_cursor = (s16 *)flag_word;
check_flag:
        flag_id = (void *) *flag_cursor;
        if ((s32)flag_id < 0) {
            flag_bits = (s32)flag_id + 0x1F;
        } else {
            flag_bits = (s32)flag_id;
        }
        flag_bits >>= 5;
        flag_word = (s32 *)((flag_bits * 4) + flags_base);
        flag_bits <<= 5;
        flag_bits = (s32)flag_id - flag_bits;
        flag_word = (s32 *)*flag_word;
        flag_bits = bit_one << flag_bits;
        flag_cursor += 1;
        if (flag_bits & (s32)flag_word) {
            matched_count += 1;
            if (*flag_cursor != 0) {
                goto check_flag;
            }
        }
    }
    callbacks[matched_count](matched_count, flag_id, flag_cursor, flags_base);
}
