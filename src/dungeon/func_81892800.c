#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/object_flags.h"










/* Advance motion and rotation, then set completion flags when the timer exceeds its limit. */
void func_80024028(B22_81892800_Entity *entity, B22_81892800_Motion *motion, B22_81892800_Aux *aux) {
    s16 timer;

    entity->link->counter++;
    motion->x += motion->dx;
    motion->y += motion->dy;
    if (entity->timer < 8) {
        motion->dz *= 2;
    }
    motion->z += motion->dz;
    aux->angle += 0x300;
    timer = (u16)entity->timer + 1;
    entity->timer = timer;
    if (entity->limit < timer) {
        entity[-1].limit |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
