#include "common.h"
#include "records/Rec_func_80021E88_arg1.h"

typedef struct S_80021E88_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    u8 pad_08[0x4C];
    union { s16 s; u16 u; } unk_54;   /* accessed as both */
} S_80021E88_0;   /* arg0 in func_80021E88 */

typedef struct S_80021E88_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    u16 unk_20;
    s16 unk_22;
} S_80021E88_1;   /* object in func_80021E88 */

typedef struct S_80021E88_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_80021E88_2;   /* arg2 in func_80021E88 */


typedef struct S_80021E88_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80021E88_4;   /* ((S_80021E88_0 *)arg0)->unk_04 in func_80021E88 */



extern void func_80021F18() __attribute__((noreturn));
extern void func_80022084() __attribute__((noreturn));
extern s32 func_800A2A18(void *, void *);
extern u32 D_80012D5C;
extern u8 D_800243F0[];
extern s32 D_80024438[];
extern s32 D_80024444[];

void func_80021E88(S_80021E88_0 *arg0, Rec_func_80021E88_arg1 *arg1, S_80021E88_2 *arg2) {
    s16 state;
    s32 value;
    s32 transition_value;
    register s32 one ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 transition ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 flags;
    S_80021E88_1 *object;

    object = arg0->unk_04;
    transition = 0;
    if (object->unk_18 == 0) {
        arg0->unk_00 = 0;
    }
    if (D_80012D5C >= 100U) {
        if (func_800A2A18(D_800243F0, arg1) != 0) {
            transition = 1;
            ASM_TAILSLOT_PIN(transition);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80021F18();
        }
        arg2->unk_08 = D_80024438[arg0->unk_54.s];
    }

    one = 1;
    state = arg0->unk_00;
    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return func_80022084(one);
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return func_80022084(one);

state_0:
    arg1->unk_08 += 0xFFF80000;
    if (arg1->unk_08 > 0) {
        goto done;
    }
    arg1->unk_08 = 0;
    arg2->unk_0C = 0x808080;
    arg0->unk_00 = one;
    func_80022084(one);

state_1:
    transition_value = transition;
    ASM_KEEP(transition_value);   /* MATCH pin: retail delay-slot fill depends on it */
    if (transition_value) {
        if (((S_80021E88_4 *)(arg0->unk_04))->unk_22 == 3) {
            object->unk_20 |= 1;
            arg2->unk_08 = D_80024444[arg0->unk_54.s];
            object->unk_22 = arg0->unk_54.u;
        }
    }
    one = 3;
    if (object->unk_22 == one) {
        goto done;
    }
    if (((S_80021E88_4 *)(arg0->unk_04))->unk_22 == arg0->unk_54.s) {
        arg0->unk_00 = one;
        func_80022084(one);
    }
    arg0->unk_00 = 2;
    func_80022084(one);

state_2:
    arg1->unk_08 += 0x80000;
    if (arg1->unk_08 > 0x3FFFFF) {
        arg1->unk_08 = 0x400000;
        func_80022084(0x80000);
    }
    goto done;

state_3:
    flags = object->unk_20;
    if (flags & 1) {
        object->unk_20 = flags | 1;
        arg2->unk_08 = D_80024444[arg0->unk_54.s];
    }

done:
    return;
}
