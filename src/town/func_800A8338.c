#include "common.h"

typedef struct S_800A5A98_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u32 unk_08;
    u8 pad_0C[0x4];
    u32 unk_10;
    u8 pad_14[0xB4];
    u16 unk_C8;
} S_800A5A98_0;   /* input in func_800A5A98 */


typedef struct {
    void *callback;
    u8 pad04[4];
    u16 mode;
    u16 timer;
    u8 pad0C[4];
    u16 direction;
} State;

typedef struct {
    u8 pad00[10];
    s16 height;
    s32 x;
    s32 y;
    s32 value;
} Actor;

typedef struct {
    u8 pad00[2];
    s16 first;
    u8 pad06[2];
    s16 second;
    u8 tail[4];
} World;

extern u8 D_80083160[];
extern World D_80083780;
extern u8 D_800CFCEE;
extern u8 D_800FE488[];
extern s32 D_80100E20;
extern u8 D_800A5DF8;

extern s32 func_800374F4();
extern s32 func_8003BD84();
extern void SD_Call();
extern s32 func_8008C180();
extern void func_80094F58();
extern void func_80095094();
extern void func_80095388();
extern void func_800954F4();
extern s16 func_80095978();
extern void func_80095A94();
extern void func_80095C80();
extern void func_80097844();
extern s32 func_800A5894();
extern s32 func_800C1D44();


/* Update actor movement, height, turning, and action state from input. */
void func_800A5A98(State *state, Actor *actor) {
    u8 *input;
    s32 speed;
    s16 height_limit;
    s32 direction;
    s32 world_value;
    s32 sound_period;

    input = D_80083160;
    func_80095C80(actor);

    state->timer--;
    if ((s16)state->timer <= 0) {
        state->timer = func_800374F4(3) + 5;
        func_80097844(actor, (u16)func_800374F4(2) + 2);
    }

    direction = (((S_800A5A98_0 *)input)->unk_C8 + 0x800) & 0xFFF;
    *(volatile u16 *)((u8 *)state + 0x10) = direction;

    if (((S_800A5A98_0 *)input)->unk_08 & 0x20) {
        func_80094F58(direction, D_80100E20, actor);
        func_80097844(actor, (u16)func_800374F4(1));
    }

    if (((S_800A5A98_0 *)input)->unk_08 & 0x10) {
        func_80095094(actor);
        if ((((S_800A5A98_0 *)input)->unk_08 & 0x30) != 0x20) {
            goto after_second_update;
        }
    }
    func_80095094(actor);

after_second_update:
    height_limit = func_80095978(actor, D_800FE488);
    if (actor->height >= height_limit) {
        func_80095A94(actor, height_limit, D_800FE488);
    } else if ((&D_800CFCEE)[1] != 0) {
        actor->value = 0;
        func_800954F4(actor, height_limit);
    } else {
        func_80095388(actor, height_limit);
    }
    world_value = func_8008C180(D_80083780.first, D_80083780.second);
    if (func_800C1D44((u16)world_value) != 0) {
        actor->value -= func_800A5894(actor);
    }

    speed = func_8003BD84(actor->x, actor->y);
    if (D_80100E20 != 0) {
        {
            s32 speed_delta;
            speed_delta = D_80100E20 - speed;
            if (speed_delta < 0) {
                speed_delta = -speed_delta;
            }
            ASM_SCHED_BARRIER();
            sound_period = ((speed_delta * 7) / D_80100E20) + 2;
        }
        {
            u16 tick_count;
            tick_count = ((S_800A5A98_0 *)input)->unk_04;
            if ((tick_count % sound_period) == 0) {
                SD_Call(0x60A);
            }
        }
    }

    if (speed == 0) {
        ((S_800A5A98_0 *)input)->unk_C8 = (((S_800A5A98_0 *)input)->unk_C8 + 8) & 0xFFF0;
    } else {
        if ((((S_800A5A98_0 *)input)->unk_08 & 0x30) == 0x10) {
            speed = (D_80100E20 * 3) / 2;
        }
    }
    {
        s32 rounded_speed;
        rounded_speed = speed;
        if (speed < 0) {
            s32 rounding_bias;
            rounding_bias = 0xFFFF;
            rounded_speed = speed + rounding_bias;
        }
        speed = rounded_speed >> 16;
    }

    if ((*(volatile u32 *)((u8 *)input + 8)) & 0x2000) {
        {
            s32 angle;
            angle = ((S_800A5A98_0 *)input)->unk_C8;
            angle = angle - 0x10;
            angle = angle - speed;
            ((S_800A5A98_0 *)input)->unk_C8 = angle;
        }
        func_80097844(actor, (u16)func_800374F4(1));
    }

    if ((*(volatile u32 *)((u8 *)input + 8)) & 0x8000) {
        {
            s32 angle;
            angle = ((S_800A5A98_0 *)input)->unk_C8;
            angle = angle + 0x10;
            angle = angle + speed;
            ((S_800A5A98_0 *)input)->unk_C8 = angle;
        }
        func_80097844(actor, (u16)func_800374F4(1));
    }

    if ((((S_800A5A98_0 *)input)->unk_10 & 0x10) && (D_800CFCEE == 0)) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 1;
        return;
    }

    if (((S_800A5A98_0 *)input)->unk_10 & 0x100) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 0;
    }
}
