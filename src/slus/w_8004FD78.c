#include "common.h"

typedef struct S_8004FD78 {
    u8 pad00[0x10];   /* 0x00 */
    s32 unk10[5];     /* 0x10 - fixed-size id array (5 slots, per sibling struct) */
    s32 unk24;         /* 0x24 - live count */
} S_8004FD78;

extern s32 func_8002137C(void *a0);

/* Finds the object's ID in the list, returning its index or the nonnegative count if absent. */
s32 func_8004FD78(void *idListData, void *object)
{
    S_8004FD78 *idList = (S_8004FD78 *)idListData;
    s32 targetId = func_8002137C(object);
    s32 idCount = idList->unk24;
    s32 idIndex;

    for (idIndex = 0; idIndex < idCount; idIndex++) {
        if (idList->unk10[idIndex] == targetId) {
            return idIndex;
        }
    }
    return idIndex;
}
