#include "modules/town_town_windows.h"

/* Passes D_80100AF4 to process_object_pointer_array and returns zero. */
s32 pass_shared_data_to_window_handler(void) {
    process_object_pointer_array(D_80100AF4);
    return 0;
}
