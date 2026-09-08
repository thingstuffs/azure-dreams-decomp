#include "common.h"
#include "m2c_compat.h"

extern s8 D_80082EA4;
extern void *D_800E3D7C;

typedef struct S_800F6738_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_800F6738_0;   /* var_v1 in func_800F6738 */

/* Set flag 0x800000 on type 0x32 entities in the ring and set the global state to 0x1F. */
void func_800F6738(void) {
    void *first_entity;
    S_800F6738_0 *entity;

    entity = D_800E3D7C;
    first_entity = entity;
    do {
        if (entity->unk_13 == 0x32) {
            entity->unk_14 = (s32) (entity->unk_14 | 0x800000);
        }
        entity = entity->unk_5C + 0x20;
    } while (entity != first_entity);
    D_80082EA4 = 0x1F;
}
