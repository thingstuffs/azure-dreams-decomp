#include "common.h"

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern u8 D_800D517C[];
extern u8 D_800D5184[];
extern u8 D_800D51AC[];
extern u8 D_800D51B0[];

/* Configure the actor with type 0x30 and its data tables. */
void func_800C5368(void *actor) {
    func_800C3050(actor, 0x30, D_800D51AC, D_800D51B0, D_800D517C, D_800D5184);
}
