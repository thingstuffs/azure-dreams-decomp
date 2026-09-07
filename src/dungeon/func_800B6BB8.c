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

void func_800BC318(s32 arg0) {
    S_8003FFF0 *node;

    node = *D_80081498;
    if (node != NULL) {
        do {
            if ((node->kind == D_800BC388) && (node->id == arg0)) {
                u16 flags = node->flags;
                s32 value = D_800814A0[0];

                node->flags = flags | 0x8000;
                D_800814A0[0] = value | 0x8000;
                return;
            }
            node = node->next;
        } while (node != NULL);
    }
}
