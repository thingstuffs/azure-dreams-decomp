#include "shared/town_event_state.h"
typedef unsigned char u8;
typedef int s32;

extern s32 D_80018014[];

/* Returns the table entry indexed by the fourth byte of D_8001E950. */
s32 get_event_table_value_by_state_index(void)
{
    return D_80018014[D_8001E950->unk_03];
}
