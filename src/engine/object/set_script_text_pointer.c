#include "engine/message.h"
#include "engine/object.h"

/* Select a script and discard the previous script's return addresses. */
void set_script_text_pointer(ScriptController *controller, u8 *script) {
    controller->pending_script = script;
    controller->script_start = script;
    controller->window.returns.next = controller->window.returns.addresses;
}
