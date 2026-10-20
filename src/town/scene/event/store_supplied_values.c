#include "script_symbols.h"
#include "common.h"

void store_supplied_values();                /* extern */
void func_80017EB0(s32, s32);                /* extern */
void func_800188CC(s32);                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;

/* Conditionally processes 0x50C, then forwards the inputs to both shared routines. */
void func_804B7BD0(s32 forwardedValue, s32 forwardedData) {
    if (func_8001894C(F_sbs07_pad21) != 0) {
        if (func_8001894C(D_80018AEA) == 0) {
            func_800188CC(F_sbs07_pad21);
        }
    }
    store_supplied_values(forwardedValue, forwardedData);
    func_80017EB0(forwardedValue, forwardedData);
}
