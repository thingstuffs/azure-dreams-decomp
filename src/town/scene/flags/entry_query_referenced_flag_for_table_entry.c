#include "script_symbols.h"
#include "common.h"

void query_referenced_flag_for_table_entry(s32, s32);
void func_80018ADC(s32);
s32 func_80018B5C();

/* Raise event 0x5BC and, when check 0x9A passes, forward the pair to the handler. */
s32 func_8051EDA4(s32 target, s32 value) {
    s32 result;

    func_80018ADC(F_sbs11_pad25);
    if (func_80018B5C(F_viv_engei_ok) == 0) {
        result = 0;
    } else {
        query_referenced_flag_for_table_entry(target, value);
        result = 1;
    }

    return result;
}
