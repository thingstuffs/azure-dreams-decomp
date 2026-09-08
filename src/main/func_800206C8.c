#include "common.h"


extern u8 D_804007A4[];
extern u8 D_804007CC[];
extern u8 D_80407298[];
extern u8 D_8040861C[];
extern u8 D_8040C318[];
extern u16 D_8040C336;
__asm__(".set D_8040C336, 0x8040C336");

extern s32 func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(s32 arg0, void *arg1);
extern s32 func_80047FD8(void *arg0);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_804075A8(s32 arg0);
extern s32 func_804075D0(void *arg0, s32 arg1);
extern u32 func_80407688(void *arg0, s32 arg1);
extern void func_8040777C(void *arg0);
extern void func_804077D4(void *arg0);


typedef struct S_800206C8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800206C8_0;   /* base_use in func_800206C8 */

typedef struct S_800206C8_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    s32 unk_60;
} S_800206C8_1;   /* sub in func_800206C8 */

typedef struct S_800206C8_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800206C8_2;   /* final_base in func_800206C8 */

/* Initializes the memory card slot object and its working state. */
void func_800206C8(s32 init_option)
{
    void *base;
    S_800206C8_0 *slot_obj;
    void *slot_state;
    void *allocated_obj;

    base = D_8040C318;
    slot_state = D_8040C318 + 0x20;
    if (func_80047FD8(base) == 0) {
        allocated_obj = (void *)(unsigned long)func_8003C714(0, base, 0x42);
        if (allocated_obj == 0) {
            func_8007C040(D_804007A4, D_804007CC, 0x136);
            func_8007BEF0(1);
        }
        func_80040560((s32)(unsigned long)allocated_obj, D_8040861C);
        func_8040777C(slot_state);
        return;
    }
    func_804077D4(base);
    D_8040C336 &= 0x7FFF;
    func_8007BFE0(slot_state, 0xE4);
    if (func_804075D0(slot_state, 4)) {
        slot_obj = base;
    } else {
        slot_obj = (u8 *)slot_state - 0x20;
    }
    slot_obj->unk_0C = (s32)(unsigned long)((u8 *)slot_state + 0x50);
    ((S_800206C8_1 *)slot_state)->unk_5C = func_804075A8(((S_800206C8_1 *)slot_state)->unk_60);
    func_80407688(slot_state, init_option);
    {
        register void *final_base ASM_REG("$2");

        final_base = slot_obj;
        ASM_KEEP(final_base);
        ((S_800206C8_2 *)final_base)->unk_10 =
            (s32)(unsigned long)D_80407298;
    }
}
