#include "common.h"
#include "frontend/libcard.h"

extern void func_804087B8(void);
extern void func_80408958(void);
extern void func_804087C8(void);
void libcard_stop(void) {
    func_804087B8();
    func_80408958();
    func_804087C8();
}
