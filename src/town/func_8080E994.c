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
extern void *D_80526454[];
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
extern void func_80529650(void) __attribute__((noreturn));
extern void func_805296D8(void) __attribute__((noreturn));
extern void func_8052974C(void) __attribute__((noreturn));
extern void func_805299DC(void) __attribute__((noreturn));
extern void func_80529AA4(void) __attribute__((noreturn));

void func_8080E994(State *state, Motion *motion, Actor *actor)
{
    State *st = state;
    Motion *mot = motion;
    Actor *act = actor;
    register Entity *entity ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 dispatch_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    Vec3 choices;
    s32 value;
    static void *const reachable_arms[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5,
        &&case_6
    };

    ASM_KEEP(st);   /* MATCH pin: retail schedule: same instructions, different order without it */
    entity = st->entity;
    choices = D_80526448;

    dispatch_a1 = 1;

    if (entity->flags20 & 8) {
        st->state = 6;
    }
    ASM_KEEP(dispatch_a1);   /* MATCH pin: retail basic-block layout depends on it */

    value = st->state;
    if ((u32)value >= 7) {
        goto done;
    }
    goto *D_80526454[value];

case_0:
    {
        s32 call_a0;
        register s32 call_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        u32 result_v0;
        s32 threshold;

        switch (st->kind) {
        default:
            return func_80529650();
        case 1:
            call_a1 = 10;
            ASM_TAILSLOT_PIN_TIED(call_a1);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_80529650();
        case 2:
            break;
        }

        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        {
            register s32 divisor ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
            divisor = 100;
            call_a0 = entity->field1E;
            ASM_KEEP(divisor);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            call_a0 /= divisor;
        }
        {
            s32 quotient;
            quotient = call_a0 / 10;
            ASM_KEEP(quotient);   /* MATCH pin: load-bearing for the whole function shape */
            result_v0 = quotient * 10;
            threshold = st->threshold;
            quotient = call_a0 - result_v0;
            if (threshold < quotient) {
                result_v0 = act->flags;
                result_v0 &= 0xff7f;
                ASM_TAILSLOT_PIN_TIED(result_v0);   /* MATCH pin: retail delay-slot fill depends on it */
                return func_805296D8();
            }
        }
        act->flags |= 0x80;
        st->field1D = 0;
        return func_80529AA4();
    }

case_1:
    {
        u32 result_v0;
        act->handler = D_80077C64;
        act->value = D_80077C68[0];
        act->mode = 0;
        act->variant = func_80071494() & 3;
        act->flags &= 0xff7f;

        value = st->kind;
        if (value == 0) {
            result_v0 = act->height;
            result_v0 += 5;
            ASM_TAILSLOT_PIN_TIED(result_v0);   /* MATCH pin: retail delay-slot fill depends on it */
            return func_8052974C();
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (value == 1) {
            act->height -= 5;
        }
        st->field1D = 0;
        st->state = 2;

        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8003EA54(act);
        mot->x += mot->dx;
        mot->y += mot->dy;
        mot->z += mot->dz;
        mot->dz += 0x30000;
        st->timer--;
        if (st->timer > 0) {
            goto done;
        }

        mot->z = -0x400000;
        mot->dz = ((func_80071494() & 0xff) << 11) - 0x180000;
        st->timer = (func_80071494() & 0xf) + 30;
        st->state = 3;
        return func_80529AA4();
    }

case_2:
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
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            st->state = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            goto done;
        }
        st->timer = 180;
        st->state = 4;
        act->value = D_80530130[st->kind];
        act->height = 0;
        act->mode = 0;
        act->variant = 0;
        mot->z = floor;
        return func_80529AA4();
    }

case_3:
        if (func_80240810(D_805300F4, mot, D_80290704, D_80132AE8)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            D_80012BCC = product * 8 + D_80012BCC;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            st->state = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            goto done;
        }
        st->timer = 31;
        st->state = 5;
        return func_80529AA4();

case_4:
    {
        u32 result_v0;
        if ((st->timer >> 2) & 1) {
            result_v0 = act->flags;
            result_v0 |= 0x80;
            ASM_TAILSLOT_PIN_TIED(result_v0);   /* MATCH pin: retail delay-slot fill depends on it */
            return func_805299DC();
        }
        act->flags &= 0xff7f;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (func_80240810(D_805300F4, mot, D_80290704, D_80132AE8)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            D_80012BCC = product * 8 + D_80012BCC;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            st->state = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            goto done;
        }
        st->state = 6;
        return func_80529AA4();
    }

case_5:
        func_8023FB18(&st->work[0]);
        *(u16 *)((u8 *)st - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
        goto done;

case_6:
done:
        return;
}
