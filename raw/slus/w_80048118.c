#include "common.h"

extern void func_800481E0(void);
extern void func_80047C00(void);
extern void *func_80047CD8(s16 a0);
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);
extern int func_800499DC(int *a0);

/* Given a packed value whose low 16 bits are a signed entity/state code (a0)
 * and an output buffer (a1): if the code is 0x38, runs the status-refresh
 * pass func_800481E0 then the cleanup pass func_80047C00. Then looks up/
 * allocates the slot for the code via func_80047CD8; if found/allocated,
 * zeroes *a1 and registers a callback (func_800499DC) with arg a1 via
 * func_8003E4FC. Returns the func_80047CD8 result (NULL if not found). */
void *func_80048118(s32 a0, s32 *a1)
{
    s16 code = (s16)a0;
    void *p;

    if (code == 0x38) {
        func_800481E0();
        func_80047C00();
    }
    p = func_80047CD8(code);
    if (p != 0) {
        *a1 = 0;
        func_8003E4FC(0xFF, (void *)func_800499DC, a1);
    }
    return p;
}
