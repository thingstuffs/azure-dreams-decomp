#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"






/* Builds a string from the selected prefix, a separator, and an indexed suffix. */
void card_boot_build_slot_path(s32 dest, s32 suffix_index) {
    s32 *prefix_ptr;

    prefix_ptr = &(*(u8 *)(&D_80027F18));
    if ((*(s32 *)(&D_800287CC)) != 0) {
        prefix_ptr = &(*(u8 *)(&D_80027F18)) + 4;
    }
    strcpy(dest, *prefix_ptr);
    strcat(dest, &(*(M2C_UNK *)(&D_80027F20)));
    strcat(dest, ((s32 *) &(*(M2C_UNK *)(&D_80027F30)))[suffix_index]);
}
