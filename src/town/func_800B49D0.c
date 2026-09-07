#include "common.h"

extern s32 func_800B2918(void);
extern s32 func_800B2154(void);

s32 func_800B2130(s32 arg0) {
    if (arg0 != 1) {
        return 0x14;
    }
    func_800B2918();
    return func_800B2154();
}
