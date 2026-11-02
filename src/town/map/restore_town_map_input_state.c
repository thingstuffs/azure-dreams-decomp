#include "town/map/body.h"
#include "common.h"
#include "town/map.h"
extern u8 D_8008BA00[];
extern u8 D_8008BC58[];

extern u8 town_map_status;

/* Select and store an address based on the global byte value. */
void restore_town_map_input_state(TownMapBody *object) {
    u8 value = town_map_status;

    if (value == 0xFF) {
        object->update = D_8008BA00;
    } else if (value == 0) {
        object->update = D_8008BC58;
    }
}
