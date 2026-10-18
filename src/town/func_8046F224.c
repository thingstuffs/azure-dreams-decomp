#include "modules/town_ovl_3ef1c8.h"

s32 lookup_variant_with_special_overrides(s32 requiredFlag, s32 completionFlag) {
    if (func_8001A510(requiredFlag) == 0) {
        return 1;
    }
    if (func_8001A510(0x7A3) != 0) {
        return 1;
    }
    func_8001A418(0x7A3);
    func_8001A418(completionFlag);
    func_8001A490(requiredFlag);
    return 0;
}
