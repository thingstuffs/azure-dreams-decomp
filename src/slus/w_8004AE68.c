#include "common.h"

/* Comparator: subtracts two table-lookup values through two independent
   record pointers. Known maspsx-fold-false-positive family
   (see func_8004A8D8/setPacked2bitFlag siblings) — see comment below. */
typedef struct {
    u8 pad0;
    u8 key;
} S_8004AE68_Rec;

typedef struct {
    S_8004AE68_Rec *rec;
} S_8004AE68_Outer;

extern u8 D_800713E4[256];

s32 func_8004AE68(S_8004AE68_Outer *a0, S_8004AE68_Outer *a1)
{
    return D_800713E4[a0->rec->key] - D_800713E4[a1->rec->key];
}
