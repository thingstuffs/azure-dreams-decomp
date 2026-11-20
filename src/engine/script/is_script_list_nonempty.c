#include "engine/message/data.h"
#include "engine/script.h"

void is_script_list_nonempty(void) {
    is_list_nonempty(&runtime_script_state);
}
