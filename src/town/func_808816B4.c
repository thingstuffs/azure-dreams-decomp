#include "common.h"

extern s32 D_807006F8[3];
extern s32 D_80701004;

/* Scale the first stored value by eight and add D_80701004. */
void scale_stored_value_and_base_alt(void) {
    D_807006F8[0] = (D_807006F8[0] * 8) + D_80701004;
}
