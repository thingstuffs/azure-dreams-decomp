#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/node.h"

typedef struct S_80033D08_0_pre {
    s32 unk_00;
    u8 pad_04[0x8];
} S_80033D08_0_pre;   /* the 0xC bytes before arg0 in unlink_node_if_registered, addressed as arg0[-1] */

/* Unlinks the enclosing block when its header field is nonzero. */
void unlink_node_if_registered(void *block_data) {
    if (((S_80033D08_0_pre *)block_data)[-1].unk_00 != 0) {
        unlink_node(block_data - 0x20);
    }
}
