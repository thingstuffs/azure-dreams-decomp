#include "common.h"

/* S_8006E704: array of pointers to a small struct whose only field this
 * function touches is a packed 32-bit "color/mode" word at offset 0 (top 9
 * bits = category, low 23 bits = an id taken from the ADDRESS of one of two
 * marker tables D_801C4640 / D_801BEE40, mirroring the func_8003F6D4 pack
 * idiom: (cat<<23) | (id & 0x7FFFFF)). */
typedef struct S_8006E704 {
    s32 field_0;
} S_8006E704;

extern S_8006E704 *D_8006E704[];
/* S_80080AF3 : a single scalar byte, gp-relative (<=8B). Kept a plain scalar
 * (not wrapped in a struct) because this function's only access is a bare
 * lb of the symbol itself, with no offset. */
extern s8 D_80080AF3;
/* D_80080AF4: 2-entry array of pointers into D_8006E704's entries, indexed by
 * the "current"/"toggled" slot selector D_80080AFC (0 or 1). Its TRUE finite
 * size (2, not an oversized/incomplete decl) is load-bearing for codegen --
 * see globals/learnings. */
extern S_8006E704 *D_80080AF4[2];
extern s16 D_80080AFC;
/* Declared oversized (>8B) so their ADDRESS is taken via %hi/%lo, matching
 * the target's lui/addiu pair (their contents are never dereferenced --
 * only the low 23 bits of the address itself are used as a packed id). */
extern s32 D_801C4640[4];
extern s32 D_801BEE40[4];

extern void func_800542BC(void);
extern void func_80044698(void);
extern s32 func_8004450C(s16 arg0);
extern s32 Control_CD(s32 a0, void *a1, s32 a2);
extern void func_8003F320(void);
extern short SD_Call(int a0);

/* Selects a buffered entry, registering it with the slot marker and applying the requested mode. */
s32 func_8004437C(s16 entry_index, s16 mode)
{
    if (D_8006E704[entry_index] == D_80080AF4[D_80080AFC]) {
        return 1;
    }

    D_80080AFC = (u16) D_80080AFC ^ 1;

    if (D_8006E704[entry_index] != D_80080AF4[D_80080AFC]) {
        func_800542BC();

        if (D_80080AF3 != mode) {
            func_80044698();
        }

        D_8006E704[entry_index]->field_0 &= ~0x7FFFFF;
        D_8006E704[entry_index]->field_0 |=
            ((D_80080AFC != 0) ? (s32) D_801C4640 : (s32) D_801BEE40) & 0x7FFFFF;

        Control_CD(6, D_8006E704[entry_index], 0);
        D_80080AF4[D_80080AFC] = D_8006E704[entry_index];
        func_8003F320();
    }

    func_8004450C(mode);

    SD_Call((D_80080AFC != 0) ? 0x22 : 0x21);

    return 0;
}
