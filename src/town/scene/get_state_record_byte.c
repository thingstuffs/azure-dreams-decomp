#include "common.h"
#include "town/scene.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* This byte has no identified member in the shared town-state view. */
typedef struct TownStateByteView {
    u8 pad_0000[0x33BA];
    u8 state_byte;
} TownStateByteView;

s32 get_state_record_byte(void) {
    return ((TownStateByteView *)town_scene_root->town_state)->state_byte;
}
