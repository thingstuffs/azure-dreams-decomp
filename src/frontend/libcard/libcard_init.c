#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_init(s32 slot) {
    func_8007CB08(0); func_8007CA38(); InitCARD2_80408798(slot);
    func_804088A0(); func_80408958(); func_8007CA48();
}
