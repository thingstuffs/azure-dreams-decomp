#include "engine/script.h"
#include "engine/message.h"

s32 is_list_nonempty(ScriptController *controller) {
    return controller->object_list.next != &controller->object_list;
}
