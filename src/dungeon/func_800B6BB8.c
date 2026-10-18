#include "common.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8003FFF0 S_8003FFF0;
struct S_8003FFF0 {
    S_8003FFF0 *next;
    u8 unk04[0x0c];
    u8 *kind;
    u8 unk14[0x0a];
    u16 flags;
    s32 id;
};

extern S_8003FFF0 *D_80081498[4];
extern void retire_effect_when_owner_or_value_ends(void *context);

// Set bit 0x8000 in the first matching node's flags and the shared flags.
void retire_tracked_effect_by_id(s32 targetId) {
    S_8003FFF0 *node;

    node = *D_80081498;
    if (node != NULL) {
        do {
            if ((node->kind == retire_effect_when_owner_or_value_ends) && (node->id == targetId)) {
                u16 nodeFlags = node->flags;
                s32 sharedFlags = object_flag_block.flags;

                node->flags = nodeFlags | 0x8000;
                object_flag_block.flags = sharedFlags | 0x8000;
                return;
            }
            node = node->next;
        } while (node != NULL);
    }
}
