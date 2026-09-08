#include "common.h"

extern s32 func_80047FD8(void *arg0);
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007BEF0(s32 arg0);
extern void func_80040560(void *arg0, void *arg1);
extern void func_804058AC(void *arg0);
extern void func_804059A8(void *arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_804056F4(void *arg0, s32 arg1);
extern s32 func_804056CC(void *arg0);
extern void func_804057B0(void *arg0, s32 arg1);
extern u8 D_8040861C[];
extern u8 D_80400738[];
extern u8 D_80400760[];

typedef struct {
    u8 pad_00[0x1E];
    u16 flags;
} Root;

extern Root D_8040B4F8;

/* Initializes the memory card information object and its working state. */
void *func_8001E7F0(s32 init_option, s32 info_value) {
    void *base;
    void *card_state;

    base = &D_8040B4F8;
    card_state = (u8 *)base + 0x20;
    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0x387);
        if (base == 0) {
            func_8007C040(D_80400738, D_80400760, 0x1A0);
            func_8007BEF0(1);
        }
        func_80040560(base, D_8040861C);
        func_804058AC(card_state);
        return;
    }
    func_804059A8(base);
    D_8040B4F8.flags &= 0x7FFF;
    func_8007BFE0(card_state, 0xDFC);
    {
        register void *body ASM_REG("$17") = card_state;

        ASM_KEEP(body);
        *(s32 *)((u8 *)body + 0x7C) = info_value;
        func_804056F4(body, 0x15);
        ASM_KEEP(base);
        *(void **)((u8 *)base + 0xC) = (u8 *)body + 0xAF8;
        *(s32 *)((u8 *)body + 0xB04) = func_804056CC((u8 *)body + 0xB08);
        func_804057B0(body, init_option);
    }
    *(s32 *)((u8 *)base + 0x10) = 0;
    return base;
}
