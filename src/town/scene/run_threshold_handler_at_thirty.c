#include "town/scene/run_threshold_handler_at_thirty.h"
#include "town/scene/run_threshold_handler_at_thirty.h"
#include "town/scene.h"
#include "town/player.h"

/* Runs the threshold handler when the queried value reaches 30, then forwards the arguments. */
void run_threshold_handler_at_thirty(s32 value, s32 context) {
    if (get_linked_record_field_2_d_60() >= 30) {
        func_80016A1C();
    }
    run_service_callback_1(value, context);
}
