#include "common.h"

typedef struct {
    void *callback0;
    void *callback4;
    u8 pad08[2];
    s16 timer;
    u8 pad0C[4];
    s16 id;
    u8 pad12[0x24];
    s16 x;
    s16 y;
} Entity;

extern void func_80099754(s32 arg0, s32 arg1, s32 arg2);
extern void func_80094984(void *arg0, void *arg1, s32 arg2);

extern Entity D_800834B8;
extern s32 D_80097D2C[3];
extern s32 D_8009A724;
extern u8 D_800D0090[];

__asm__(".set D_8009A724, 0x8009A724");

void func_8009A674(s32 arg0, s32 arg1, s32 arg2) {
    Entity *entity = &D_800834B8;
    s32 *context = (s32 *)((u8 *)entity - 0x20);
    s32 value = context[3];

    func_80099754(context[2], arg1, arg2);
    func_80094984(D_800D0090, entity, value);
    D_800834B8.callback0 = D_80097D2C;
    entity->callback4 = &D_8009A724;
    entity->id = arg0 & 0xFFF;
    entity->x = arg1;
    entity->y = arg2;
    entity->timer = 8;
}
