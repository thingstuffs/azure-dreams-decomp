#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


typedef struct S_80019DE0_0 {
    u16 unk_00;
    u16 unk_02;
} S_80019DE0_0;   /* arg0 in apply_half_step_position_deltas */


/* Calls the active callback and adds signed half-deltas, rounded toward zero, to two target fields. */
void apply_half_step_position_deltas(S_80019DE0_0 *deltas) {
    u16 first_delta;
    u16 second_delta;
    u32 shifted_delta;
    TownPositionState *first_target;
    TownPositionState *second_target;

    ((s32 (*) (s32))town_scene_root->services->callback_258)(1);
    first_delta = deltas->unk_00;
    first_target = town_scene_root->position;
    shifted_delta = (u32) first_delta << 0x10;
    first_target->x = (s32) (first_target->x + ((s32) (((s32) shifted_delta >> 0x10) + (shifted_delta
        >> 0x1F)) >> 1));
    second_delta = deltas->unk_02;
    second_target = town_scene_root->position;
    shifted_delta = (u32) second_delta << 0x10;
    second_target->y = (s32) (second_target->y + ((s32) (((s32) shifted_delta >> 0x10) + (shifted_delta
        >> 0x1F)) >> 1));
}
