#include "modules/dungeon_ovl_18e8800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in func_80024124, addressed as arg0[-1] */








/* Advance effect motion and lifetime, updating its object and marking completion. */
void func_80024124(B31_818C8924_EffectState *effect, s32 *position, B31_818C8924_EffectObject *object)
{
    u16 timer;
    u16 life;

    effect->x += effect->vx;
    effect->y += effect->vy;
    effect->z += effect->vz;
    position[0] += effect->x;
    position[1] += effect->y;
    position[2] += effect->z;

    D_80024D04 = 1;
    timer = effect->timer + 1;
    effect->timer = timer;
    if (!(timer & 1)) {
        func_800478B8(object);
    }

    object->field1C += 200;
    object->field1E += 200;

    life = effect->life - 1;
    effect->life = life;
    if ((life << 16) <= 0) {
        ((B31_818C8924_S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    if (object->flags & 0x8000) {
        ((B31_818C8924_S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
