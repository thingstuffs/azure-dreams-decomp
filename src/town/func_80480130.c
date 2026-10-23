#include "common.h"
#include "town/scene/data_access.h"

extern u8 D_80019678;

u8 *get_scene_entry_bytes(void) {
    return &D_80019678;
}
