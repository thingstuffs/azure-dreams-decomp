#include "script_symbols.h"
#include "common.h"

extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 D_80019178[];

/* Apply the fixed operation codes and clear the first D_80019178 entry. */
void run_events_5a5_5c2_and_reset(void) {
    func_80018A64(F_sbs11_pad02);
    func_80018ADC(F_sbs11_pad31);
    func_80018ADC(F_sbs11_pad28);
    func_80018ADC(F_sbs11_pad29);
    D_80019178[0] = 0;
}
