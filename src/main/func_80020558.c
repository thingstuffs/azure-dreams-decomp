#include "common.h"

void func_80407160(s32 arg0);
void func_804072CC(s32 arg0, void *arg1, void *arg2);
void func_80407458(s32);
void func_804074C4(s32 arg0);


extern u8 D_80408D54[];
extern u8 D_80408D5C[];

/* Run the slot setup sequence with the two shared data tables. */
void func_80020558(s32 slot_addr) {
    func_80407458(slot_addr);
    func_804074C4(slot_addr);
    func_804072CC(slot_addr, D_80408D54, D_80408D5C);
    func_80407160(slot_addr);
}
