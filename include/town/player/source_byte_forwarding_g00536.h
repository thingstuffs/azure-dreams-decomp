#ifndef TOWN_PLAYER_SOURCE_BYTE_FORWARDING_G00536_H
#define TOWN_PLAYER_SOURCE_BYTE_FORWARDING_G00536_H
/* G00536: shared declarations for source byte forwarding. */
/* Original-file evidence (G00536): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80097264, CL:town/func_80097300. */

#include "common.h"
#include "shared/town_handler.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

void set_sprite_animation_frame();
s32 view_relative_angle_sector();
extern u8 D_80080A84;

/* Functions defined in this translation unit. */
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination);
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, void *destination);

#endif
