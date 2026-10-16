/* Relink of matched dungeon/func_800CEE70; every changed retail word is a paired relocation. */
#define D_800D4494 D_8014DCE8
#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 dungeonCheckActorFloorTrap();                /* extern */
extern u8 D_8014DCE8;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D45D0_0;   /* arg0 in func_8014F4B0 */


s32 dungeonUpdateLinkedActorMotion(S_800D45D0_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
/* Select D_8014DCE8 after the countdown completes and the actor check succeeds. */
void func_8014F4B0(S_800D45D0_0 *state, M2C_UNK transform, M2C_UNK entity, M2C_UNK actor) {
    if ((dungeonUpdateLinkedActorMotion(state, transform, entity, actor) != 0) && ((dungeonCheckActorFloorTrap(entity, actor) << 0x10) > 0)) {
        state->unk_8C = &D_8014DCE8;
    }
}
