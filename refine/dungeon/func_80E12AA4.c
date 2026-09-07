#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(s32, s32);
extern void func_800A5720(s32);
extern void func_801762FC(void) __attribute__((noreturn));

extern u8 D_800E1F65[9];
extern u8 D_800E1FB9[9];

/* Format an entity message or dispatch its alternate message. */
void func_80E12AA4(s32 alternate_message, s32 entity)
{
    s32 text_ctx;
    register void *dispatch_arg ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    text_ctx = func_800990FC();
    if (alternate_message << 16) {
        func_80099734(entity, text_ctx);
        dispatch_arg = D_800E1FB9;
        ASM_TAILSLOT_PIN(dispatch_arg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_801762FC();
        return;
    }
    func_80099290(func_80099194(D_800E1F65,
                                func_80099734(entity, text_ctx)));
    func_800A5720(text_ctx);
}
