/* Relink of matched dungeon/func_80CBBA74; every changed retail word is a paired relocation. */
#include "modules/dungeon_ovl_cd7000.h"
extern void func_8014D760(void *, void *, void *, void *);

void func_80150E48(CL_CD7000_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonPropagateActorActionFlag(state,position,sprite,entity) != 0)
  state->handler=func_8014D760;
}
