#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_8050E100_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8050E100_0;   /* *(void **)D_80016000 in func_8050E100 */

typedef struct S_8050E100_1 {
    u8 pad_00[0x35BE];
    s16 unk_35BE;
} S_8050E100_1;   /* town in func_8050E100 */

extern void (*D_80017618)(void);
extern s16 town_event_counter;

extern void func_800173F8();
extern void clear_thirty_six_table_fields(void);

/* Installs the town callback, enforces a minimum town value of 40, and runs the setup sequence. */
void initialize_town_counter_and_callback(void)
{
    s32 current_town_value;
    S_8050E100_1 *town = ((S_8050E100_0 *)(*(void **)((u8 *)(&D_80016000))))->unk_38;

    current_town_value = town->unk_35BE;
    D_80017618 = clear_thirty_six_table_fields;
    if (current_town_value < 40) {
        town->unk_35BE = 40;
    }
    func_800173F8(F_sbs42_pad11, town);
    func_800173F8(F_sbs42_pad12);
    town_event_counter = 0;
    func_800173F8(F_sbs42_pad14);
}
