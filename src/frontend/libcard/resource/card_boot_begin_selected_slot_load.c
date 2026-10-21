#include "common.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"

typedef struct TableEntry_800252CC {
    s32 value;
    u8 pad04[0x7C];
} TableEntry_800252CC;

extern u8 D_80024FAC[];
extern u8 D_800252A4[];
extern u8 D_8002593C[];
extern TableEntry_800252CC card_save_slot_metadata[];

#define FIELD32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define FIELDP(base, offset) (*(void **)((u8 *)(base) + (offset)))

/* Selects the parent handler and initializes state based on the indexed table value. */
void card_boot_begin_selected_slot_load(void *state)
{
    s32 enabled;
    void *parent;

    parent = (u8 *)state - 0x20;
    if (card_save_slot_metadata[FIELD32(state, 0x28)].value != 0) {
        enabled = 1;
        FIELD32(state, 0x3C) = enabled;
        card_boot_show_loading_progress(parent, (u8 *)state + 0x40);
        FIELD32(state, 0x40) = enabled;
        FIELDP(state, -0x10) = D_800252A4;
    } else {
        FIELDP(state, 0x34) = D_8002593C;
        card_boot_show_no_saved_game_notice(parent);
        FIELDP(state, -0x10) = D_80024FAC;
    }
}
