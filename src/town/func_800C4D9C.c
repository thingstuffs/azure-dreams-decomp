#include "modules/town_minigame_dispatch.h"
#include "common.h"

extern s32 test_resident_bitmap_bit(s32 bit_id);
extern void set_resident_bitmap_bit(s32 bit_id);
extern void clear_resident_bitmap_bit(s32 flag_id);
extern s16 D_800D4770[];

/* Dispatches each table pair's second value according to the test of its first value. */
void dispatch_conditional_table_pairs(void) {
    s16 *test_id;
    s16 *target_id;

    test_id = D_800D4770;
    if (*test_id != -1) {
        s32 sentinel = -1;
        target_id = test_id + 1;
        do {
            if (test_resident_bitmap_bit(*test_id) != 0) {
                set_resident_bitmap_bit(*target_id);
            } else {
                clear_resident_bitmap_bit(*target_id);
            }
            test_id += 2;
            target_id += 2;
        } while (*test_id != sentinel);
    }
}
