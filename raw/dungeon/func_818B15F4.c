#include "common.h"

extern void func_800249B4(void);
extern void func_80024B34(void);
extern void func_80024C84(void);
extern void func_80024E54(void) __attribute__((noreturn));
extern void *D_80024008[];

typedef struct {
    u8 pad00[0xA];
    s16 state;
} Func818B15F4Arg;

s32 func_818B15F4(Func818B15F4Arg *arg0)
{
    static void *const keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&done,
        &&done, &&done, &&done, &&done
    };
    s32 state = *(s16 *)((u8 *)arg0 + 0xA);

    if (state >= 0 && state < 8) {
        s32 index = state << 2;
        void **table = D_80024008;
        ASM_KEEP(table);
        goto *(*(void **)(index + (u32)table));
    }
    (void)keepalive;
    goto done;

case_0:
        func_800249B4();
        func_80024E54();

case_1:
        func_80024B34();
        func_80024E54();

case_2:
        func_80024C84();

done:
    return 0;
}
