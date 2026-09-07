#include "common.h"

/* Runs a per-frame update via func_80043EB8, then, if the current
   D_80081500-indexed slot of D_80083120 has not been flagged yet,
   sets bit 0 of D_80082E60.field_0 and invokes func_80040B88. */
/* element type for the D_80083120 dispatch/state table, indexed by *8 (element size 8) */
typedef struct S_80083120 {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern s16 D_80081500;

/* only offset 0 (a 32-bit field) of D_80082E60 is touched here; padded so the
   global is addressed via %hi/%lo rather than %gp_rel like the sibling TU */
extern struct {
    s32 field_0;
    u8 pad[12];
} D_80082E60;

extern void func_80043EB8(void);
extern void func_80040B88(void);

void func_80043E60(void) {
    func_80043EB8();
    if (D_80083120[D_80081500].field_0 == 0) {
        D_80082E60.field_0 |= 1;
        func_80040B88();
    }
}
