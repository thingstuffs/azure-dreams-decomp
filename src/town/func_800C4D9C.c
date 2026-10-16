#include "modules/town_minigame_dispatch.h"
#include "common.h"

extern s32 testResidentBitmapBit(s32 bit_id);
extern void setResidentBitmapBit(s32 bit_id);
extern void clearResidentBitmapBit(s32 flag_id);
extern s16 D_800D4770[];

/* Dispatches each table pair's second value according to the test of its first value. */
void townDispatchConditionalTablePairs(void) {
    s16 *test_id;
    s16 *target_id;

    test_id = D_800D4770;
    if (*test_id != -1) {
        s32 sentinel = -1;
        target_id = test_id + 1;
        do {
            if (testResidentBitmapBit(*test_id) != 0) {
                setResidentBitmapBit(*target_id);
            } else {
                clearResidentBitmapBit(*target_id);
            }
            test_id += 2;
            target_id += 2;
        } while (*test_id != sentinel);
    }
}
