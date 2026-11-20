#include "engine/graphics.h"
#include "engine/message.h"

void clear_graphics_record(ScriptController *controller) {
    controller->reset_requested = 0;
    controller->camera_target_slot = 0;
    controller->pending_script = 0;
}
