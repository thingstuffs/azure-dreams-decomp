#include "common.h"

extern s32 D_800E3D7C[4];

typedef struct S_800C8078_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} S_800C8078_0;   /* arg0 in func_800C8078 */

typedef struct S_800C8078_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8078_1;   /* var_v1 in func_800C8078 */

typedef struct S_800C8078_2 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C8078_2;   /* temp_v0 in func_800C8078 */

/* Checks flag 0x4000 on the entity or its two global linked entities. */
s32 func_800C8078(S_800C8078_0 *entity) {
    s32 slot_index;
    S_800C8078_2 *linked_entity;
    void *slot_cursor;

    if (entity->unk_14 & 0x4000) {
        slot_index = 1;
        slot_cursor = (void *)(D_800E3D7C[0] + 4);
        do {
            linked_entity = ((S_800C8078_1 *)slot_cursor)->unk_AC;
            if ((linked_entity != 0) && ((linked_entity->unk_54 & 0x4000) != 0)) {
                return 1;
            }
            slot_index -= 1;
            slot_cursor -= 4;
        } while (slot_index >= 0);
        goto zero;
    }
    if ((entity->unk_54 & 0x4000) != 0) {
        return 1;
    }
zero:
    return 0;
}
