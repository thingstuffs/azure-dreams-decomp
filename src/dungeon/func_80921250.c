/* Relink of matched town/func_800BB95C; every changed retail word is a paired relocation. */
#define D_800B90B4 D_800F6020
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800F6020;

typedef struct S_800B90BC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B90BC_0;   /* temp_v0 in func_800F6250 */

/* Allocate an object and set its data pointer. */
void func_800F6250(void) {
    S_800B90BC_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->unk_10 = &D_800F6020;
    }
}
