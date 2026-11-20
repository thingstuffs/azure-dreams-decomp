#include "engine/message/data.h"
#include "engine/script.h"

void flag_script_list_nonempty(void) {
    set_flag_if_list_nonempty(&runtime_script_state);
}
