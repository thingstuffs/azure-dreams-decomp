#include "common.h"

typedef struct S_8004FD78 {
    u8 pad00[0x10];   /* 0x00 */
    s32 unk10[5];     /* 0x10 - fixed-size id array (5 slots, per sibling struct) */
    s32 unk24;         /* 0x24 - live count */
} S_8004FD78;

extern s32 func_8002137C(void *a0);

/* Finds the resolved target ID's index, returning the count if absent or zero if empty. */
s32 func_8004FD78(void *id_list_data, void *object)
{
    S_8004FD78 *id_list = (S_8004FD78 *)id_list_data;
    s32 target_id = func_8002137C(object);
    s32 id_count = id_list->unk24;
    s32 id_index;

    for (id_index = 0; id_index < id_count; id_index++) {
        if (id_list->unk10[id_index] == target_id) {
            return id_index;
        }
    }
    return id_index;
}
