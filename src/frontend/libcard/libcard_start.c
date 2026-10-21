#include "common.h"
#include "frontend/libcard.h"

extern void func_8007CA38(void);
extern void func_804087A8(void);
extern void func_8007CB08(s32);
extern void func_8007CA48(void);
void libcard_start(void) {
    func_8007CA38();
    func_804087A8();
    func_8007CB08(0);
    func_8007CA48();
}
