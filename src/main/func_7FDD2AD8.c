typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Owner {
    unsigned char pad0[0x20];
    s16 kind;
    unsigned char pad22[2];
    s16 height;
    u16 flags;
} Owner;

typedef struct State {
    Owner *owner;
    unsigned char pad4[4];
    u16 step;
    unsigned char padA[2];
    s16 direction;
} State;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 pad8;
    s32 dx;
    s32 dy;
} Motion;

typedef union MotionView {
    Motion fields;
    s16 half[10];
} MotionView;

extern void func_800478B8(void *);
extern u32 D_800814A0;
extern int abs(int);

void func_80089A38(State *state, Motion *motion, void *arg2)
{
    Owner *owner;
    s16 step;
    s16 short_value;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    s32 value;
    s32 check3;

    owner = state->owner;
    func_800478B8(arg2);
    if (owner->flags & 1)
        state->step = 255;

    step = state->step;
    if (step != 2) {
        if (step < 3) {
            if (step == 0)
                goto epilogue;
            if (step == 1)
                goto state1;
            goto epilogue;
        }
        if (step == 3)
            goto state3;
        if (step == 255)
            goto state255;
        goto epilogue;
    }
    goto state2;

state1:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->dx += state->direction != 0 ? -0x10000 : 0x10000;
    motion->dy += 0x8000;
    if (motion->dx != 0)
        goto epilogue;
    goto increment;

state2:
    value = 232;
    if (state->direction != 0)
        value = 88;
    *(s16 *)((unsigned char *)motion + 2) = value;
    *(s16 *)((unsigned char *)motion + 6) = owner->height * 16 + 168;
    if (owner->kind != 32)
        goto epilogue;
    value = -0x20000;
    if (state->direction != 0)
        value = 0x20000;
    motion->dx = value;
    motion->dy = -0x40000;

increment:
    state->step++;
    goto epilogue;

state3:
    {
    check3 = motion->y;
    motion->x += motion->dx;
    motion->y += motion->dy;
    temp_v1 = motion->dx;
    motion->dx = temp_v1 + (temp_v1 >> 3);
    if (abs(((MotionView *)motion)->half[1]) < 361)
        goto epilogue;
    state->step = 255;
    goto epilogue;
    }

state255:
    *(u16 *)((unsigned char *)state - 2) |= 0x8000;
    D_800814A0 |= 0x8000;

epilogue:
    return;
}
