#include "common.h"

extern void func_8007CB08(s32 arg0);
extern void func_8007CA38(void);
extern void func_80408798(void *arg0);
extern void func_804088A0(void);
extern void func_80408958(void);
extern void func_8007CA48(void);

/* Run the setup sequence using the supplied context. */
void func_802F16DC(void *context) {
    func_8007CB08(0);
    func_8007CA38();
    func_80408798(context);
    func_804088A0();
    func_80408958();
    func_8007CA48();
}
