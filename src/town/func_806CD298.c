#include "modules/town_ovl_64d298.h"

/* Runs the threshold handler when the queried value reaches 30, then forwards the arguments. */
void run_threshold_handler_at_thirty(s32 value, s32 context) {
    if (func_800175D0() >= 30) {
        func_80016A1C();
    }
    run_service_callback_1(value, context);
}
