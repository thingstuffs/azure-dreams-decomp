#ifndef TOWN_SHOP_SLOT_RESOURCE_UPDATES_G00621_H
#define TOWN_SHOP_SLOT_RESOURCE_UPDATES_G00621_H
/* Update slot countdowns, choices, and resource colors (G00621): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B6384, CL:town/func_800B63B8, CL:town/func_800B64A4. */

#include "common.h"
#include "shared/game_work.h"

typedef struct TownState {
    u8 pad0[8];
    s32 enabled;
    u8 padC[4];
    s32 flags;
} TownState;

/* extern */
typedef struct S_800B3C74_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B3C74_0;

typedef struct S_800B3C74_1 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B3C74_1;

typedef struct S_800B3C74_2 {
    u8 pad_00[0x4];
    u8 * unk_04;
} S_800B3C74_2;

extern int abs(int);

/* Functions defined in this translation unit. */
void move_color_channels_toward_neutral(u8 *channels);
s32 select_choice_from_input_flags(s32 *choice_values);
void process_resources_for_expired_slot_countdowns(void *state);

#endif
