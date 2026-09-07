#include "common.h"

extern void func_8003AD08(s32 arg0, void *arg1);
extern void strcat(s32 arg0, s32 arg1);
extern void strcpy(s32 arg0, s32 arg1);

extern s16 D_80010208;
extern s32 D_80028294[];
extern s32 D_800282A0;

void func_80025F0C(s32 arg0, s32 arg1) {
    s32 sp10[4];
    s32 *settings;
    s32 temp_s0;
    s32 call_context;
    s32 saved_arg1;
    s32 selected;
    s32 final_value;

    saved_arg1 = arg1;
    temp_s0 = arg0 + 4;
    settings = D_80028294;
    strcpy(temp_s0, settings[0]);
    func_8003AD08(saved_arg1 + 1, sp10);
    strcat(temp_s0, (s32)sp10);
    strcat(temp_s0, settings[3]);
    strcat(temp_s0, 0x8001020C);
    strcat(temp_s0, settings[3]);

    call_context = temp_s0;
    if (D_80010208 != 0) {
        selected = settings[1];
    } else {
        selected = settings[2];
    }
    ASM_KEEP(saved_arg1);
    strcat(call_context, selected);

    temp_s0 = arg0 + 4;
    strcat(temp_s0, D_800282A0);
    final_value = *(s32 *)0x8001022C;
    func_8003AD08(final_value, sp10);
    strcat(temp_s0, (s32)sp10);
}
