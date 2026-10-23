#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script.h"
extern u8 runtime_script_state[];

/* Tests the runtime script handler and its fallback status using runtime_script_state. */
void service_script_controller(void) {
    test_runtime_handler_or_fallback_status(&runtime_script_state);
}
