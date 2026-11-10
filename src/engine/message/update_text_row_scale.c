#include "common.h"

#include "engine/message.h"
#include "slus/data.h"

/* Updates the runtime scale and scaled value from lookup tables. */
void update_text_row_scale(u8 *entity, u8 unused_scale) {
    u8 *runtime_data = entity + 0x8C;

    runtime_data[0x25] = message_mode_row_scale[entity[2]];
    *(s16 *)(runtime_data + 0x0E) = message_row_heights[runtime_data[0x2A]] * runtime_data[0x25];
}
