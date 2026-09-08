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

/* Updates phased motion and marks completion when stopped or out of bounds. */
void func_80089A38(State *state, Motion *motion, void *update_data)
{
    Owner *owner;
    s16 step;
    s32 x_velocity;
    s32 horizontal_value;
    s32 previous_y;

    owner = state->owner;
    func_800478B8(update_data);
    if (owner->flags & 1)
        state->step = 255;

    step = state->step;
    if (step != 2) {
        if (step < 3) {
            if (step == 0)
                goto epilogue;
            if (step == 1)
                goto advance_motion;
            goto epilogue;
        }
        if (step == 3)
            goto accelerate_motion;
        if (step == 255)
            goto mark_complete;
        goto epilogue;
    }
    goto reset_motion;

advance_motion:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->dx += state->direction != 0 ? -0x10000 : 0x10000;
    motion->dy += 0x8000;
    if (motion->dx != 0)
        goto epilogue;
    goto advance_step;

reset_motion:
    horizontal_value = 232;
    if (state->direction != 0)
        horizontal_value = 88;
    *(s16 *)((unsigned char *)motion + 2) = horizontal_value;
    *(s16 *)((unsigned char *)motion + 6) = owner->height * 16 + 168;
    if (owner->kind != 32)
        goto epilogue;
    horizontal_value = -0x20000;
    if (state->direction != 0)
        horizontal_value = 0x20000;
    motion->dx = horizontal_value;
    motion->dy = -0x40000;

advance_step:
    state->step++;
    goto epilogue;

accelerate_motion:
    {
        previous_y = motion->y;
        motion->x += motion->dx;
        motion->y += motion->dy;
        x_velocity = motion->dx;
        motion->dx = x_velocity + (x_velocity >> 3);
        if (abs(((MotionView *)motion)->half[1]) < 361)
            goto epilogue;
        state->step = 255;
        goto epilogue;
    }

mark_complete:
    *(u16 *)((unsigned char *)state - 2) |= 0x8000;
    D_800814A0 |= 0x8000;

epilogue:
    return;
}
