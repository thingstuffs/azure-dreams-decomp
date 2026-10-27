#include "script_symbols.h"
#include "shared/town_root.h"
#include "shared/town_state.h"
#include "common.h"
#include "shared/record_ptrs.h"


extern void (*D_80017618)(void);
extern s16 town_event_counter;

extern void func_800173F8(); /* Unprototyped: one or two arguments; the second register argument is ignored. */
extern void clear_thirty_six_table_fields(void);

/* Installs the town callback, enforces a minimum town value of 40, and runs the setup sequence. */
void initialize_town_counter_and_callback(void)
{
    s32 current_town_value;
    TownStateRecord *town = ((Rec_D_80016000 *)(*(void **)((u8 *)(&town_scene_root))))->town_state;

    current_town_value = town->unk_35BE;
    D_80017618 = clear_thirty_six_table_fields;
    if (current_town_value < 40) {
        town->unk_35BE = 40;
    }
    func_800173F8(F_sbs42_pad11);
    func_800173F8(F_sbs42_pad12);
    town_event_counter = 0;
    func_800173F8(F_sbs42_pad14);
}
