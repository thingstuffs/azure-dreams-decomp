#include "common.h"

#include "common.h"
#include "slus/owned_80035484.h"
#include "slus/data.h"
void create_window_object(s32 object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config);   /* extern */

/* Passes the fixed runtime data pair and supplied value to create_window_object. */
void create_default_window_object(s32 value) {
    create_window_object(&default_window_node_storage, &default_window_model_storage, value);
}
