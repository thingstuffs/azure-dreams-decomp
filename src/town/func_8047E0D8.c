#include "modules/town_ovl_3fe0d0_p00.h"

void dispatchTownCallbackOrDefault(s32 value0, s32 value1)
{
    SceneCallType2 callback;

    callback = ((Runtime *)D_80016000)->callbacks[((Runtime *)D_80016000)->callbackIndex].callback;
    if (callback == 0) {
        func_80016130(value0, value1);
    } else {
        callback();
    }
}
