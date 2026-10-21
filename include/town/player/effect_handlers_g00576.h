#ifndef TOWN_PLAYER_EFFECT_HANDLERS_G00576_H
#define TOWN_PLAYER_EFFECT_HANDLERS_G00576_H
/* Initialize player effect handlers from prior state (G00576). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A7DDC. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"
#include "shared/entity.h"

typedef struct S_800A553C_0 {
    s32 * unk_00;
    u8 pad_04[0xC];
    s32 * unk_10;
} S_800A553C_0;

/* arg0 in initialize_effect_record_handlers; pointer addresses record offset 0x10 */
void unlink_node_if_registered(void *block_data);
/* extern */
extern u8 D_800A5638[];
void update_town_movement_and_actions(u8 *state, EntityRec *table, void *action_context);
extern s32 D_800D0460;
extern M2C_UNK D_800D0C50;
extern s32 D_800834B8;

/* Functions defined in this translation unit. */
void initialize_effect_record_handlers(void *record_data, s32 unused, s32 destination);
void update_target_from_previous_state(void);

#endif
