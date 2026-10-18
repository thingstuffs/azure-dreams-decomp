#include "common.h"

#include "common.h"

void func_80034F9C(s8 *result_flag);
extern u8 D_80082A38[];

/* Passes the global object D_80082A38 to func_80034F9C. */
void func_800352B4(void) {
    func_80034F9C(&D_80082A38);
}
