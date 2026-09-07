#include "common.h"

/* Builds four "list pointer" fields in D_80083160's sub-record at +0x1DC (f4/f8/fC/f10) from word-offsets in D_8006E7F0[arg1], and relocates the first list in place by adding arg0 to each of its count entries. */
/* D_8006E7F0: array of pointers to per-type info records; each record has a
 * u16 count at +0x6 and four u16 word-offsets at +0x8/+0xA/+0xC/+0xE. */
typedef struct S_80046D64_Info {
    u8 pad0[6];
    u16 count; /* 0x6 */
    u16 off8;  /* 0x8 */
    u16 offA;  /* 0xA */
    u16 offC;  /* 0xC */
    u16 offE;  /* 0xE */
} S_80046D64_Info;

extern S_80046D64_Info *D_8006E7F0[];

/* D_80083160: shared state table (own view here); this function only touches
 * a small sub-record living at +0x1DC (five s32 fields; f0 is untouched by
 * this function, f4/f8/fC/f10 are written). */
typedef struct S_80046D64_Dst {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} S_80046D64_Dst;

typedef struct S_80083160_View {
    u8 pad0[0x1DC];
    S_80046D64_Dst sub;
} S_80083160_View;

extern S_80083160_View D_80083160;

void func_80046D64(s32 arg0, s16 arg1)
{
    S_80083160_View *base = &D_80083160;
    S_80046D64_Dst *dst = &base->sub;
    s32 *p;
    s32 *cur;
    s32 count;

    p = (s32 *) (arg0 + D_8006E7F0[arg1]->off8 * 4);
    dst->f4 = (s32) p;

    cur = p;
    count = D_8006E7F0[arg1]->count;
    if (count > 0) {
        do {
            count--;
            *cur += arg0;
            cur++;
        } while (count > 0);
    }

    dst->f8 = arg0 + D_8006E7F0[arg1]->offA * 4;
    dst->fC = arg0 + D_8006E7F0[arg1]->offC * 4;
    dst->f10 = arg0 + D_8006E7F0[arg1]->offE * 4;
}
