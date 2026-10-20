#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033CD8_0_pre {
    s32 unk_00;
    u8 pad_04[0x8];
} S_80033CD8_0_pre;   /* the 0xC bytes before arg0 in register_node_if_unregistered, addressed as arg0[-1] */


typedef struct RegistrationNode RegistrationNode;
s32 register_node(RegistrationNode *entry, s32 registration_id);                      /* extern */

/* Call register_node on the block header when the preceding status is zero. */
void register_node_if_unregistered(void *block_data, s32 registration_id) {
    if (((S_80033CD8_0_pre *)block_data)[-1].unk_00 == 0) {
        register_node((RegistrationNode *)(block_data - 0x20), registration_id);
    }
}
