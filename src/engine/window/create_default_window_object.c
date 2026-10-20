#include "common.h"

#include "common.h"
#include "slus/owned_80035484.h"
void create_window_object(s32 object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config);   /* extern */
extern u8 D_80081EB0[];
extern u8 D_800820A8[];

/* Passes the fixed runtime data pair and supplied value to create_window_object. */
void create_default_window_object(s32 value) {
    create_window_object(&D_800820A8, &D_80081EB0, value);
}
