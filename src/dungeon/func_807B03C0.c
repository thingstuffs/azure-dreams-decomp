#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x71];
    u8 flags;
    u8 pad1[0x46];
    u8 state;
} Entity;


/* Set the current entity state to three, decrement the counter, and clear the global and entity flags. */
void func_800F7BC0(void) {
    Entity *entity;

    entity = (Entity *)((u8 *)D_800FBE1C + 0x20);
    entity->state = 3;
    dungeonStatus.unk_0A--;
    D_80013714 &= 0xFFF7;
    entity->flags &= 0x7F;
}
