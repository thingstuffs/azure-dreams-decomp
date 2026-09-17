#include "common.h"

struct S_818B11B4_0;
struct S_818B11B4_2;
struct S_818B1334_1;
struct S_818B1334_3;
struct S_818B1484_1;
struct S_818B1484_3;
extern s32 func_800249B4(struct S_818B11B4_0 *, struct S_818B11B4_2 *, void *);
extern s32 func_80024B34(struct S_818B1334_1 *, struct S_818B1334_3 *, void *);
extern s32 func_80024C84(struct S_818B1484_1 *, struct S_818B1484_3 *, void *);

typedef struct {
    u8 pad00[0xA];
    s16 state;
} Func818B15F4Arg;

s32 func_80024DF4(void *arg0, void *arg1, void *arg2)
{
    switch (((Func818B15F4Arg *)arg0)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    default:
        break;
    case 4:
        func_800249B4(arg0, arg1, arg2);
        break;
    case 5:
        func_80024B34(arg0, arg1, arg2);
        break;
    case 6:
        func_80024C84(arg0, arg1, arg2);
        break;
    }
    return 0;
}
