#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s8 pad00[0x10];
    void (*unk10)(void);
    s8 pad14[0x0C];
    s32 unk20;
    s8 pad24[0x14];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s8 pad4C[0x1C];
    s32 unk68;
} StructA_8001F678;

extern StructA_8001F678 *func_8003C714(s32 arg0, s32 arg1, s32 arg2);
extern void func_80406570(void *arg0, s32 arg1);
extern void func_804023C4(void);
extern void func_80402214(void);
extern s32 func_80404C84(StructA_8001F678 *arg0, s32 *arg1);
extern s32 func_80403BC4(StructA_8001F678 *arg0);
extern s32 func_804057F0(StructA_8001F678 *arg0, s32 arg1);
extern void func_804065CC(void);
extern u8 D_8040C628[0x1C];

/* Creates and initializes state and installs its update callback. */
StructA_8001F678 *func_8001F678(s32 init_value) {
    StructA_8001F678 *state;

    state = func_8003C714(0, D_8040C628, 0x1C);
    func_80406570((void *) ((s32) state + 0x20), init_value);
    func_804023C4();
    func_80402214();
    state->unk68 = 1;
    state->unk20 = func_80404C84(state, &state->unk68);
    state->unk38 = func_80403BC4(state);
    state->unk3C = func_804057F0(state, state->unk48);
    state->unk44 = 0;
    state->unk10 = func_804065CC;
    return state;
}
