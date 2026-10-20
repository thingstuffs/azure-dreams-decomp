#include "modules/town_ovl_3fe0d0_p00.h"

void dispatch_town_callback_or_default(s32 value0, s32 value1)
{
    SceneCallType2 callback;

    callback = ((Runtime *)D_80016000)->callbacks[((Runtime *)D_80016000)->callbackIndex].callback;
    if (callback == 0) {
        initialize_context_entry_tables_variant_1(value0, value1);
    } else {
        callback();
    }
}
