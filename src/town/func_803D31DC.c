/* Relink of matched town/func_8032FDE4; every changed retail word is a paired relocation. */
#define townPrepareSharedTextBuffer func_8001A1DC
#define D_80016108 D_80016124
#define D_8001C380 D_8001B330
#include "common.h"
extern u8 D_8001B330[];

extern void * func_80018878(void *, void *);
extern void * func_800188B4(void *, void *);
extern u8 D_80016124[];

/* Prepare and return the shared text buffer using the source and D_80016124. */
void *func_8001A1DC(s32 source)
{
    u32 call_arg;

    call_arg = source;
    func_80018878(D_8001B330, call_arg);
    func_800188B4(D_8001B330, D_80016124);
    return D_8001B330;
}
