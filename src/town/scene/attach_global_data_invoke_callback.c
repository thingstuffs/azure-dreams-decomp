#include "common.h"
typedef struct { u8 pad[0x40]; void *value; } Child;
typedef struct { u8 pad[0x1C]; Child *child; } State;
extern State *town_scene_root;
extern void *D_800174E0;
extern u8 D_80016084[], scene_event_data[];
void attach_global_data_and_invoke_callback(void) {
    D_800174E0 = D_80016084;
    town_scene_root->child->value = scene_event_data;
}
