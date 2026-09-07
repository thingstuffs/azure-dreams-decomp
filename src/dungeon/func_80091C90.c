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

s32 func_800973F0(Entity *arg0, s32 arg1, s32 arg2, Actor *arg3) {
    DungeonState *state;

    arg0->field98 |= 0x2000;
    func_8009C93C(arg3, arg2, arg3->field2A, 1, 0);
    if (arg3->field1C & 0x400) {
        arg3->field2A = (u16)arg3->field2A + (func_800A6D30() & 0xE00);
    }
    arg0->field9A = 0x37;
    state = &D_80083460;
    arg0->field9B = 0;
    arg0->field8C = 0;
    state->field0C = arg3;
    arg0->fieldA6 = 0;
    func_80099F70(arg3->field5C);
    func_8009F644(arg3, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        state->field2 |= 0x80;
    }
    return 0;
}
