#include "common.h"

extern s32 func_800990FC(s32, void *, s32, s32);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80099290(s32 arg0);
extern s32 func_80099368(void *arg0, s32 arg1);
extern s32 func_80099734(s32 arg0, s32 arg1);
extern s32 func_800999B0(s32 arg0);
extern void func_800A5720(s32 arg0);
extern u8 D_80089000[];
extern u8 D_800E0A1B[];

/* Builds and processes a message containing the item and actor names. */
void func_800A6480(s32 actor, void *item, s32 buffer_arg2, s32 buffer_arg3) {
    register void *format_item ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 text_out ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 message ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 text_buffer;

    text_buffer = func_800990FC(actor, item, buffer_arg2, buffer_arg3);
    format_item = item;
    text_out = text_buffer;
    message = text_out;
    func_80099290(func_800999B0(func_80099194(D_80089000,
        func_80099734(actor, func_80099194(D_800E0A1B,
            func_80099368(format_item, text_out))))));
    func_800A5720(message);
}
