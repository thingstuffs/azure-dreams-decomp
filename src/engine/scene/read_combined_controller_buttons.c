#include "common.h"
#include "engine/input.h"
#include "engine/scene.h"

/* Returns inverted input bits packed from the two valid input records. */
s32 read_combined_controller_buttons(s32 unused_mode) {
    s32 input_bits;

    input_bits = -1;
    if (controller_port_one_reply[PAD_REPLY_STATUS] == 0) {
        if ((u32) (controller_port_one_reply[PAD_REPLY_ID] - 0x20) < 0x51U) {
            input_bits = 0xFFFF0000;
            input_bits |= controller_port_one_reply[PAD_REPLY_BUTTONS_LOW] | (controller_port_one_reply[PAD_REPLY_BUTTONS_HIGH] << 8);
        }
    }
    if ((controller_port_two_reply[PAD_REPLY_STATUS] == 0) && ((u32) (controller_port_two_reply[PAD_REPLY_ID] - 0x20)
        < 0x51U)) {
        input_bits = (input_bits & 0xFFFF) | ((controller_port_two_reply[PAD_REPLY_BUTTONS_LOW]
            | (controller_port_two_reply[PAD_REPLY_BUTTONS_HIGH] << 8)) << 0x10);
    }
    return ~input_bits;
}
