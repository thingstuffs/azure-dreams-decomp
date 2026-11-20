#include "engine/message/data.h"
#include "engine/object.h"
#include "engine/script.h"

void call_script(u8 *script) {
    reset_script_message_window(&runtime_script_state, script, 2);
}
