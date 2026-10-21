#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script.h"
extern u8 runtime_script_state[];

/* Pass the global object D_80082A38 to func_80034FFC. */
void service_script_controller(void) {
    test_runtime_handler_or_fallback_status(&runtime_script_state);
}
