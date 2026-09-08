#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378(void *, s32, s32, s32);
s32 func_800AD9B4(s32, s32);
extern u8 D_80170F20;
extern u8 D_80173B98;

typedef struct S_80172538_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x17];
    u8 unk_A7;
} S_80172538_0;   /* object in func_80172538 */

/* Selects the object's data pointer by its flag after both update checks succeed. */
void func_80172538(void *state, s32 motion, s32 entity, s32 actor) {
    S_80172538_0 *object = state;
    s32 saved_entity = entity;
    s32 saved_actor = actor;
    void *next_data;

    if ((func_800AB378(state, motion, entity, actor) != 0) &&
        ((func_800AD9B4(saved_entity, saved_actor) << 0x10) > 0)) {
        if (object->unk_A7 != 0) {
            next_data = &D_80173B98;
        } else {
            next_data = &D_80170F20;
        }
        object->unk_8C = next_data;
    }
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_entity);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
