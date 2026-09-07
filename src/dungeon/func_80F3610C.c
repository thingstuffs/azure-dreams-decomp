#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_8017390C_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017390C_0;   /* arg0 in func_8017390C */

typedef struct S_8017390C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x28];
    u8 unk_48;
    u8 unk_49;
} S_8017390C_1;   /* saved_arg3 in func_8017390C */

typedef struct S_8017390C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017390C_2;   /* temp_s0 in func_8017390C */

typedef struct S_8017390C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_8017390C_3;   /* saved_arg1 in func_8017390C */

typedef struct S_8017390C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017390C_4;   /* temp_v1 in func_8017390C */

typedef struct S_8017390C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8017390C_5;   /* temp_s1 in func_8017390C */

typedef struct S_8017390C_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017390C_6;   /* arg2 in func_8017390C */

typedef struct {
    s32 value;
} __attribute__((packed)) Unaligned32;


extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 func_8004A658();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_800BC26C();

extern s32 D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80173770;
extern s16 D_8008346A;

void func_8017390C(S_8017390C_0 *arg0, void *arg1, S_8017390C_6 *arg2, void *arg3)
{
    s32 temp_a2;
    s32 temp_word;
    s32 state;
    register void *saved_arg1 ASM_REG("$19") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    register void *saved_arg3 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *temp_s0;
    S_8017390C_5 *temp_s1;
    void *temp_s5;
    void *temp_v0;
    S_8017390C_4 *temp_v1;
    void *call_arg0;
    void *call_obj;
    register s32 angle ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */

    saved_arg3 = arg3;
    state = arg0->unk_9B;
    if (state == 1) {
        goto active;
    }
    if (state >= 2) {
        goto high_state;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

high_state:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (D_8008346A != 0) {
        goto done;
    }
    arg0->unk_9B = 1;

active:
    if (((S_8017390C_1 *)saved_arg3)->unk_49 != 0) {
        temp_s0 = func_8003FC64(0x12);
        if (temp_s0 != 0) {
            call_obj = temp_s0;
            temp_v1 = ((S_8017390C_2 *)temp_s0)->unk_08;
            temp_word = ((S_8017390C_3 *)saved_arg1)->unk_00;
            temp_s1 = ((S_8017390C_2 *)temp_s0)->unk_0C;
            temp_v1->unk_00 = temp_word;
            temp_v1->unk_04 = ((S_8017390C_3 *)saved_arg1)->unk_04;
            temp_a2 = ((S_8017390C_3 *)saved_arg1)->unk_08;
            temp_v1->unk_10 = 0;
            temp_v1->unk_0C = 0;
            temp_v1->unk_14 = 0xFFEE0000;
            temp_v1->unk_08 = temp_a2;
            func_8004491C(call_obj, &D_80045340, temp_a2);
            temp_s1->unk_0C = 0x808080;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            angle = 0xC90;
            temp_s1->unk_1E = angle;
            temp_s5 = (u8 *)temp_s0 + 0x20;
            temp_s1->unk_1C = angle;
            saved_arg1 = temp_s5;
            if (((S_8017390C_1 *)saved_arg3)->unk_49 == 0x12) {
                temp_v0 = &D_8006E240;
            } else {
                temp_v0 = (void *)func_8004A658(
                    ((S_8017390C_1 *)saved_arg3)->unk_49, ((S_8017390C_1 *)saved_arg3)->unk_48);
            }
            temp_s1->unk_08 = temp_v0;
            ASM_KEEP(temp_v0);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ((S_8017390C_3 *)saved_arg1)->unk_A8 = arg2->unk_24;
            ((S_8017390C_3 *)saved_arg1)->unk_AA = arg2->unk_25;
            *(Unaligned32 *)((u8 *)temp_s5 + 0x48) =
                *(Unaligned32 *)((u8 *)saved_arg3 + 0x48);
            func_800BC26C(temp_s0, 0, 0, 0);
            ((S_8017390C_2 *)temp_s0)->unk_10 = &D_80173770;
        }
        ((S_8017390C_1 *)saved_arg3)->unk_48 = 0;
        ((S_8017390C_1 *)saved_arg3)->unk_49 = 0;
    }

    arg2->unk_10 = 0x20;
    arg2->unk_12 -= 0x80;
    arg2->unk_14 |= 0xC;
    ((S_8017390C_1 *)saved_arg3)->unk_1C |= 0x10000000;
    arg2->unk_0C = 0x808080;
    arg0->unk_96 = 0x10;
    arg0->unk_9B++;
    func_800A56E0(0x805);
    goto done;

state_two:
    call_arg0 = arg0;
    ASM_KEEP(call_arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(saved_arg1);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800AD058(call_arg0, saved_arg1, arg2, saved_arg3);

done:
    return;
}
