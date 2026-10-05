#include "common.h"

extern void func_800BA414(void *unused, s32 position, void *owner_data, s16 depth_bias);

/* Initialize scratchpad quad coordinates and process each linked node. */
s32 func_800BA384(void *node_payload, s32 node_value, u8 *node_data) {
    s16 *scratch = (s16 *)0x1F800000;
    register u8 *next_ptr;
    s32 next_value;
    s32 result;

    scratch[0x46] = 0;
    scratch[0x42] = 0;
    scratch[0x3E] = 0;
    scratch[0x3A] = 0;
    scratch[0x40] = -31;
    scratch[0x38] = -31;
    scratch[0x44] = 31;
    scratch[0x3C] = 31;
    scratch[0x3D] = -31;
    scratch[0x39] = -31;
    scratch[0x45] = 31;
    scratch[0x41] = 31;

    for (;;) {
        func_800BA414(node_payload, node_value, node_data, *(s16 *)(node_data + 6));
        next_ptr = *(u8 **)((u8 *)node_payload - 8);
        node_payload = next_ptr + 32;
        if (next_ptr == 0) {
            break;
        }
        node_value = *(s32 *)(next_ptr + 8);
        next_ptr = *(u8 **)(next_ptr + 12);
        node_data = next_ptr;
    }
    result = 0;
    return result;
}
