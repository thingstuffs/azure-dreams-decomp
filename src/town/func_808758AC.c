#include "common.h"
extern s32 *D_80701968;
s32 func_807018AC(s32 bit) {
    if (bit != 0) {
        if (bit != 1) {
            return D_80701968[bit / 32] & (1 << (bit % 32));
        }
        return 1;
    }
    return 0;
}
