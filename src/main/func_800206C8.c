#include "common.h"


extern u8 D_804007A4[];
extern u8 D_804007CC[];
extern u8 D_80407298[];
extern u8 D_8040861C[];
extern u8 D_8040C318[];
extern u16 D_8040C336;

extern s32 func_8003C714(s32 option, void *object, s32 param);
extern void func_80040560(s32 object, void *data);
extern s32 func_80047FD8(void *object);
extern void func_8007BEF0(s32 value);
extern void func_8007BFE0(void *object, s32 value);
extern void func_8007C040(void *first_ptr, void *second_ptr, s32 value);
extern s32 func_804075A8(s32 context);
extern s32 func_804075D0(void *object, s32 value);
extern u32 func_80407688(void *object, s32 option);
extern void func_804077D4(void *card_slot);


typedef struct S_800206C8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800206C8_0;   /* base in func_800206C8 */

typedef struct S_800206C8_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    s32 unk_60;
} S_800206C8_1;   /* slot_state in func_800206C8 */

/* Initializes the memory card slot object and its working state. */
void *func_804076C8(s32 init_option)
{
    void *base;
    void *slot_state;

    base = D_8040C318;
    slot_state = D_8040C318 + 0x20;
    if (func_80047FD8(base) == 0) {
        base = (void *)(unsigned long)func_8003C714(0, base, 0x42);
        if (base == 0) {
            func_8007C040(D_804007A4, D_804007CC, 0x136);
            func_8007BEF0(1);
        }
        func_80040560((s32)(unsigned long)base, D_8040861C);
    } else {
        func_804077D4(base);
        D_8040C336 &= 0x7FFF;
        func_8007BFE0(slot_state, 0xE4);
    }
    func_804075D0(slot_state, 4);
    ((S_800206C8_0 *)base)->unk_0C = (s32)(unsigned long)((u8 *)slot_state + 0x50);
    ((S_800206C8_1 *)slot_state)->unk_5C = func_804075A8(((S_800206C8_1 *)slot_state)->unk_60);
    func_80407688(slot_state, init_option);
    ((S_800206C8_0 *)base)->unk_10 = (s32)(unsigned long)D_80407298;
    return base;
}
