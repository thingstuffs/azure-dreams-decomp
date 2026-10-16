/* Relink of matched dungeon/func_8028AD48; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

void func_8001DD48(void *step_state, s32 update_id)
{
    if (((s16 *) step_state)[2] > 0) {
        ((u16 *) step_state)[0] = (u16) (((u16 *) step_state)[0] - 1);
        ((u16 *) step_state)[1] = (u16) (((u16 *) step_state)[1] - 0x20);
        ((u16 *) step_state)[2] = (u16) (((u16 *) step_state)[2] - 1);
    }
}
