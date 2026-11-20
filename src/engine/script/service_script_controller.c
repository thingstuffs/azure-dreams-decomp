#include "engine/message/data.h"
#include "engine/object.h"
#include "engine/script.h"

/* Tests the runtime script handler and its fallback status using runtime_script_state. */
s32 service_script_controller(void) {
    return is_script_or_map_change_pending(&runtime_script_state);
}
