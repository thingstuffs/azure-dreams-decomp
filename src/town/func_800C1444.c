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
extern void SD_Call(s32, s32);
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

/* Update motion, spawn particles, and flash then restore the palette. */
void func_800BEBA4(State *state, Motion *motion, u8 *sprite_data)
{
    u16 colors[16];
    s32 index;
    s32 red;
    s32 green;
    s32 blue;
    s32 gravity;
    s16 timer;
    u16 color;
    u16 *source_color;
    u16 *original_palette;
    Object *particle;
    Sprite *sprite;
    static void *const state_labels[] = {
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

    (void)state_labels;
    {
        s32 phase;

        phase = state->state;
        if ((u32)phase >= 6) {
            goto L_epilogue;
        }
        goto *jtbl_800898AC[(u32)phase];
    }

L_case0:
    if (state->timer > 0) {
        goto L_epilogue;
    }

    SD_Call(0x519, gravity);
    index = 15;
    do {
        particle = func_8003FC64(0x136);
        if (particle != 0) {
            particle->callback = func_800BF15C;
            func_8004491C(particle, D_80045340);
            sprite = particle->sprite;
            particle->position->x = motion->x + ((rand() & 0x1FF) - 0x100) * 0x2000;
            particle->position->y = motion->y + ((rand() & 0x1FF) - 0x100) * 0x2000;
            particle->position->z = motion->z;
            sprite->unk10 = 0x60;
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            sprite->flags |= 0xC;
            func_8003DB94(sprite, D_800F15AC, 0);
            sprite->color = 0x606060;
        }
        index--;
    } while (index >= 0);
    state->timer = 8;
    state->state++;
    goto L_epilogue;

L_case1:
    if (state->timer > 0) {
        goto L_epilogue;
    }
    *(u16 *)(sprite_data + 0x14) |= 0x80;
    state->timer = 0x40;
    state->state++;
    goto L_epilogue;

L_case2: {
        u16 *output_color;
        s32 channel_max;
        s32 color_bias;

        func_8006733C(D_800D2324, colors);
        func_80067014(0);

        index = 15;
        channel_max = 0x1F;
        color_bias = -0x8000;
        output_color = &colors[15];
        do {
            color = *output_color;
            timer = state->timer;
            red = channel_max - (((channel_max - (color & 0x1F)) * timer) >> 6);
            green = channel_max - (((channel_max - ((s16)color >> 5 & 0x1F)) * timer) >> 6);
            blue = channel_max - (((channel_max - ((s16)color >> 10 & 0x1F)) * timer) >> 6);
            *output_color = (blue << 10) + ((green << 5) + color_bias) + red;
            index--;
            output_color--;
        } while (index >= 0);

        if (state->timer < 0x30) {
            index = 0;
            while (index < 0x10 - (state->timer >> 2)) {
                index++;
                red = (rand() % 3) * 8 + 0xF;
                green = (rand() % 3) * 8 + 0xF;
                blue = (rand() % 3) * 8 + 0xF;
                colors[rand() & 0xF] = (blue << 10) + ((green << 5) - 0x8000) + red;
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
    index = 15;
    do {
        red = (rand() % 3) * 8 + 0xF;
        green = (rand() % 3) * 8 + 0xF;
        blue = (rand() % 3) * 8 + 0xF;
        colors[index] = (blue << 10) + ((green << 5) - 0x8000) + red;
        index--;
    } while (index >= 0);
    func_800672D8(D_800D231C, colors);
    func_80067014(0);
    if (state->timer <= 0) {
        state->timer = 0x20;
        state->state++;
    }
    goto L_epilogue;

L_case4: {
        u16 *output_color;
        s32 channel_max;
        s32 color_bias;

        index = 15;
        channel_max = 0x1F;
        color_bias = -0x8000;
        output_color = &colors[15];
        original_palette = D_80113138;
        source_color = original_palette + 15;
        do {
            color = *source_color;
            timer = state->timer;
            red = color & 0x1F;
            green = (color >> 5) & 0x1F;
            blue = (color >> 10) & 0x1F;
            red += ((channel_max - red) * timer) >> 5;
            green += ((channel_max - green) * timer) >> 5;
            blue += ((channel_max - blue) * timer) >> 5;
            *output_color = (blue << 10) + ((green << 5) + color_bias) + red;
            source_color--;
            output_color--;
            index--;
        } while (index >= 0);
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
