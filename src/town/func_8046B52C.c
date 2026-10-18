#include "common.h"
void func_8001E670(s32);                         /* extern */
extern s16 D_80017950;

/* Passes the value of D_80017950 to func_8001E670. */
void apply_stored_value_17950(void) {
    func_8001E670(D_80017950);
}
