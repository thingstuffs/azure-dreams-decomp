/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*Callback)(s32, s32, s16 *, u8 *);

extern u8 D_A0700000[];
__asm__(".set D_A0700000, 0xA0700000");

/* Dispatch a callback based on the number of leading set flags in the ID list. */
void func_808B2D90(s32 unused_count, s32 unused_flag, s16 *input_ids, u8 *input_bits) {
    Callback callbacks[3];
    Callback callback_0;
    Callback callback_1;
    Callback callback_2;
    s16 *flag_cursor;
    s32 set_count;
    u8 *flag_bits;
    s32 flag_id;
    s16 *flag_ids;

    flag_bits = input_bits;
    flag_cursor = input_ids;
    ASM_KEEP(flag_cursor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    flag_id = (u32)(D_A0700000 + 0x104);
    ASM_KEEP(flag_id);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    callback_0 = ((Callback *)flag_id)[0];
    callback_1 = ((Callback *)flag_id)[1];
    callback_2 = ((Callback *)flag_id)[2];
    callbacks[0] = callback_0;
    callbacks[1] = callback_1;
    callbacks[2] = callback_2;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    flag_ids = (s16 *)(D_A0700000 + 0xF34);
    ASM_KEEP(flag_ids);   /* MATCH pin: retail immediate-load split depends on it */
    set_count = 0;
    if (*flag_ids != 0) {
        register s32 flag_group ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        flag_bits = D_A0700000;
        flag_bits = *(u8 **)(flag_bits + 0xF40);
        flag_cursor = flag_ids;
check_flag:
        flag_id = (s32) *flag_cursor;
        flag_group = flag_id;
        if ((s32) flag_id < 0) {
            flag_group = flag_id + 0x1F;
        }
        flag_group >>= 5;
        flag_cursor++;
        if (((s32) *(flag_bits + flag_group) >> (flag_id - (flag_group << 5))) & 1) {
            set_count += 1;
            if (*flag_cursor != 0) {
                goto check_flag;
            }
        }
    }
    callbacks[set_count](set_count, flag_id, flag_cursor, flag_bits);
}
