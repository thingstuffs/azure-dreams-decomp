#include "common.h"

/* extern decls for callees; sizes/types from asm inspection */
extern void func_8005CA70(void);
extern void func_80056C30(void);
extern void func_8005A26C(void);
extern void func_8005D838(int arg0, void *arg1);

typedef struct {
    int unk0;
    int unk4;
    int unk8; /* padding beyond 8 bytes to force %hi/%lo addressing (not gp-relative) */
} S_80086CC0;

extern S_80086CC0 D_80086CC0;

/* Runs initialization and update routines, then reinitializes D_80086CC0. */
void func_8005A2FC(void)
{
    func_8005CA70();
    func_80056C30();
    func_8005A26C();
    func_8005D838(0x10, &D_80086CC0);
}
