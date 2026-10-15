#include "modules/town_town_windows.h"

/* Reset the object handler and restore its saved byte unless the check returns two. */
void func_8009DF84(void *object, void *context) {
    if (func_8009D20C(object, context) != 2) {
        func_80033CD8(object, func_80045340);
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_00 = &func_8009DEBC;
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_25 = (u8) ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_BC;
    }
}
