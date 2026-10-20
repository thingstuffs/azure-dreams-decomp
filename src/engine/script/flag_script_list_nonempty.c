#include "common.h"

#include "common.h"

void set_flag_if_list_nonempty(s8 *result_flag);
extern u8 D_80082A38[];

/* Passes the global object D_80082A38 to set_flag_if_list_nonempty. */
void flag_script_list_nonempty(void) {
    set_flag_if_list_nonempty(&D_80082A38);
}
