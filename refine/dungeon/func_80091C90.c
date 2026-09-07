#include "common.h"

typedef struct {
    u8 pad00[0x8C];
    s32 field8C;
    u8 pad90[8];
    u16 field98;
    s8 field9A;
    s8 field9B;
    u8 pad9C[0xA];
    s16 fieldA6;
} Entity;

typedef struct {
    u8 pad00[0x1C];
    s32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x30];
    s32 field5C;
} Actor;

typedef struct {
    u16 field0;
    u16 field2;
    u8 pad04[8];
    Actor *field0C;
} DungeonState;

extern DungeonState D_80083460;
extern void func_8009C93C(Actor *, s32, s16, s32, s32);
extern s32 func_800A6D30(void);
extern void func_80099F70(u32);
extern void func_8009F644(Actor *, s32, s32, s32);
extern s32 func_800A5C70(void);

/* Reset the entity state and initialize the active dungeon actor. */
s32 func_800973F0(Entity *entity, s32 unused, s32 action_param, Actor *actor) {
    DungeonState *state;

    entity->field98 |= 0x2000;
    func_8009C93C(actor, action_param, actor->field2A, 1, 0);
    if (actor->field1C & 0x400) {
        actor->field2A = (u16)actor->field2A + (func_800A6D30() & 0xE00);
    }
    entity->field9A = 0x37;
    state = &D_80083460;
    entity->field9B = 0;
    entity->field8C = 0;
    state->field0C = actor;
    entity->fieldA6 = 0;
    func_80099F70(actor->field5C);
    func_8009F644(actor, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        state->field2 |= 0x80;
    }
    return 0;
}
