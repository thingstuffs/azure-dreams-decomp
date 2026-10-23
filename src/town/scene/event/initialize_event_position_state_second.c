#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef s32 (*Callback)(s32);


typedef struct S_800164E0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800164E0_1;

typedef struct S_800164E0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x10];
    s32 unk_18;
} S_800164E0_3;

typedef struct S_800164E0_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_800164E0_6;   /* (*(void * *)((u8 *)D_80016000 + 0)) in initialize_event_position_state */


/* Run two callbacks and initialize offset and saved coordinates from the current position. */
void initialize_event_position_state(void) {
    void *offset_x_state;
    TownPositionState *offset_y_state;
    void *saved_x_state;
    TownPositionState *saved_y_state;

    ((Callback)town_scene_root->services->callback_248)(0);
    offset_x_state = town_scene_root->position;
    ((S_800164E0_1 *)offset_x_state)->unk_10 = ((S_800164E0_1 *)offset_x_state)->unk_04 + 0x20;
    offset_y_state = town_scene_root->position;
    offset_y_state->unk_14 = offset_y_state->y;
    ((Callback)town_scene_root->services->callback_258)(0xD);
    saved_x_state = town_scene_root->position;
    ((S_800164E0_3 *)saved_x_state)->unk_18 = ((S_800164E0_3 *)saved_x_state)->unk_04;
    saved_y_state = town_scene_root->position;
    saved_y_state->unk_1C = saved_y_state->y;
}
