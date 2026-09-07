#include "common.h"

typedef s32 (*Callback)(s8 *);

extern void *D_80016000[];
extern s32 D_80017FB8[];

void func_80601228(void)
{
    s8 args[4];

    args[1] = 0x17;
    args[0] = 0x10;
    args[2] = 0;
    args[3] = 0;
    D_80017FB8[0] = ((Callback)*(void **)((s8 *)*(void **)((s8 *)D_80016000[0] + 0x20) + 0x50))(args);
}

/* MECHANISM: The four-byte args array yields the 0x20 frame with only $ra saved.
   The nested callback expression preserves the load chain and call-result store.
   gcc 2.7.2-cdk-G0 supplies retail's compiler-split hi/lo emission order. */
