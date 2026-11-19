#include "common.h"
#include "town/scene/state_data.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/data.h"

typedef s32 (*Callback)(void *);

/* Call the handler with the current kind and store its result in the current slot and global. */
void store_charge_for_selected_row(void) {
    u8 request[2];
    TownSceneChargeEntry *slot;
    s32 handler_result;
    u8 kind;

    slot = (TownSceneChargeEntry *)town_scene_root->event_data + town_scene_root->entry_index;
    kind = *(u8 *)&selected_scene_row_index;
    request[1] = 0x19;
    request[0] = kind;
    slot->row_index = kind;
    handler_result = ((Callback)(town_scene_root->services->callback_050))(request);
    scene_charge = handler_result;
    slot->charge = handler_result;
}

/* MECHANISM
 * - GLOBAL DECL FORM: D_80016000 as `extern s8 D_80016000[]` deref'd twice as
 *   *(s8**)D_80016000 gives retail's single held `lui $a1,0x8001` + two
 *   `lw 0x6000($a1)`; the intervening `sb 6($s0)` store kills the CSE, which
 *   is exactly why retail reloads. The handler receives the low byte of the selected row; its explicit
 *   byte read preserves the retail lbu.
 * - STATEMENT ORDER IS THE LEVER: computing `slot` BEFORE `kind = D_80019B8C`
 *   puts %hi(D_80016000) in $a1 ahead of %hi(D_80019B8C) and lets gcc color the
 *   D_80019B8C hi-base and the lbu destination onto the same $a0 (retail words
 *   0/1/3). The reverse order costs a third lui register ($v1) and swaps them.
 * - FRAME: two sibling u8 stack bytes as a u8[2] passed by address gives the
 *   0x20 frame (16 arg + 8 local + ra/s0) and `addiu $a0,$sp,0x10` in the jalr
 *   delay slot; a wrapper struct would not.
 */
