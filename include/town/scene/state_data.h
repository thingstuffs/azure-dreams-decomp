#ifndef TOWN_SCENE_STATE_DATA_H
#define TOWN_SCENE_STATE_DATA_H

#include "common.h"

/* Bank 4CF800 selects the argument to scene service 0x230 with this halfword. */
extern s16 scene_selection_index;

/* Eight-byte charge record in the current scene's event-data table. */
typedef struct TownSceneChargeEntry {
    s32 charge;
    u8 pad_04[2];
    u8 row_index;
    u8 pad_07;
} TownSceneChargeEntry;

/* Current row in the 0x18-byte scene table, assigned by both lookup and charge selection. */
extern s32 selected_scene_row_index;

/* Current scene update state at 0x80019BB0. */
extern s32 scene_update_state;

/* Four-byte context passed to town scene entry dispatchers. */
extern s32 scene_state_dispatch_context;

typedef struct TownSceneCopiedState {
    u8 pad0[0x20];
    s32 unk20;
    u16 unk24;
    u16 unk26;
} TownSceneCopiedState;

TownSceneCopiedState *copy_indexed_entry_to_state(s32 entry_index);

#endif
