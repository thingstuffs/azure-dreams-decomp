#include "common.h"

typedef struct {
    u8 pad0[0xA];
    u16 counter;
} DungeonState;

typedef struct {
    u8 pad0[0x71];
    u8 flags;
    u8 pad1[0x46];
    u8 state;
} Entity;

extern Entity *D_800FBE1C;
extern DungeonState D_80083460;
extern u16 D_80013714;

/* Set the current entity state to three, decrement the counter, and clear the global and entity flags. */
void func_807B03C0(void) {
    Entity *entity;

    entity = (Entity *)((u8 *)D_800FBE1C + 0x20);
    entity->state = 3;
    D_80083460.counter--;
    D_80013714 &= 0xFFF7;
    entity->flags &= 0x7F;
}
