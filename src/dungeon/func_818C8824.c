#include "modules/dungeon_ovl_18e8800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in func_80024024, addressed as arg0[-1] */








/* Apply the effect offset, update its object, and flag expired or inactive effects. */
void func_80024024(B31_818C8824_EffectState *state, s32 *position, B31_818C8824_EffectObject *object)
{
    u16 life;

    position[0] += state->x;
    position[1] += state->y;
    D_80024D04 = 1;
    position[2] += state->z;
    func_800478B8(object);
    object->field1C += 0x80;
    object->field1E += 0x80;
    life = state->life - 1;
    state->life = life;
    if ((life << 16) <= 0) {
        ((B31_818C8824_S_818C8824_0_pre *)state)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    if (object->flags & 0x8000) {
        ((B31_818C8824_S_818C8824_0_pre *)state)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
