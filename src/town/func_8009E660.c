#include "common.h"

typedef struct Actor Actor;
typedef struct Subject Subject;
typedef struct Motion Motion;
typedef struct Context Context;

typedef void (*TownCallback)(Actor *, Subject *, Motion *, Context *);

struct Motion {
    u16 field_00;
    u16 x;
    u16 field_04;
    u16 y;
    u16 field_08;
    s16 height;
};

struct Subject {
    u8 pad_00[0x3B];
    u8 state;
};

struct Actor {
    u8 pad_00[0x50];
    TownCallback state;
    u8 pad_54[0x28];
    s32 *value;
};

struct Context {
    u8 pad_00[8];
    s32 value;
};

typedef struct TownControl {
    u8 pad_00[0x10];
    Subject *subject;
    u8 pad_14[4];
    s32 index;
    u8 pad_1C[0x80];
} TownControl;

typedef struct TownState {
    u8 pad_00[8];
    Motion *target;
    u8 pad_0C[0x14];
    TownCallback current;
} TownState;

typedef struct MotionDelta {
    u16 x;
    u16 y;
} MotionDelta;

extern s16 func_8008F170(Motion *, void *);
extern void func_8008F27C(Subject *, Motion *, s16);
extern void func_8008F294(Subject *, Motion *);
extern void func_8008F664(Subject *, Motion *);
extern void func_8009BFD8(Actor *, Subject *, Motion *, Context *);
extern void func_8009C0C0(Actor *, Subject *, Motion *, Context *);

extern void D_800924EC(Actor *, Subject *, Motion *, Context *);
extern void D_8009B454(Actor *, Subject *, Motion *, Context *);
extern void D_8009B594(Actor *, Subject *, Motion *, Context *);
extern void func_8009BDC0(Actor *, Subject *, Motion *, Context *);

extern TownState D_80083498;
extern TownControl D_800CFCB4;
extern MotionDelta D_800CFDF0[];
extern MotionDelta D_800CFE08[];
extern u8 D_800FE488[];

/* Update town movement and height, then copy the actor value into the context. */
void func_8009BDC0(Actor *actor, Subject *subject, Motion *motion,
                   Context *context)
{
    TownControl *control = &D_800CFCB4;
    TownState *town_state;
    TownCallback *town_callback;
    MotionDelta *x_deltas;
    MotionDelta *y_deltas;
    TownCallback actor_callback;
    s16 surface_height;
    s32 control_index;
    s32 *actor_value;

    if ((control->subject != subject) ||
        ((control_index = control->index),
         ((u8 *)control)[control_index + 0x3A] != 1) ||
        ((town_callback = &D_80083498.current),
         (*town_callback != D_800924EC))) {
        func_8009BFD8(actor, subject, motion, context);
        goto motion_common;
    }

    town_state = &D_80083498;
    x_deltas = D_800CFDF0;
    motion->x += x_deltas[control_index].x;
    y_deltas = D_800CFE08;
    motion->y += y_deltas[control->index].x;
    town_state->target->x += x_deltas[control->index].x;
    town_state->target->y += y_deltas[control->index].x;

motion_common:
    surface_height = func_8008F170(motion, D_800FE488);
    func_8008F294(subject, motion);
    func_8008F664(subject, motion);
    if (subject->state == 0) {
        if (surface_height - motion->height >= 4) {
            func_8009C0C0(actor, subject, motion, context);
            goto tail;
        }
        func_8008F27C(subject, motion, surface_height);
    }

tail:
    actor_callback = actor->state;
    if ((actor_callback != D_8009B454) &&
        (actor_callback != D_8009B594) &&
        (actor_callback != func_8009BDC0)) {
        actor_value = actor->value;
        if (actor_value != 0) {
            context->value = *actor_value;
        }
    }
}
