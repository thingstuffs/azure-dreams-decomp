#include "slus.h"
#include "slus/map_state.h"
#include "engine/message.h"

void initialize_script_controller(ScriptController *controller) {
    MapRuntimeState *defaults = &map_runtime_state;

    controller->mode = 2;
    controller->object_list.next = &controller->object_list;
    controller->object_list.backlink = &controller->object_list;
    controller->variable_addresses = defaults->variable_addresses;
    controller->service_handlers = defaults->service_handlers;
}
