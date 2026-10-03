#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Child {
    u8 pad00[0x1E];
    u16 flags;
} Child;

typedef struct Controller {
    s16 state;
    s16 timer;
    s16 attached;
    s16 finished;
    s16 *script;
    Child *child0;
    Child *child1;
    Child *child2;
    Child *child3;
    void *group;
} Controller;

typedef struct Shared83160 {
    u8 pad00[0x10];
    s32 flags10;
} Shared83160;

extern Shared83160 D_80083160;
extern void *jtbl_8002EFDC[];

extern s32 D_800814A0;


extern void func_800530C4(void *);
extern s16 SD_Call(s32);
extern s32 func_80053EF0(s32);
extern void func_80051528(void *);
extern void func_800517AC(void *);
extern void func_800530A4(void *);
extern void func_80051CA4(void *);
extern void func_80051F38(void *);
extern void func_80041094(s32, s32, s32, s32, s32);

/* Advances the timed child sequence and retires the controller when all children finish. */
void func_80052144(Controller *controller)
{
    s32 notify_id;
    s32 zero;
    s32 third_zero;
    Shared83160 *events = &D_80083160;
    s32 state;
    static void *const case_labels[] = {
        &&L_case_0, &&L_case_1, &&L_case_2, &&L_case_3,
        &&L_case_4, &&L_default
    };
    (void)case_labels;

    controller->timer++;

    if (controller->state < 4 && (events->flags10 & 0x40)) {
        if (controller->child0 != 0) {
            controller->child0->flags |= 0x8000;
            controller->child0 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child1 != 0) {
            controller->child1->flags |= 0x8000;
            controller->child1 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child2 != 0) {
            controller->child2->flags |= 0x8000;
            controller->child2 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child3 != 0) {
            controller->child3->flags |= 0x8000;
            controller->child3 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->group != 0) {
            func_800530C4(controller->group);
        }
        SD_Call(0xB4);
        controller->timer = 0;
        controller->state = 4;
    }

    state = controller->state;
    if ((u32)state >= 5) {
        goto L_default;
    }
    goto *jtbl_8002EFDC[state];

L_case_0:
    if (func_80053EF0(4) != 1) {
        return;
    }
    func_80051528(controller->child0);
    func_800517AC(controller->child1);
    func_800530A4(controller->group);
    controller->timer = 0;
    controller->state++;
    return;
L_case_1:
    if (controller->child2 != 0) {
        if (controller->script[0] != controller->timer) {
            return;
        }
        func_80051CA4(controller->child2);
        controller->script = (s16 *)((u8 *)controller->script + 0x10);
        if (controller->script[0] != 0) {
            return;
        }
        controller->state++;
        return;
    }
    controller->state++;
    return;
L_case_2:
    if (controller->timer != 0x1C09) {
        return;
    }
    func_80051528(controller->child0);
    func_800517AC(controller->child1);
    controller->state++;
    return;
L_case_3:
    if (controller->timer != 0x1CCF) {
        return;
    }
    func_80051F38(controller->child3);
    controller->timer = 0;
    controller->state++;
    return;
L_case_4:
    if (controller->attached != controller->finished) {
        return;
    }
    notify_id = 6;
    zero = 0;
    third_zero = zero;
    goto notify;
L_default:
    if (controller->child0 != 0) {
        controller->child0->flags |= 0x8000;
        controller->child0 = 0;
        D_800814A0 |= 0x8000;
        controller->finished++;
    }
    if (controller->child1 != 0) {
        controller->child1->flags |= 0x8000;
        controller->child1 = 0;
        D_800814A0 |= 0x8000;
        controller->finished++;
    }
    if (controller->child2 != 0) {
        controller->child2->flags |= 0x8000;
        controller->child2 = 0;
        D_800814A0 |= 0x8000;
        controller->finished++;
    }
    if (controller->child3 != 0) {
        controller->child3->flags |= 0x8000;
        controller->child3 = 0;
        D_800814A0 |= 0x8000;
        controller->finished++;
    }
    if (controller->group != 0) {
        func_800530C4(controller->group);
    }
    if (controller->attached != controller->finished) {
        return;
    }
    SD_Call(0xB4);
    notify_id = 6;
    zero = 0;
    third_zero = zero;

notify:
    D_80082E60.flags16 |= 0x8000;
    func_80041094(notify_id, zero, third_zero, zero, D_80082E60.flags16 ^ 1);
    *((u16 *)controller - 1) |= 0x8000;
    D_800814A0 |= 0x8000;
}
