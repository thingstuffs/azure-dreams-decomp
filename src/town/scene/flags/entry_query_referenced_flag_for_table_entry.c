#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"
#include "town/player/script_flags.h"

s32 query_referenced_flag_for_table_entry(s32, s32); /* Unprototyped: retail call passes a different argument count */

/* Raise event 0x5BC and, when check 0x9A passes, forward the pair to the handler. */
s32 dispatch_entry_flag_query_if_ready(s32 target, s32 value) {
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
