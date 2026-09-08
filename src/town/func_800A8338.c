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
extern void func_80053DA8();
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
extern void func_800A5BFC();
extern void func_800A5CF0();
extern s32 func_800C1D44();


void func_800A5A98(State *state, Actor *actor) {
    u8 *input;
    s32 amount;
    s16 limit;
    s32 direction;
    s32 temp;

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
    limit = func_80095978(actor, D_800FE488);
    if (actor->height >= limit) {
        func_80095A94(actor, limit, D_800FE488);
        {
            u32 page;
            page = 0x80080000;
            ASM_PAGEBASE_PIN(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_800A5BFC();
        }
    }

    if ((&D_800CFCEE)[1] != 0) {
        actor->value = 0;
        func_800954F4(actor, limit);
        {
            u32 page;
            page = 0x80080000;
            ASM_PAGEBASE_PIN(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_800A5BFC();
        }
    }

    func_80095388(actor, limit);
    temp = func_8008C180(D_80083780.first, D_80083780.second);
    if (func_800C1D44((u16)temp) != 0) {
        actor->value -= func_800A5894(actor);
    }

    amount = func_8003BD84(actor->x, actor->y);
    if (D_80100E20 != 0) {
        {
            s32 delta;
            delta = D_80100E20 - amount;
            if (delta < 0) {
                delta = -delta;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            temp = ((delta * 7) / D_80100E20) + 2;
        }
        {
            u16 sample;
            sample = ((S_800A5A98_0 *)input)->unk_04;
            if ((sample % temp) == 0) {
                func_80053DA8(0x60A);
            }
        }
    }

    if (amount == 0) {
        ((S_800A5A98_0 *)input)->unk_C8 = (((S_800A5A98_0 *)input)->unk_C8 + 8) & 0xFFF0;
        return func_800A5CF0();
    }

    if ((((S_800A5A98_0 *)input)->unk_08 & 0x30) == 0x10) {
        amount = (D_80100E20 * 3) / 2;
    }
    {
        s32 adjusted;
        adjusted = amount;
        if (amount < 0) {
            s32 bias;
            bias = 0xFFFF;
            adjusted = amount + bias;
        }
        amount = adjusted >> 16;
    }

    if ((*(volatile u32 *)((u8 *)input + 8)) & 0x2000) {
        {
            s32 angle;
            angle = ((S_800A5A98_0 *)input)->unk_C8;
            angle = angle - 0x10;
            angle = angle - amount;
            ((S_800A5A98_0 *)input)->unk_C8 = angle;
        }
        func_80097844(actor, (u16)func_800374F4(1));
    }

    if ((*(volatile u32 *)((u8 *)input + 8)) & 0x8000) {
        {
            s32 angle;
            angle = ((S_800A5A98_0 *)input)->unk_C8;
            angle = angle + 0x10;
            angle = angle + amount;
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
