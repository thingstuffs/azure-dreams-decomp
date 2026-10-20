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

extern StructA_8001F678 *func_8003C714(s32 value, s32 value2, s32 value3);
extern void func_80406570(void *ptr, s32 value);
extern void run_slot_operation_code_five(void);
extern void func_80402214(void);
extern s32 init_card_background_object(StructA_8001F678 *state, s32 *value_ptr);
extern s32 init_card_options_object(StructA_8001F678 *state);
extern s32 init_card_info_object(StructA_8001F678 *state, s32 value);
extern void card_devkit_build_save_slot_windows(void);
extern u8 D_8040C628[0x1C];

/* Creates and initializes state and installs its update callback. */
StructA_8001F678 *card_dev_create_save_screen(s32 init_value) {
    StructA_8001F678 *state;

    state = func_8003C714(0, D_8040C628, 0x1C);
    func_80406570((void *) ((s32) state + 0x20), init_value);
    run_slot_operation_code_five();
    func_80402214();
    state->unk68 = 1;
    state->unk20 = init_card_background_object(state, &state->unk68);
    state->unk38 = init_card_options_object(state);
    state->unk3C = init_card_info_object(state, state->unk48);
    state->unk44 = 0;
    state->unk10 = card_devkit_build_save_slot_windows;
    return state;
}
