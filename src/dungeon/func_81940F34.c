typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct {
    unsigned char pad_00[0x32];
    s16 timer;
} Entity;

typedef struct {
    unsigned char pad_00[8];
    s32 position;
} State;

extern s16 D_8002571C;
extern s32 D_800814A0[3];

void func_80024734(Entity *entity, State *state)
{
    s16 timer;

    state->position -= 0x18000;
    D_8002571C = 1;
    timer = entity->timer - 8;
    entity->timer = timer;
    if (timer <= 0) {
        ((u16 *)entity)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
