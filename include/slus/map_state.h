#ifndef SLUS_MAP_STATE_H
#define SLUS_MAP_STATE_H

#include "engine/message.h"

struct MapRuntimeState;
typedef void (*MapChangeCallback)(struct MapRuntimeState *, void *);

struct TownRectangle;

/* Map transitions copy the entire pending record to the active one (0x30 bytes on PS1). */
typedef struct MapRuntimeState {
    void *loaded_descriptor;
    void *next_descriptor;
    u8 pad_08[4];
    u16 facing_angle;
    s16 alternate;
    struct TownRectangle *position;
    u16 x_offset;
    u16 y_offset;
    s16 scene_selector;
    s16 map_index;
    MessageServiceHandler *service_handlers;
    void **variable_addresses;
    MapChangeCallback callback;
    u16 previous_scene_selector;
    u16 previous_map_index;
    u8 pad_2C[4];
} MapRuntimeState;

extern MapRuntimeState map_runtime_state;
extern MapRuntimeState map_change_state;

#endif
