#include "common.h"

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

Object *func_8003FD64();
void func_8004491C();
void func_800B835C();
extern u8 D_80025AC4[12];
extern u8 D_800281FC[12];
extern u8 D_80028238[12];
extern u8 D_80028250[12];
extern u8 D_80045340[12];

void func_8195A35C(Object *arg0, s16 arg1) {
    Pair pair;
    Object *obj;
    Node *node;
    ObjectTail *tail;

    obj = func_8003FD64(0x212, arg0);
    if (obj != 0) {
        obj->field10 = D_80025AC4;
        func_8004491C(obj, D_80045340);
        obj->sprite->x = arg0->sprite->x;
        obj->sprite->y = arg0->sprite->y;
        obj->sprite->z = arg0->sprite->z;
        node = obj->node;
        node->field8 = D_800281FC;
        node->field1E = 0x2800;
        node->field1C = 0x2800;
        node->field6 = 8;
        node->field1A = arg1 + 0x400;
        tail = (ObjectTail *)((u8 *)obj + 0x20);
        node->fieldC = 0x808080;
        tail->owner = arg0;
        tail->angle = arg1;
        pair.first = 0x01400340;
        pair.second = 0x200020;
        func_800B835C(D_80028238, &pair, 0, 0);
        func_800B835C(D_80028250, &pair, 1, 0);
    }
}
