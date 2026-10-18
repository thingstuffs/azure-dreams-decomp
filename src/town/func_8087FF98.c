#include "common.h"

s32 func_80700C54(s32, s32, s32, s32);
extern s32 D_80700A18[];

/* Run the indexed operation and return its table value. */
s32 grid_run_indexed_operation_a(s32 table_index, s32 call_input, s32 call_param, s32 call_extra) {
    func_80700C54(table_index, call_input, call_param, call_extra);
    return D_80700A18[table_index];
}
