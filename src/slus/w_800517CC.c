#include "common.h"

typedef struct EffectState800517CC {
    void *parent;
    s16 state;
    u16 timer;
    s16 wait;
    s16 unkA;
    s16 trigger;
} EffectState800517CC;

typedef struct VecState800517CC {
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
} VecState800517CC;

typedef struct ColorState800517CC {
    u8 pad[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorState800517CC;

typedef struct ParentState800517CC {
    u8 pad0[6];
    u16 timer;
    u8 pad8[8];
    void *child10;
} ParentState800517CC;

extern void func_800478B8(void *);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern s32 rand(void);
extern void *jtbl_8002E964[8];
extern s32 D_800814A0[3];

/* Update the effect motion state and detach it from its parent when finished. */
void func_800517CC(
    EffectState800517CC *effect,
    VecState800517CC *motion,
    ColorState800517CC *color)
{
    u32 state_index;
    void **state_table;
    static void *const keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7
    };

    (void)keepalive;
    effect->timer++;
    func_800478B8(color);

    state_index = effect->state;
    if (state_index >= 8) {
        goto state_default;
    }
    state_table = jtbl_8002E964;
    goto *state_table[state_index];

state_0:
    if (effect->trigger != 0) {
        effect->trigger = 0;
        effect->timer = 0;
        effect->state = (u16)effect->state + 1;
    }
    return;

state_1:
    if ((s16)effect->timer >= 0x60) {
        effect->timer = 0;
        effect->state = (u16)effect->state + 1;
    }
    return;

state_2:
    motion->x = 0x01A00000 - ((rsin((s16)effect->timer << 4) >> 4) << 16);
    motion->y = ((rcos((s16)effect->timer << 4) >> 4) << 14) + 0x00200000;
    if ((s16)effect->timer >= 0x40) {
        effect->timer = 0;
        effect->state = (u16)effect->state + 1;
    }
    return;

state_3:
    motion->x = 0x00C00000 - ((rcos((s16)effect->timer << 5) >> 4) << 13);
    motion->y = ((rsin((s16)effect->timer << 5) >> 4) << 12) + 0x00200000;
    if ((s16)effect->timer >= 0x20) {
        motion->z = 0x00800000;
        effect->wait = (rand() % 64) + 0x20;
        effect->timer = 0;
        effect->state = (u16)effect->state + 1;
    }
    return;

state_4:
    if ((s16)effect->timer < effect->wait) {
        goto check_trigger;
    }
    {
        s32 next_state = (u16)effect->state + 1;
        effect->timer = 0;
        effect->state = next_state;
    }
    goto check_trigger;

state_5:
    {
        s32 cos_value;
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vx;
        s32 next_x;

        cos_value = rcos(((s16)effect->timer + 0x100) << 3) >> 4;
        accel = (cos_value * 3) << 11;
        displacement = motion->x;
        center_offset = (s32)0xFF280000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vx = motion->vx + accel;
        next_x = motion->x + next_vx;
        motion->vx = next_vx;
        motion->x = next_x;
    }

    {
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vy;
        s32 next_y;

        accel = rcos((s16)effect->timer << 3) >> 4;
        accel <<= 10;
        displacement = motion->y;
        center_offset = (s32)0xFFD40000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vy = motion->vy + accel;
        next_y = motion->y + next_vy;
        motion->vy = next_vy;
        motion->y = next_y;
    }

    if ((s16)effect->timer < 0x100) {
        goto check_trigger;
    }
    {
        s32 next_state = (u16)effect->state + 1;
        effect->timer = 0;
        effect->state = next_state;
    }
    goto check_trigger;

state_6:
    {
        s32 cos_value;
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vx;
        s32 next_x;

        cos_value = rcos((s16)effect->timer << 4) >> 4;
        accel = (cos_value * 3) << 11;
        displacement = motion->x;
        center_offset = (s32)0xFF280000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vx = motion->vx + accel;
        next_x = motion->x + next_vx;
        motion->vx = next_vx;
        motion->x = next_x;
    }

    {
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vy;
        s32 next_y;

        accel = rcos(((s16)effect->timer + 0x80) << 4) >> 4;
        accel <<= 10;
        displacement = motion->y;
        center_offset = (s32)0xFFD40000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vy = motion->vy + accel;
        next_y = motion->y + next_vy;
        motion->vy = next_vy;
        motion->y = next_y;
    }

    if ((s16)effect->timer < 0x80) {
        goto check_trigger;
    }
    effect->wait = (rand() % 64) + 0x20;
    effect->timer = 0;
    effect->state = 4;

check_trigger:
    if (effect->trigger != 0) {
        effect->trigger = 0;
        effect->timer = 0;
        effect->state = 7;
    }
    return;

state_7:
    motion->x += (s32)0xFFF40000;
    motion->y += 0x00020000;
    if ((s16)effect->timer < 0x40) {
        return;
    }
    goto destroy;

state_default:
    color->b = 0;
    color->g = 0;
    color->r = 0;

destroy:
    ((ParentState800517CC *)effect->parent)->child10 = 0;
    ((ParentState800517CC *)effect->parent)->timer++;
    *(u16 *)((u8 *)effect - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
