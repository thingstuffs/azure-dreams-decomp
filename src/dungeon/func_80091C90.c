#include "common.h"
#include "shared/dungeon_status.h"

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

extern void dungeonPrepareDirectionalAttack(Actor *, s32, s16, s32, s32);
extern s32 func_800A6D30(void);
extern void dungeonProcessUnflaggedLinkedEntriesAlt(u32);
extern void dungeonAppendPackedActionRecord(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);
extern s32 func_800A5C70(void);

/* Reset the entity state and initialize the active dungeon actor. */
s32 dungeonBeginActorAttack(Entity *entity, s32 unused, s32 action_param, Actor *actor) {

    entity->field98 |= 0x2000;
    dungeonPrepareDirectionalAttack(actor, action_param, actor->field2A, 1, 0);
    if (actor->field1C & 0x400) {
        actor->field2A = (u16)actor->field2A + (func_800A6D30() & 0xE00);
    }
    entity->field9A = 0x37;
    entity->field9B = 0;
    entity->field8C = 0;
    dungeonStatus.unk_0C = actor;
    entity->fieldA6 = 0;
    dungeonProcessUnflaggedLinkedEntriesAlt(actor->field5C);
    dungeonAppendPackedActionRecord(actor, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        dungeonStatus.flags |= 0x80;
    }
    return 0;
}
