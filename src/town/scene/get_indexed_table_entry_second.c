#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
void check_ready_or_run_followup(s32);                     /* extern */
s32 get_indexed_table_entry();                         /* extern */
s32 func_80017990();                         /* extern */
extern M2C_UNK D_80017AB8;
extern s32 *D_80017B6C;

/* Set the active data pointer and process entries for the two checks for index 7. */
void install_table_and_test_entries(void) {
    D_80017B6C = &D_80017AB8;
    if (get_indexed_table_entry(7) != 0) {
        check_ready_or_run_followup(F_sbs36_pad08);
    }
    if (func_80017990(7) != 0) {
        check_ready_or_run_followup(F_sbs36_pad07);
    }
}
