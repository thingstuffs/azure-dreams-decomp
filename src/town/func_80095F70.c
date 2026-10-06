#include "common.h"

extern s32 D_800834B8;
extern void func_8009368C(void *record, s32 first_value, s32 second_value);

/* Run plt_carry_on_chk_ext using the global record and its context values. */
void plt_carry_on_chk_ext(void) {
    s32 *record = &D_800834B8;
    s32 *context = record - 8;


    func_8009368C(record, context[2], context[3]);
}
