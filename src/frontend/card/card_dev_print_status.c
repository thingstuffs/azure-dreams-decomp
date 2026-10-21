#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
void func_8003FA78(void *destination, s32 value);                /* extern */
s32 func_80408644();                         /* extern */

/* Passes four stored values and two queried values to func_8003FA78. */
void card_dev_print_status(void) {
    func_8003FA78(&D_80400090[0], *(s32 *)0x804094EC);
    func_8003FA78(&D_8040009C[0], *(s32 *)0x804094E8);
    func_8003FA78(&D_804000A4[0], *(s32 *)0x80409500);
    func_8003FA78(&D_804000B0[0], *(s32 *)0x80409504);
    func_8003FA78(&D_804000BC[0], func_80408644(0));
    func_8003FA78(&D_804000D0[0], func_80408644(1));
}
