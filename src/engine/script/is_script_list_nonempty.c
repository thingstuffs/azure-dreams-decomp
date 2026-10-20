#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 is_list_nonempty();                   /* extern */
extern u8 D_80082A38[];

/* Passes the global state to is_list_nonempty. */
void is_script_list_nonempty(void) {
    is_list_nonempty(&D_80082A38);
}
