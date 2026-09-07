#include "common.h"

/* S_80086C00: 12-byte-stride entry table (8 entries), indexed by the "slot
 * index" arg0. field_0/field_2 are s16, field_4 is a s32 buffer/base
 * pointer value, field_8/field_A are u16 (not accessed here). */
typedef struct {
    /* 0x00 */ s16 field_0;
    /* 0x02 */ s16 field_2;
    /* 0x04 */ s32 field_4;
    /* 0x08 */ u16 field_8;
    /* 0x0A */ u16 field_A;
} S_80086C00; /* size 0xC (12) */

extern S_80086C00 D_80086C00[8];
extern s16 D_80086D50[8];  /* forced hi/lo access via size > 8 */
extern s16 D_80086D48[8];  /* forced hi/lo access via size > 8 */
extern s32 D_800869B0[4];  /* forced hi/lo access via size > 8 */
extern s32 D_80085FA4[4];  /* forced hi/lo access via size > 8 */
extern s32 D_800737A4[4];  /* forced hi/lo access via size > 8 */
extern s32 D_80085F98[4];  /* forced hi/lo access via size > 8 */

extern void func_80056A08(void);
extern void func_800599B0(void);

/* Activates a table slot (D_80086C00[a0]) for playback/display: skips if
 * a0 is -1 or the slot's field_0 is -1 (empty). Otherwise runs
 * func_80056A08(), records the "current slot" value (D_80086D50), current
 * sub-id (D_80086D48 = a2), a base pointer (D_800869B0 = 0x10000), and the
 * slot's data-buffer pointer (D_80085FA4 = field_4), kicks off
 * func_800599B0(), then records a mode flag (D_800737A4 / D_80085F98) and
 * stores that mode back into the slot entry's field_2, depending on
 * whether arg1's low byte is set. */
void func_8005AE90(s16 a0, u8 a1, s16 a2)
{
    s16 new_var;
    S_80086C00 *entry;

    new_var = a0;
    if (new_var != -1) {
        func_80056A08();
        if ((&D_80086C00[a0])->field_0 != -1) {
            D_80086D50[0] = (&D_80086C00[a0])->field_0;
            D_80086D48[0] = a2;
            D_800869B0[0] = 0x10000;
            D_80085FA4[0] = (&D_80086C00[a0])->field_4;
            func_800599B0();
            if (!(a1 & 0xFF)) {
                D_800737A4[0] = 0;
                D_80085F98[0] = 1;
                (&D_80086C00[a0])->field_2 = 4;
            } else {
                D_800737A4[0] = 1;
                D_80085F98[0] = 0;
                (&D_80086C00[a0])->field_2 = 1;
            }
        }
    }
}
