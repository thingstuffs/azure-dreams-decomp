#include "engine/object.h"
#include "engine/message.h"

/* init_message_window copies this default into the new window's text speed. */
void runtime_set_record_byte_three(ScriptController *controller, s32 value) {
    controller->text_speed = value;
}
