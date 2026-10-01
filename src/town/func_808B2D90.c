/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*Callback)(s32);

typedef struct CallbackTable { Callback entry[3]; } CallbackTable;
extern CallbackTable D_A0700104;
extern s16 D_A0700F34[];
extern u8 *D_A0700F40;

/* Dispatch a callback based on the number of leading set flags in the ID list. */
void func_808B2D90(void) {
    CallbackTable callbacks;
    s16 *flag_cursor;
    s32 set_count;
    u8 *flag_bits;
    s32 flag_id;
    s16 *flag_ids;

    callbacks = D_A0700104;
    flag_ids = D_A0700F34;
    set_count = 0;
    if (*flag_ids != 0) {
        s32 flag_group;
        flag_bits = D_A0700F40;
        flag_cursor = flag_ids;
check_flag:
        flag_id = (s32)*flag_cursor;
        flag_group = flag_id / 32;
        flag_cursor++;
        if (((s32)flag_bits[flag_group] >> (flag_id % 32)) & 1) {
            set_count++;
            if (*flag_cursor != 0) goto check_flag;
        }
    }
    callbacks.entry[set_count](set_count);
}
