#include "engine/message.h"
#include "engine/object.h"
#include "engine/script/vm.h"

/* The end opcode parks the embedded window on this callback. */
s32 has_active_script_handler(ScriptController *controller) {
    return controller->window.message_handler != noop_runtime_record_idle;
}
