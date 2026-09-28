#include "common.h"
#include "shared/dungeon_status.h"

extern void *func_8003FC64(s32);
extern s32 D_800A5D5C;


/* Set the object data pointer and increment the global state counter. */
void func_800A5DBC(void) {

    ((s32 **)func_8003FC64(0))[4] = &D_800A5D5C;
    dungeonStatus.unk_0A += 1;
}
