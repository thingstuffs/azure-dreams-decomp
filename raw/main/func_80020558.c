#include "common.h"

void func_80407160(s32 arg0);
void func_804072CC(s32 arg0, void *arg1, void *arg2);
void func_80407458(void);
void func_804074C4(s32 arg0);


extern u8 D_80408D54[];
extern u8 D_80408D5C[];

void func_80020558(s32 arg0) {
    func_80407458();
    func_804074C4(arg0);
    func_804072CC(arg0, D_80408D54, D_80408D5C);
    func_80407160(arg0);
}
