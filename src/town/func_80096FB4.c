/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"

s32 SD_Call();                     
void call_the_handler_selects_nonzero_entry(); 
void store_the_valid_shared_angle_in_offset_hex_10();                  
extern s32 D_80093250;

void func_80094714(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x512);
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D00B8, record, setup_value);
    *record = &D_80093250;
}
