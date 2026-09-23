#include "common.h"

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Actor {
    void *handler;
    u8 mode;
    u8 variant;
    u8 pad06[2];
    s32 value;
    u8 pad0C[6];
    u16 height;
    u16 flags;
} Actor;

typedef struct Entity {
    u8 pad00[0x1e];
    s16 field1E;
    u16 flags20;
} Entity;

typedef struct State {
    s16 state;
    s16 timer;
    Entity *entity;
    u8 work[0x15];
    u8 field1D;
    u8 pad1E[0x36];
    s16 kind;
    s16 threshold;
} State;

extern Vec3 D_80526448;
extern s32 D_80530130[];
extern u8 D_805300F4[];
extern u8 D_80290704[];
extern u8 D_80132AE8[];
extern u8 D_80077C64[];
extern s32 D_80077C68[3];
extern volatile s32 D_80012BCC;
extern s32 D_80084D5C;

extern s32 func_80071494(void);
extern void func_8003EA54(Actor *);
extern s32 func_80240810(void *, Motion *, void *, void *);
extern void func_8023FB18(void *);

void func_80529594(State *st, Motion *mot, Actor *actor)
{
    Actor *act = actor;
    Entity *entity;
    s16 dispatch_a1;
    Vec3 choices;
    s32 value;

    entity = st->entity;
    choices = D_80526448;

    dispatch_a1 = 1;

    if (entity->flags20 & 8) {
        st->state = 6;
    }

    value = st->state;
    switch (value) {

    case 0:
    {
        s32 call_a0;
        u32 result_v0;
        s32 threshold;

        switch (st->kind) {
        default:
            break;
        case 1:
            dispatch_a1 = 10;
            break;
        case 2:
            dispatch_a1 = 100;
            break;
        }

        call_a0 = entity->field1E;
        call_a0 /= dispatch_a1;
        {
            s32 quotient;
            quotient = call_a0 / 10;
               /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            result_v0 = quotient * 10;
            threshold = st->threshold;
            quotient = call_a0 - result_v0;
            {
                u16 flags;

                if (threshold < quotient) {
                    flags = act->flags & 0xff7f;
                } else {
                    flags = act->flags | 0x80;
                }
                act->flags = flags;
            }
        }
        st->field1D = 0;
        return;
    }

    case 1:
    {
        u32 result_v0;
        act->handler = D_80077C64;
        act->value = D_80077C68[0];
        act->mode = 0;
        act->variant = func_80071494() & 3;
        act->flags &= 0xff7f;

        value = st->kind;
        if (value == 0) {
            act->height += 5;
        } else if (value == 1) {
            act->height -= 5;
        }
        st->field1D = 0;
        st->state = 2;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_8003EA54(act);
        mot->x += mot->dx;
        mot->y += mot->dy;
        mot->z += mot->dz;
        mot->dz += 0x30000;
        st->timer--;
        if (st->timer > 0) {
            return;
        }

        mot->z = -0x400000;
        mot->dz = ((func_80071494() & 0xff) << 11) - 0x180000;
        st->timer = (func_80071494() & 0xf) + 30;
        st->state = 3;
        return;
    }

    case 2:
    {
        s32 floor;
        s32 z;
        func_8003EA54(act);
        mot->z += mot->dz;
        mot->dz += 0x30000;
        z = mot->z;
        floor = -0x400000;
        if (z > floor) {
            mot->z = floor;
            mot->dz = (-mot->dz) >> 1;
        }
        if (func_80240810(D_805300F4, mot, D_80290704, D_80132AE8)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            D_80012BCC = product * 8 + D_80012BCC;
            (*(s16 *)((u8 *)st + 0)) = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->timer = 180;
        st->state = 4;
        act->value = D_80530130[st->kind];
        act->height = 0;
        act->mode = 0;
        act->variant = 0;
        mot->z = floor;
        return;
    }

    case 3:
        if (func_80240810(D_805300F4, mot, D_80290704, D_80132AE8)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            D_80012BCC = product * 8 + D_80012BCC;
            (*(s16 *)((u8 *)st + 0)) = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->timer = 31;
        st->state = 5;
        return;

    case 4:
    {
        u32 result_v0;
        if ((st->timer >> 2) & 1) {
            result_v0 = act->flags | 0x80;
        } else {
            result_v0 = act->flags & 0xff7f;
        }
        act->flags = result_v0;
        if (func_80240810(D_805300F4, mot, D_80290704, D_80132AE8)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            D_80012BCC = product * 8 + D_80012BCC;
            (*(s16 *)((u8 *)st + 0)) = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->state = 6;
        return;
    }

    case 5:
        func_8023FB18(&st->work[0]);
        *(u16 *)((u8 *)st - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
        return;

    case 6:
    default:
        return;
    }
}
