#include "common.h"
#include "shared/game_work.h"
#include "engine/camera.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 pad6[2];
} S_80174CF0;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 pad4[3];
} S_800DCE60;

extern S_80174CF0 D_80174CF0;
extern S_800DCE60 dungeon_camera_targets;

/* Initializes the destination state from the source and submits it for processing. */
void initialize_destination_state(void)
{
    S_80174CF0 *destinationState = &D_80174CF0;

    destinationState->unk4 = 0;
    g_game_work.view.slot[2].callback = 0;
    D_80174CF0.unk0 = dungeon_camera_targets.unk0;
    destinationState->unk2 = dungeon_camera_targets.unk2;
    queue_view_slot(1);
    set_camera_targets(0, destinationState, 10);
}
