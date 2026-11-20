#include "engine/message/data.h"
#include "engine/object.h"
#include "engine/script.h"

void set_script_record_byte(s32 value) {
    runtime_set_record_byte_three(&runtime_script_state, value);
}
