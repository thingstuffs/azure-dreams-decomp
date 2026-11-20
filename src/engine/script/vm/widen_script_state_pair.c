#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/script/vm.h"

/* Store the signed text column and row in the first two script variables. */
void widen_script_state_pair(void) {
    ScriptController *controller = &runtime_script_state;
    s32 column = controller->window.column;
    s32 row = controller->window.row;

    controller->variables[0] = column;
    controller->variables[1] = row;
}
