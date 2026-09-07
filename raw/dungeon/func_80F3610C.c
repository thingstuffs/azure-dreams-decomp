#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} __attribute__((packed)) Unaligned32;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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

void func_8017390C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 temp_a2;
    s32 temp_word;
    s32 state;
    register void *saved_arg1 ASM_REG("$19") = arg1;
    register void *saved_arg3 ASM_REG("$18");
    void *temp_s0;
    register void *temp_s1 ASM_REG("$17");
    void *temp_s5;
    void *temp_v0;
    void *temp_v1;
    void *call_arg0;
    void *call_obj;
    register s32 angle ASM_REG("$2");

    saved_arg3 = arg3;
    state = FIELD(arg0, u8, 0x9B);
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
    FIELD(arg0, u8, 0x9B) = 1;

active:
    if (FIELD(saved_arg3, u8, 0x49) != 0) {
        temp_s0 = func_8003FC64(0x12);
        if (temp_s0 != 0) {
            call_obj = temp_s0;
            temp_v1 = FIELD(temp_s0, void *, 8);
            temp_word = FIELD(saved_arg1, s32, 0);
            temp_s1 = FIELD(temp_s0, void *, 0xC);
            FIELD(temp_v1, s32, 0) = temp_word;
            FIELD(temp_v1, s32, 4) = FIELD(saved_arg1, s32, 4);
            temp_a2 = FIELD(saved_arg1, s32, 8);
            FIELD(temp_v1, s32, 0x10) = 0;
            FIELD(temp_v1, s32, 0xC) = 0;
            FIELD(temp_v1, s32, 0x14) = 0xFFEE0000;
            FIELD(temp_v1, s32, 8) = temp_a2;
            func_8004491C(call_obj, &D_80045340, temp_a2);
            FIELD(temp_s1, s32, 0xC) = 0x808080;
            ASM_SCHED_BARRIER();
            angle = 0xC90;
            FIELD(temp_s1, s16, 0x1E) = angle;
            temp_s5 = (u8 *)temp_s0 + 0x20;
            FIELD(temp_s1, s16, 0x1C) = angle;
            saved_arg1 = temp_s5;
            if (FIELD(saved_arg3, u8, 0x49) == 0x12) {
                temp_v0 = &D_8006E240;
            } else {
                temp_v0 = (void *)func_8004A658(
                    FIELD(saved_arg3, u8, 0x49), FIELD(saved_arg3, u8, 0x48));
            }
            FIELD(temp_s1, void *, 8) = temp_v0;
            ASM_KEEP(temp_v0);
            FIELD(saved_arg1, s16, 0xA8) = FIELD(arg2, u8, 0x24);
            FIELD(saved_arg1, s16, 0xAA) = FIELD(arg2, u8, 0x25);
            *(Unaligned32 *)((u8 *)temp_s5 + 0x48) =
                *(Unaligned32 *)((u8 *)saved_arg3 + 0x48);
            func_800BC26C(temp_s0, 0, 0, 0);
            FIELD(temp_s0, void *, 0x10) = &D_80173770;
        }
        FIELD(saved_arg3, u8, 0x48) = 0;
        FIELD(saved_arg3, u8, 0x49) = 0;
    }

    FIELD(arg2, s16, 0x10) = 0x20;
    FIELD(arg2, u16, 0x12) -= 0x80;
    FIELD(arg2, u16, 0x14) |= 0xC;
    FIELD(saved_arg3, s32, 0x1C) |= 0x10000000;
    FIELD(arg2, s32, 0xC) = 0x808080;
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x805);
    goto done;

state_two:
    call_arg0 = arg0;
    ASM_KEEP(call_arg0);
    ASM_KEEP(saved_arg1);
    ASM_CLOBBER("$7");
    func_800AD058(call_arg0, saved_arg1, arg2, saved_arg3);

done:
    return;
}
