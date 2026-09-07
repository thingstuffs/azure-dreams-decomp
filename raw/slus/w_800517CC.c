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

void func_800517CC(
    EffectState800517CC *arg0,
    VecState800517CC *arg1,
    ColorState800517CC *arg2)
{
    u32 idx;
    void **table;
    static void *const keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7
    };

    (void)keepalive;
    arg0->timer++;
    func_800478B8(arg2);

    idx = arg0->state;
    if (idx >= 8) {
        goto state_default;
    }
    table = jtbl_8002E964;
    goto *table[idx];

state_0:
    if (arg0->trigger != 0) {
        arg0->trigger = 0;
        arg0->timer = 0;
        arg0->state = (u16)arg0->state + 1;
    }
    return;

state_1:
    if ((s16)arg0->timer >= 0x60) {
        arg0->timer = 0;
        arg0->state = (u16)arg0->state + 1;
    }
    return;

state_2:
    arg1->x = 0x01A00000 - ((rsin((s16)arg0->timer << 4) >> 4) << 16);
    arg1->y = ((rcos((s16)arg0->timer << 4) >> 4) << 14) + 0x00200000;
    if ((s16)arg0->timer >= 0x40) {
        arg0->timer = 0;
        arg0->state = (u16)arg0->state + 1;
    }
    return;

state_3:
    arg1->x = 0x00C00000 - ((rcos((s16)arg0->timer << 5) >> 4) << 13);
    arg1->y = ((rsin((s16)arg0->timer << 5) >> 4) << 12) + 0x00200000;
    if ((s16)arg0->timer >= 0x20) {
        arg1->z = 0x00800000;
        arg0->wait = (rand() % 64) + 0x20;
        arg0->timer = 0;
        arg0->state = (u16)arg0->state + 1;
    }
    return;

state_4:
    if ((s16)arg0->timer < arg0->wait) {
        goto check_trigger;
    }
    {
        s32 v = (u16)arg0->state + 1;
        arg0->timer = 0;
        arg0->state = v;
    }
    goto check_trigger;

state_5:
    {
        register s32 a ASM_REG("$2");
        register s32 t ASM_REG("$3");
        register s32 b ASM_REG("$2");
        register s32 o ASM_REG("$4");
        register s32 sgn ASM_REG("$2");
        register s32 vx ASM_REG("$2");
        register s32 x ASM_REG("$4");

        a = rcos(((s16)arg0->timer + 0x100) << 3) >> 4;
        t = (a * 3) << 11;
        b = arg1->x;
        o = (s32)0xFF280000;
        b += o;
        t -= b;
        sgn = (s32)((u32)t >> 31);
        t += sgn;
        t >>= 1;
        vx = arg1->vx + t;
        x = arg1->x + vx;
        arg1->vx = vx;
        arg1->x = x;
    }

    {
        register s32 t ASM_REG("$2");
        register s32 b ASM_REG("$3");
        register s32 o ASM_REG("$4");
        register s32 sgn ASM_REG("$3");
        register s32 vy ASM_REG("$3");
        register s32 y ASM_REG("$4");

        t = rcos((s16)arg0->timer << 3) >> 4;
        t <<= 10;
        b = arg1->y;
        o = (s32)0xFFD40000;
        b += o;
        t -= b;
        sgn = (s32)((u32)t >> 31);
        t += sgn;
        t >>= 1;
        vy = arg1->vy + t;
        y = arg1->y + vy;
        arg1->vy = vy;
        arg1->y = y;
    }

    if ((s16)arg0->timer < 0x100) {
        goto check_trigger;
    }
    {
        s32 v = (u16)arg0->state + 1;
        arg0->timer = 0;
        arg0->state = v;
    }
    goto check_trigger;

state_6:
    {
        register s32 a ASM_REG("$2");
        register s32 t ASM_REG("$3");
        register s32 b ASM_REG("$2");
        register s32 o ASM_REG("$4");
        register s32 sgn ASM_REG("$2");
        register s32 vx ASM_REG("$2");
        register s32 x ASM_REG("$4");

        a = rcos((s16)arg0->timer << 4) >> 4;
        t = (a * 3) << 11;
        b = arg1->x;
        o = (s32)0xFF280000;
        b += o;
        t -= b;
        sgn = (s32)((u32)t >> 31);
        t += sgn;
        t >>= 1;
        vx = arg1->vx + t;
        x = arg1->x + vx;
        arg1->vx = vx;
        arg1->x = x;
    }

    {
        register s32 t ASM_REG("$2");
        register s32 b ASM_REG("$3");
        register s32 o ASM_REG("$4");
        register s32 sgn ASM_REG("$3");
        register s32 vy ASM_REG("$3");
        register s32 y ASM_REG("$4");

        t = rcos(((s16)arg0->timer + 0x80) << 4) >> 4;
        t <<= 10;
        b = arg1->y;
        o = (s32)0xFFD40000;
        b += o;
        t -= b;
        sgn = (s32)((u32)t >> 31);
        t += sgn;
        t >>= 1;
        vy = arg1->vy + t;
        y = arg1->y + vy;
        arg1->vy = vy;
        arg1->y = y;
    }

    if ((s16)arg0->timer < 0x80) {
        goto check_trigger;
    }
    arg0->wait = (rand() % 64) + 0x20;
    arg0->timer = 0;
    arg0->state = 4;

check_trigger:
    if (arg0->trigger != 0) {
        arg0->trigger = 0;
        arg0->timer = 0;
        arg0->state = 7;
    }
    return;

state_7:
    arg1->x += (s32)0xFFF40000;
    arg1->y += 0x00020000;
    if ((s16)arg0->timer < 0x40) {
        return;
    }
    goto destroy;

state_default:
    arg2->b = 0;
    arg2->g = 0;
    arg2->r = 0;

destroy:
    ((ParentState800517CC *)arg0->parent)->child10 = 0;
    ((ParentState800517CC *)arg0->parent)->timer++;
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
