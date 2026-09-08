#include "common.h"

typedef struct S_80081490 {
    /* 0x00 */ struct S_80081490 *next;
    /* 0x04 */ u8 pad[0x1E - 0x04];
    /* 0x1E */ u16 unk1E;
} S_80081490;

extern S_80081490 *D_80081490[3];
extern S_80081490 *D_80081498[3];

/* Returns whether counting all D_80081490 nodes and flagged D_80081498 nodes reaches the limit. */
s32 func_8003FA44(s32 limit) {
    S_80081490 *node;
    s32 count;

    count = 0;
    node = D_80081490[0];
    while (node != 0) {
        count++;
        if (!(count < limit)) {
            goto ret_true;
        }
        node = node->next;
    }

    node = D_80081498[0];
    if (node != 0) {
        do {
            if (node->unk1E & 0x200) {
                count++;
                if (!(count < limit)) {
ret_true:
                    return 1;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
