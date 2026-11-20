#include "engine/script.h"
#include "engine/message.h"

void set_flag_if_list_nonempty(ScriptController *controller) {
    if (is_list_nonempty(controller)) {
        controller->reset_requested = 1;
    }
}
