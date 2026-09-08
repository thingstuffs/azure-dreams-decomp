#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80173904_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_80173904_0;   /* state in func_80173904 */

typedef struct S_80173904_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80173904_1;   /* object in func_80173904 */

typedef struct S_80173904_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80173904_2;   /* display in func_80173904 */

typedef struct S_80173904_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173904_3;   /* held_arg1 in func_80173904 */

typedef struct S_80173904_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173904_4;   /* transform in func_80173904 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_801739E0(void);

extern u8 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80173738;

void func_80173904(
    s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5)
{
    register s32 product ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 factor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 normalized ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 work ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 held_arg4;
    register void *held_arg1;
    register u16 held_arg5 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_80173904_2 *display;
    S_80173904_0 *state;
    void *object;
    register void *transform ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *texture;
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    void *call_a1;
    s32 call_a2;

    (void)arg0;
    (void)arg2;
    (void)arg3;
    held_arg4 = arg4;
    held_arg1 = arg1;
    call_a0 = (void *)0x212;
    held_arg5 = arg5;
    ASM_KEEP_NV(held_arg4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    object = func_8003FC64((s32)call_a0);
    if (object != NULL) {
        work = held_arg4;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        call_a0 = object;
        call_a1 = &D_80045340;
        state = (u8 *)object + 0x20;
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = (s16)held_arg4;
        ((S_80173904_1 *)object)->unk_10 = &D_80173738;
        func_8004491C(call_a0, call_a1);

        display = ((S_80173904_1 *)object)->unk_0C;
        display->unk_10 = 0x60;
        display->unk_14 |= 0xC;
        if (rand() & 1) {
            display->unk_14 |= 1;
        }

        transform = ((S_80173904_1 *)object)->unk_08;
        state->unk_40 = ((S_80173904_3 *)held_arg1)->unk_00;
        dispatch_result = ((S_80173904_3 *)held_arg1)->unk_04;
        state->unk_44 = dispatch_result;
        dispatch_result = held_arg4 << 16;
        ASM_TAILSLOT_PIN(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        dispatch_result = func_801739E0();
        do {
            work = dispatch_result;
            ASM_KEEP_NV(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            dispatch_result = (s16)dispatch_result;
            if (dispatch_result < 0x1001) {
                break;
            }
            dispatch_result = work - 0x1000;
        } while (1);

        normalized = (s16)work;
        dispatch_result = func_80064584(normalized);
        factor = state->unk_20;
        product = factor * dispatch_result;
        dispatch_result = state->unk_40;
        factor = product << 4;
        dispatch_result += factor;
        ((S_80173904_4 *)transform)->unk_00 = dispatch_result;
        dispatch_result = func_800644B8(normalized);
        factor = state->unk_20;
        product = factor * dispatch_result;
        texture = D_800DEC70;
        dispatch_result = state->unk_44;
        factor = product << 4;
        dispatch_result += factor;
        ((S_80173904_4 *)transform)->unk_04 = dispatch_result;
        ((S_80173904_4 *)transform)->unk_0A = ((S_80173904_3 *)held_arg1)->unk_0A + held_arg5;

        display = ((S_80173904_1 *)object)->unk_0C;
        display->unk_1E = 0x1000;
        display->unk_1C = 0x1000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        dispatch_result = 0x40;
        ASM_KEEP(dispatch_result);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        display->unk_0C = dispatch_result;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        factor = dispatch_result;
        display->unk_0E = dispatch_result;
        dispatch_result = 0xC0;
        display->unk_0D = dispatch_result;
        state->unk_00 = factor;
        dispatch_result = display->unk_0D;
        call_a2 = 0;
        ASM_KEEP_NV(call_a2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        state->unk_01 = dispatch_result;
        dispatch_result = display->unk_0E;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        call_a0 = display;
        state->unk_02 = dispatch_result;
        func_8003DB94(call_a0, texture, call_a2);
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
    }
}

extern s32 func_801739E0(void) __attribute__((noreturn));
