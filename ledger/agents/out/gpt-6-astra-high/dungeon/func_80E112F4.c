#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80171094[];
extern s32 D_8008346C[];
extern u8 D_80176460[8];
extern s16 D_80083228[5];
typedef struct Obj0 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad8c[0x8c - 0x16];
    u8 *field8c;
    u8 pad96[0x96 - 0x90];
    u16 field96;
    u16 field98;
    u8 pad9b[1];
    u8 state9b;
} Obj0;

typedef struct Obj2 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad24[0x24 - 0x16];
    u8 field24;
    u8 field25;
    u8 pad2c[0x2c - 0x26];
    u8 *field2c;
} Obj2;

typedef struct Obj3 {
    u8 pad14[0x14];
    u32 field14;
    u8 pad2a[0x2a - 0x18];
    s16 field2a;
    u8 pad46[0x46 - 0x2c];
    u16 field46;
    u8 pad60[0x60 - 0x48];
    struct Obj3 *field60;
} Obj3;

extern void func_800AD594(Obj3 *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_80047784(Obj2 *, u8, s32);
extern void func_80174CB0(s32);
extern void func_80174D0C(s32);
extern void func_80175D04(Obj0 *, void *, Obj2 *);
extern void func_801762A4(s32, Obj3 *);

/* Advance the timed object state sequence and update its direction from flags. */
void func_80174AF4(Obj0 *controller, void *context, Obj2 *object, Obj3 *actor) {
    s32 state;
    s32 old_state;
    u16 ticks_left;
    u16 delay;
    u16 object_flags;
    s32 actor_selector;

    state = controller->state9b;
    actor_selector = 1;
    if (state != actor_selector) {
        if ((s32) state < 2) {
            if (state == 0) {
                goto state0;
            }
            goto common;
        }
    } else {
        goto state1;
    }
    if (state != 2) {
        goto common;
    }
    goto state2;

state0:
    object_flags = object->field14;
    if (object_flags & 0x8000) {
        object->field14 = (u16) (object_flags | 0x6000);
        controller->state9b = 2;
        goto epilogue;
    }
    if (object->field04 != actor_selector) {
        if ((object_flags & 0x6000) == 0) {
            goto common;
        }
    } else if ((object_flags & 0x1000) == 0) {
        if ((object_flags & 0x6000) == 0) {
            goto common;
        }
    }
state0_call:
    func_80175D04(controller, context, object);
    actor_selector = 1;
    if ((actor->field14 & 0x4000) || (actor_selector = 0, (actor->field60->field14 & 0x4000) != 0)) {
        func_801762A4(actor_selector, actor);
    }
    func_800A56E0(0x80D);
    old_state = controller->state9b;
    delay = 0x20;
    controller->field96 = delay;
    controller->state9b = old_state + 1;
    goto common;

state1:
    ticks_left = controller->field96 - 1;
    controller->field96 = ticks_left;
    if ((ticks_left << 0x10) != 0) {
        if ((object->field14 | 0x8000) == 0) {
            goto common;
        }
    }
    old_state = controller->state9b;
    delay = 4;
    controller->field96 = delay;
    controller->state9b = old_state + 1;
    goto common;

state2:
    ticks_left = controller->field96 - 1;
    controller->field96 = ticks_left;
    if ((ticks_left << 0x10) != 0 && (object->field14 & 0xE000) == 0) {
        goto epilogue;
    }
    func_800AD594(actor, 0x400);
    func_800A2B04(context, object->field24, object->field25);
    controller->field8c = D_80171094;
    *D_8008346C = 0;
    actor->field46 &= 0x7FFF;
    goto common;

common:
    if (object->field14 & 0xE000) {
        object->field2c = D_80176460;
        func_80047784(object, D_80176460[((D_80083228[0] + actor->field2a + 0x100) >> 9) & 7], 0);
        controller->field98 &= 0xFFF7;
    }

epilogue:
    return;
}
