#include "common.h"

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

typedef struct Shared82E60 {
    u8 pad00[0x16];
    u16 flags16;
} Shared82E60;

extern Shared83160 D_80083160;
extern Shared82E60 D_80082E60;
extern s32 D_800814A0;


extern void *jtbl_8002EFDC[];
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
    s32 state;
    void **jump_table;
    register u8 *event_page ASM_REG("$3") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register Shared83160 *event_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    static void *const case_labels[] = {
        &&L_case_0, &&L_case_1, &&L_case_2, &&L_case_3,
        &&L_case_4, &&L_default
    };
    (void)case_labels;

    controller->timer++;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(event_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    event_state = (Shared83160 *)(event_page + 0x3160);

    if (controller->state < 4 && (event_state->flags10 & 0x40)) {
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
    {
        u8 *jump_page = (u8 *)0x80030000;
        ASM_KEEP_NV(jump_page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        jump_table = (void **)(jump_page - 0x1024);
        ASM_KEEP_NV(jump_table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
    goto *jump_table[state];

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
#line 900 "x"
        {
            register u8 *state_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            Shared82E60 *shared_state;
            s32 zero;
            s32 notify_id;
            register s32 third_zero ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            notify_id = 6;
            zero = 0;
            ASM_KEEP_NV(notify_id);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            third_zero = zero;
            ASM_KEEP_NV(third_zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            state_page = (u8 *)0x80080000;
            ASM_KEEP_NV(state_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            shared_state = (Shared82E60 *)(state_page + 0x2E60);
            ASM_KEEP_NV(shared_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            shared_state->flags16 |= 0x8000;
            func_80041094(notify_id, zero, third_zero, zero, shared_state->flags16 ^ 1);
        }
#line 1000 "x"
        ((u16 *)controller)[-1] |= 0x8000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        D_800814A0 |= 0x8000;
        return;

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
#line 900 "x"
        {
            register u8 *state_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            Shared82E60 *shared_state;
            s32 zero;
            s32 notify_id;
            register s32 third_zero ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            notify_id = 6;
            zero = 0; ASM_USE_NV(zero); /* cross-jump boundary; MUST stay on this line -- see NOTES.md */
            ASM_KEEP_NV(notify_id);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            third_zero = zero;
            ASM_KEEP_NV(third_zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            state_page = (u8 *)0x80080000;
            ASM_KEEP_NV(state_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            shared_state = (Shared82E60 *)(state_page + 0x2E60);
            ASM_KEEP_NV(shared_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            shared_state->flags16 |= 0x8000;
            func_80041094(notify_id, zero, third_zero, zero, shared_state->flags16 ^ 1);
        }
#line 1000 "x"
        ((u16 *)controller)[-1] |= 0x8000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        D_800814A0 |= 0x8000;
        return;
}
