#include "common.h"
extern s32 *devkit_state_slots;
s32 test_indexed_flag_bit(s32 bit) {
    if (bit != 0) {
        if (bit != 1) {
            return devkit_state_slots[bit / 32] & (1 << (bit % 32));
        }
        return 1;
    }
    return 0;
}
