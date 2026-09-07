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

void func_800D7F38(void)
{
    u8 *obj;

    D_80083460.count++;
    obj = func_8003FD64(2, D_80083498);
    if (obj != 0) {
        *(void (**)(void))(obj + 0x10) = func_800D7FB8;
        obj += 0x20;
        *(u16 *)(obj + 4) = D_80083780.x;
        *(u16 *)(obj + 6) = D_80083780.y;
        *(u16 *)(obj + 8) = D_80083780.z - 0x30;
    }
}
