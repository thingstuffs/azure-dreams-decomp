#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

typedef struct TableEntry {
    s32 value;
    u8 pad[0x7C];
} TableEntry;

extern s32 func_80022138(void *arg0);
extern void func_80022FDC(void *arg0);
extern void func_8002311C(void *arg0);
extern void func_80025494(void *arg0);

extern u8 D_80024FAC[];
extern u8 D_80024FFC[];
extern TableEntry D_80083E98[];

void func_800254E4(void *arg0)
{
    u8 *base;
    s32 index;
    s32 result;

    base = arg0;
    index = FIELD(base, s32, 0x28);
    arg0 = base - 0x20;

    if (D_80083E98[index].value == 0) {
        result = func_80022138(arg0);
        arg0 = 0;
        arg0 = base - 0x20;
        if (result < 3) {
            FIELD(base, u8 *, 0x34) = D_80024FFC;
            func_80022FDC(arg0);
        } else {
            func_80025494(base);
            return;
        }
    } else {
        FIELD(base, u8 *, 0x34) = D_80024FFC;
        func_8002311C(arg0);
    }

    FIELD(base, u8 *, -0x10) = D_80024FAC;
}
