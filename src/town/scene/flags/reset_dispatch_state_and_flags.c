#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"

extern void func_8001E5F0(s32 event_flag_id);

/* Clear two state bytes and process five fixed identifiers. */
void reset_dispatch_state_and_flags(void) {
    town_event_state->dispatchState = 0;
    town_event_state->unk_06 = 0;
    func_8001E5F0(F_sbs01_pad11);
    func_8001E5F0(F_sbs01_pad12);
    func_8001E5F0(F_sbs01_pad13);
    func_8001E5F0(Ft_home01_rees_once);
    func_8001E5F0(F_tw_rain_del);
}
