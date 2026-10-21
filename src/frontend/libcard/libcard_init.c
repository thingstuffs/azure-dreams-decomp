#include "common.h"
#include "frontend/libcard.h"

extern void func_8007CB08(s32);
extern void func_8007CA38(void);
extern void func_80408798(s32);
extern void func_804088A0(void);
extern void func_80408958(void);
extern void func_8007CA48(void);
void libcard_init(s32 slot) {
    func_8007CB08(0); func_8007CA38(); func_80408798(slot);
    func_804088A0(); func_80408958(); func_8007CA48();
}
