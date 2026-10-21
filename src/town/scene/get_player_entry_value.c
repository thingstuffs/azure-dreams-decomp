#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"

typedef struct {
    u8 pad[8];
    s32 value;
} TownRecord;

extern TownRecord town_selection_records[];
extern s32 D_80018054[];
extern void func_8001E578(s32);

/* Return the player's table value, calling func_8001E578 if its town record value is zero. */
s32 get_player_entry_value(void) {
    u8 **player_ptr = ((u8 **)&town_event_state);
    u8 *player = *player_ptr;
    u8 player_index = player[4];

    if (town_selection_records[player_index].value == 0) {
        func_8001E578(F_sbs01_pad12);
    }

    {
        u8 *updated_player = *player_ptr;
        u8 updated_index = updated_player[4];

        return D_80018054[updated_index];
    }
}
