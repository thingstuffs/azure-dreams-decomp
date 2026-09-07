#include "common.h"

__asm__(".set jtbl_800898AC, 0x800898AC");
extern void *jtbl_800898AC[6];

typedef struct State {
    s16 state;
    s16 timer;
} State;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 unk10;
    s32 dz;
} Motion;

typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
} Position;

typedef struct Sprite {
    u8 pad0[0xC];
    u32 color;
    s16 unk10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_y;
    s16 scale_x;
} Sprite;

typedef struct Object {
    u8 pad0[8];
    Position *position;
    Sprite *sprite;
    void (*callback)(void);
} Object;

extern void func_8003DB94(Sprite *, void *, s32);
extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern void func_80053DA8(s32, s32);
extern void func_80067014(s32);
extern void func_800672D8(void *, void *);
extern void func_8006733C(void *, void *);
extern s32 rand(void);
extern void func_800BF15C(void);

extern u8 D_80045340[];
extern s32 D_800814A0[];
extern u8 D_800D231C[];
extern u8 D_800D2324[];
extern u8 D_800F15AC[];
extern u16 D_80113138[];

void func_800BEBA4(State *state, Motion *motion, u8 *arg2)
{
    u16 colors[16];
    s32 i;
    s32 c0;
    s32 c1;
    s32 c2;
    s32 old_dz;
    s32 gravity;
    s16 timer;
    u16 color;
    u16 *src;
    u16 *base;
    Object *obj;
    Sprite *sprite;
    static void *const keepalive[] = {
        &&L_case0,
        &&L_case1,
        &&L_case2,
        &&L_case3,
        &&L_case4,
        &&L_case5,
    };

    gravity = 0x38000;
    state->timer--;
    motion->x += motion->dx;
    motion->z += motion->dz;
    motion->dz += gravity;

    (void)keepalive;
    {
        s32 selector;

        selector = state->state;
        if ((u32)selector >= 6) {
            goto L_epilogue;
        }
        goto *jtbl_800898AC[(u32)selector];
    }

L_case0:
        if (state->timer > 0) {
            goto L_epilogue;
        }

        func_80053DA8(0x519, gravity);
        i = 15;
        do {
            obj = func_8003FC64(0x136);
            if (obj != 0) {
                obj->callback = func_800BF15C;
                func_8004491C(obj, D_80045340);
                sprite = obj->sprite;
                obj->position->x = motion->x + ((rand() & 0x1FF) - 0x100) * 0x2000;
                obj->position->y = motion->y + ((rand() & 0x1FF) - 0x100) * 0x2000;
                obj->position->z = motion->z;
                sprite->unk10 = 0x60;
                sprite->scale_x = 0x1000;
                sprite->scale_y = 0x1000;
                sprite->flags |= 0xC;
                func_8003DB94(sprite, D_800F15AC, 0);
                sprite->color = 0x606060;
            }
            i--;
        } while (i >= 0);
        state->timer = 8;
        state->state++;
        goto L_epilogue;

L_case1:
        if (state->timer > 0) {
            goto L_epilogue;
        }
        *(u16 *)(arg2 + 0x14) |= 0x80;
        state->timer = 0x40;
        state->state++;
        goto L_epilogue;

L_case2: {
        u16 *dst2;
        s32 max_color;
        s32 color_bias;

        func_8006733C(D_800D2324, colors);
        func_80067014(0);

        i = 15;
        max_color = 0x1F;
        color_bias = -0x8000;
        dst2 = &colors[15];
        do {
            color = *dst2;
            timer = state->timer;
            c0 = max_color - (((max_color - (color & 0x1F)) * timer) >> 6);
            c1 = max_color - (((max_color - ((s16)color >> 5 & 0x1F)) * timer) >> 6);
            c2 = max_color - (((max_color - ((s16)color >> 10 & 0x1F)) * timer) >> 6);
            *dst2 = (c2 << 10) + ((c1 << 5) + color_bias) + c0;
            i--;
            dst2--;
        } while (i >= 0);

        if (state->timer < 0x30) {
            i = 0;
            while (i < 0x10 - (state->timer >> 2)) {
                i++;
                c0 = (rand() % 3) * 8 + 0xF;
                c1 = (rand() % 3) * 8 + 0xF;
                c2 = (rand() % 3) * 8 + 0xF;
                colors[rand() & 0xF] = (c2 << 10) +
                                                ((c1 << 5) - 0x8000) + c0;
            }
        }

        func_800672D8(D_800D231C, colors);
        func_80067014(0);
        if (state->timer <= 0) {
            state->timer = 0x1E;
            state->state++;
        }
        goto L_epilogue;
    }

L_case3:
        i = 15;
        do {
            c0 = (rand() % 3) * 8 + 0xF;
            c1 = (rand() % 3) * 8 + 0xF;
            c2 = (rand() % 3) * 8 + 0xF;
            colors[i] = (c2 << 10) + ((c1 << 5) - 0x8000) + c0;
            i--;
        } while (i >= 0);
        func_800672D8(D_800D231C, colors);
        func_80067014(0);
        if (state->timer <= 0) {
            state->timer = 0x20;
            state->state++;
        }
        goto L_epilogue;

L_case4: {
        u16 *dst4;
        s32 max_color;
        s32 color_bias;

        i = 15;
        max_color = 0x1F;
        color_bias = -0x8000;
        dst4 = &colors[15];
        base = D_80113138;
        src = base + 15;
        do {
            color = *src;
            timer = state->timer;
            c0 = color & 0x1F;
            c1 = (color >> 5) & 0x1F;
            c2 = (color >> 10) & 0x1F;
            c0 += ((max_color - c0) * timer) >> 5;
            c1 += ((max_color - c1) * timer) >> 5;
            c2 += ((max_color - c2) * timer) >> 5;
            *dst4 = (c2 << 10) + ((c1 << 5) + color_bias) + c0;
            src--;
            dst4--;
            i--;
        } while (i >= 0);
        func_800672D8(D_800D231C, colors);
        func_80067014(0);
        if (state->timer <= 0) {
            state->state++;
        }
        goto L_epilogue;
    }

L_case5:
        func_800672D8(D_800D231C, D_80113138);
        func_80067014(0);
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
L_epilogue:
    ;
}
