#include "engine/message/data.h"
#include "engine/object.h"
#include "engine/script.h"

void start_script(u8 *script) {
    reset_script_message_window(&runtime_script_state, script, 1);
}
