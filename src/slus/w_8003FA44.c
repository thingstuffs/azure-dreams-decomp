#include "common.h"

typedef struct S_80081490 {
    /* 0x00 */ struct S_80081490 *next;
    /* 0x04 */ u8 pad[0x1E - 0x04];
    /* 0x1E */ u16 unk1E;
} S_80081490;

extern S_80081490 *D_80081490[3];
extern S_80081490 *D_80081498[3];

/* Walks the D_80081490 list counting nodes (up to a0), then continues counting
 * nodes in D_80081498 that have flag 0x200 set (offset 0x1E). Returns TRUE(1)
 * if the running count ever reaches the a0 limit, otherwise FALSE(0). */
s32 func_8003FA44(s32 a0) {
    S_80081490 *v1;
    s32 a1;

    a1 = 0;
    v1 = D_80081490[0];
    while (v1 != 0) {
        a1++;
        if (!(a1 < a0)) {
            goto ret_true;
        }
        v1 = v1->next;
    }

    v1 = D_80081498[0];
    if (v1 != 0) {
        do {
            if (v1->unk1E & 0x200) {
                a1++;
                if (!(a1 < a0)) {
ret_true:
                    return 1;
                }
            }
            v1 = v1->next;
        } while (v1 != 0);
    }
    return 0;
}
