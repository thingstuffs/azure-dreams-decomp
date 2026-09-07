#include "common.h"

/* Scans D_80083120's 8 slots from the end (index 7) backward, looking for the
   first slot with field_0 == 0 (free). On finding one, fills it with
   {field_0=a0, field_2=0, field_4=a1, field_6=0} and returns its index.
   Returns -1 if every slot is occupied. */
typedef struct S_80083120 {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
} S_80083120;

extern S_80083120 D_80083120[8];

s16 func_8003F794(s16 a0, s16 a1)
{
    s32 i;
    u32 start;
    S_80083120 *p;

    i = 7;
    start = 7;
    p = &D_80083120[start];
loop:
    if (p->field_0 == 0)
        goto found;
    i--;
    p--;
    if (i >= 0)
        goto loop;
    return -1;
found:
    p->field_0 = a0;
    p->field_2 = 0;
    p->field_4 = a1;
    p->field_6 = 0;
    return i;
}
