#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/scene.h"

typedef struct S_8003E240_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 pad[0x24];
} S_8003E240_0;   /* &D_800830C0 in read_combined_controller_buttons */

typedef struct S_8003E240_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 pad[0x24];
} S_8003E240_1;   /* &D_800830E8 in read_combined_controller_buttons */


extern S_8003E240_0 controller_port_one_reply;
extern S_8003E240_1 controller_port_two_reply;

/* Returns inverted input bits packed from the two valid input records. */
s32 read_combined_controller_buttons(void) {
    s32 input_bits;

    input_bits = -1;
    if (controller_port_one_reply.unk_00 == 0) {
        if ((u32) (controller_port_one_reply.unk_01 - 0x20) < 0x51U) {
            input_bits = 0xFFFF0000;
            input_bits |= controller_port_one_reply.unk_03 | (controller_port_one_reply.unk_02 << 8);
        }
    }
    if ((controller_port_two_reply.unk_00 == 0) && ((u32) (controller_port_two_reply.unk_01 - 0x20)
        < 0x51U)) {
        input_bits = (input_bits & 0xFFFF) | ((controller_port_two_reply.unk_03
            | (controller_port_two_reply.unk_02 << 8)) << 0x10);
    }
    return ~input_bits;
}
