#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"

extern void *func_8003FD64(s32 kind, void *owner);
extern void func_800D7FB8(void);

/* Increment the dungeon count and initialize a new object's callback and rotation. */
void func_800D7F38(void)
{
    u8 *object;

    dungeonStatus.unk_0A++;
    object = func_8003FD64(2, ((s32 *)(&D_80083498)));
    if (object != 0) {
        *(void (**)(void))(object + 0x10) = func_800D7FB8;
        object += 0x20;
        *(u16 *)(object + 4) = ((u16)D_80083780.x.w.i);
        *(u16 *)(object + 6) = ((u16)D_80083780.y.w.i);
        *(u16 *)(object + 8) = ((u16)D_80083780.z.w.i) - 0x30;
    }
}
