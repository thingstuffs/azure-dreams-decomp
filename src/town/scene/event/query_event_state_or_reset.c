#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 Callback(s32);

extern s32 func_8001E670(s32 id);
extern void reset_dispatch_state_and_flags(void);

extern s32 D_80018448[];

/* Town state query: when flag 0x1391 is clear or flag 0xA2 is set, return the table entry the object's 0x2D4 callback picks; otherwise run the fallback and bump its counter. */
s32 query_event_state_or_reset(void)
{
    s32 index;

    if ((func_8001E670(F_veld_kill) == 0) ||
        (func_8001E670(F_end_ending) != 0)) {
        index = (*(Callback **)((u8 *)*(void **)((u8 *)D_80016000 + 0x20) + 0x2D4))(0);
        return D_80018448[index];
    }

    reset_dispatch_state_and_flags();
    D_8001E950->unk_00++;
    return 0;
}

/* MECHANISM: The natural callback/table-return CFG preserves the retail
   24-byte frame with only $ra saved.  The callback field is a stored function
   pointer (Callback **), forcing retail's lw/load-delay/jalr sequence. */
