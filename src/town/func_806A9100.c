#include "modules/town_ovl_629100.h"

void func_80016100(void) {
    Callback firstCallback;

    firstCallback = ((Callback)D_80016000->unk_20->callback_28C);
    D_800174D4[0] = D_80017420;
    firstCallback(1);
    ((Callback)D_80016000->unk_20->callback_290)(1);
}
