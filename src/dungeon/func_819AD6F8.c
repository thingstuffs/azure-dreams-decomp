#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

typedef struct Sprite {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Sprite;

typedef struct Node {
    u8 pad0[6];
    s16 field6;
    void *field8;
    s32 fieldC;
    u8 pad10[10];
    s16 field1A;
    s16 field1C;
    s16 field1E;
} Node;

typedef struct Object {
    u8 pad0[8];
    Sprite *sprite;
    Node *node;
    void *field10;
} Object;

typedef struct ObjectTail {
    u8 pad0[8];
    Object *owner;
    u8 padC[42];
    s16 angle;
} ObjectTail;

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

void func_800B835C();
extern void func_80024E60(void *, void *, void *);
extern u8 D_80027454[12];
extern u8 D_80027490[12];
extern u8 D_800274A8[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void func_80024EF8(Object *owner, s16 angle) {
    Pair rect;
    Object *spawned;
    Node *node;
    ObjectTail *tail;

    spawned = (Object *)func_8003FD64(0x212, (ObjectNodeHeader **)owner);
    if (spawned != 0) {
        spawned->field10 = func_80024E60;
        func_8004491C(spawned, (s32)func_80045340);
        spawned->sprite->x = owner->sprite->x;
        spawned->sprite->y = owner->sprite->y;
        spawned->sprite->z = owner->sprite->z;
        node = spawned->node;
        node->field8 = D_80027454;
        node->field1E = 0x2800;
        node->field1C = 0x2800;
        node->field6 = 8;
        node->field1A = angle + 0x400;
        tail = (ObjectTail *)((u8 *)spawned + 0x20);
        node->fieldC = 0x808080;
        tail->owner = owner;
        tail->angle = angle;
        rect.first = 0x01400340;
        rect.second = 0x200020;
        func_800B835C(D_80027490, &rect, 0, 0);
        func_800B835C(D_800274A8, &rect, 1, 0);
    }
}
