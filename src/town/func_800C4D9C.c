#include "common.h"

extern s32 func_80033B2C(s32 arg0);
extern void func_80033AA8(s32 arg0);
extern void func_80033AE8(s32 arg0);
extern s16 D_800D4770[];

/* Dispatches each table pair's second value according to the test of its first value. */
void func_800C24FC(void) {
    s16 *test_id;
    s16 *target_id;

    test_id = D_800D4770;
    if (*test_id != -1) {
        s32 sentinel = -1;
        target_id = test_id + 1;
        do {
            if (func_80033B2C(*test_id) != 0) {
                func_80033AA8(*target_id);
            } else {
                func_80033AE8(*target_id);
            }
            test_id += 2;
            target_id += 2;
        } while (*test_id != sentinel);
    }
}
