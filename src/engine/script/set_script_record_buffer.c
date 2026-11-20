#include "engine/message/data.h"
#include "engine/object.h"
#include "engine/script.h"

/* Submit a packed command buffer to the bytecode reader. */
void set_script_record_buffer(void *buffer) {
    set_script_text_pointer(&runtime_script_state, buffer);
}
