#include "shared/object_node.h"
#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/slus_callbacks.h"


#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))



extern s32 D_800E2178;

   /* temp_v0 in func_800242F0 */

   /* temp_v0_2 in func_800242F0 */

   /* temp_s0 in func_800242F0 */

   /* temp_a1 in func_800242F0 */

/* Creates a sprite object with initialized state and a copied, adjusted transform. */
void *func_800242F0(s32 state_value, B22_81892AF0_Copy24 *source_transform, s16 variant) {
    B22_81892AF0_Copy24 *transform;
    B22_81892AF0_S_81892AF0_2 *sprite;
    void *object;
    B22_81892AF0_S_81892AF0_1 *state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((B22_81892AF0_S_81892AF0_0 *)object)->unk_10 = func_8002420C;
        state = object + 0x20;
        ((B22_81892AF0_S_81892AF0_0 *)object)->unk_20 = state_value;
        state->unk_04 = 0;
        state->unk_06 = variant;
        sprite = ((B22_81892AF0_S_81892AF0_0 *)object)->unk_0C;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, &D_800E2178, 0);
        sprite->unk_1E = 0x1800;
        sprite->unk_1C = 0x1800;
        func_8004491C(object, func_80045340);
        transform = ((B22_81892AF0_S_81892AF0_0 *)object)->unk_08;
        *transform = *source_transform;
        ((B22_81892AF0_S_81892AF0_3 *)transform)->unk_14 = 0x10000;
        ((B22_81892AF0_S_81892AF0_3 *)transform)->unk_08 += 0xFD010000;
        return object;
    }
    return NULL;
}
