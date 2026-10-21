#include "common.h"

#include "common.h"
#include "engine/message.h"

extern u8 message_mode_row_scale[];
extern s32 message_row_heights[];

/* Updates the runtime scale and scaled value from lookup tables. */
void update_text_row_scale(u8 *entity) {
    u8 *runtime_data = entity + 0x8C;

    runtime_data[0x25] = message_mode_row_scale[entity[2]];
    *(s16 *)(runtime_data + 0x0E) = message_row_heights[runtime_data[0x2A]] * runtime_data[0x25];
}
