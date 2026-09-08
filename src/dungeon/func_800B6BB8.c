#include "common.h"

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
extern u8 D_800BC388[9];
extern s32 D_800814A0[3];

// Set bit 0x8000 in the first matching node's flags and the shared flags.
void func_800BC318(s32 targetId) {
    S_8003FFF0 *node;

    node = *D_80081498;
    if (node != NULL) {
        do {
            if ((node->kind == D_800BC388) && (node->id == targetId)) {
                u16 nodeFlags = node->flags;
                s32 sharedFlags = D_800814A0[0];

                node->flags = nodeFlags | 0x8000;
                D_800814A0[0] = sharedFlags | 0x8000;
                return;
            }
            node = node->next;
        } while (node != NULL);
    }
}
