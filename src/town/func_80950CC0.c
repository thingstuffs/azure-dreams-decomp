#include "common.h"

extern u8 D_80016034[16];
extern u8 *D_80016D08[3];

/* Initialize the first data pointer to D_80016034. */
void set_first_data_slot_pointer(void) {
    D_80016D08[0] = D_80016034;
}
