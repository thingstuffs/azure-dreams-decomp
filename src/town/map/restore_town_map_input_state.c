#include "common.h"
extern u8 D_8008BA00[];
extern u8 D_8008BC58[];

extern u8 town_map_status;

/* Select and store an address based on the global byte value. */
void restore_town_map_input_state(void *object) {
    u8 value = town_map_status;

    if (value == 0xFF) {
        *(void **)((u8 *)object + 0x68) = D_8008BA00;
    } else if (value == 0) {
        *(void **)((u8 *)object + 0x68) = D_8008BC58;
    }
}
