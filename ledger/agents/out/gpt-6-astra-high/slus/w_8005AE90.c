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

/* Activates an occupied slot with the requested sub-id and mode. */
void func_8005AE90(s16 slot_index, u8 mode, s16 sub_id)
{
    if (slot_index != -1) {
        func_80056A08();
        if (D_80086C00[slot_index].field_0 != -1) {
            D_80086D50[0] = D_80086C00[slot_index].field_0;
            D_80086D48[0] = sub_id;
            D_800869B0[0] = 0x10000;
            D_80085FA4[0] = D_80086C00[slot_index].field_4;
            func_800599B0();
            if (!(mode & 0xFF)) {
                D_800737A4[0] = 0;
                D_80085F98[0] = 1;
                D_80086C00[slot_index].field_2 = 4;
            } else {
                D_800737A4[0] = 1;
                D_80085F98[0] = 0;
                D_80086C00[slot_index].field_2 = 1;
            }
        }
    }
}
