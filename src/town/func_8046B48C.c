#include "common.h"
void func_8001E670(s32);                         /* extern */
extern s16 D_8001792C;

/* Pass the current value of D_8001792C to func_8001E670. */
void apply_stored_value_1792_c(void) {
    func_8001E670(D_8001792C);
}
