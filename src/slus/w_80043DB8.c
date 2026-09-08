#include "common.h"

/* element type for the D_80083120 dispatch/state table, indexed by *8 (element size 8) */
typedef struct S_80083120 {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
} S_80083120;

extern S_80083120 D_80083120[];
extern s16 D_80081500;

extern void func_80043EB8(void);
extern void func_80043E04(void);
extern void func_80040A88(int a0);

/* Updates the current slot and installs func_80043E04 as its handler if inactive. */
void func_80043DB8(void) {
    func_80043EB8();
    if (D_80083120[D_80081500].field_0 == 0) {
        func_80040A88((int) func_80043E04);
    }
}
