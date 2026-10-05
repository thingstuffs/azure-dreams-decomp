#include "common.h"

struct S_818B11B4_0;
struct S_818B11B4_2;
struct S_818B1334_1;
struct S_818B1334_3;
struct S_818B1484_1;
struct S_818B1484_3;
extern s32 func_800249B4(struct S_818B11B4_0 *);
extern s32 func_80024B34(struct S_818B1334_1 *, struct S_818B1334_3 *, void *);
extern s32 func_80024C84(struct S_818B1484_1 *, struct S_818B1484_3 *, void *);

typedef struct {
    u8 pad00[0xA];
    s16 state;
} Func818B15F4Arg;

s32 func_80024DF4(void *state_ptr, void *second_ptr, void *third_ptr)
{
    switch (((Func818B15F4Arg *)state_ptr)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    default:
        break;
    case 4:
        func_800249B4(state_ptr);
        break;
    case 5:
        func_80024B34(state_ptr, second_ptr, third_ptr);
        break;
    case 6:
        func_80024C84(state_ptr, second_ptr, third_ptr);
        break;
    }
    return 0;
}
