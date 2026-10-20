#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018FDC(s32, s32);

/* Forwards the index plus four to func_80018FDC with mode 1. */
void call_value_handler_index_plus_4(s32 index) {
    func_80018FDC(index + 4, 1);
}
