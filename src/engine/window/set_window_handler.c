#include "common.h"
#include "records/Rec_func_80036210_arg0.h"
#include "m2c_compat.h"

#include "common.h"
#include "slus/data.h"

/* Set the object's function pointer to func_80035AF8. */
void set_window_handler(Rec_func_80036210_arg0 *object) {
    object->unk_68 = &display_sound_selection_and_prepare_playback;
}
