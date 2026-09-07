#include "common.h"

typedef struct {
    s8 pad0[0xA];
    u16 count;
    u8 padC[0x14];
} DungeonState;

typedef struct {
    u16 pad0;
    u16 x;
    u16 pad4;
    u16 y;
    u16 pad8;
    u16 z;
} Rotation;

extern void *func_8003FD64(s32 kind, void *owner);
extern void func_800D7FB8(void);
extern DungeonState D_80083460;
extern s32 D_80083498[4];
extern Rotation D_80083780;

/* Increment the dungeon count and initialize a new object's callback and rotation. */
void func_800D7F38(void)
{
    u8 *object;

    D_80083460.count++;
    object = func_8003FD64(2, D_80083498);
    if (object != 0) {
        *(void (**)(void))(object + 0x10) = func_800D7FB8;
        object += 0x20;
        *(u16 *)(object + 4) = D_80083780.x;
        *(u16 *)(object + 6) = D_80083780.y;
        *(u16 *)(object + 8) = D_80083780.z - 0x30;
    }
}
