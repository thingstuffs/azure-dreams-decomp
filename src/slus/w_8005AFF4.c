#include "common.h"

/* S_80086C00: 12-byte-stride sound-driver "sequence slot" table (8 entries),
 * indexed by the slot index arg0. Canonical layout established by sibling
 * functions (w_8005AE08.c, w_8005AE90.c, w_8005B27C.c, w_8005C5D0.c). */
typedef struct S_80086C00 {
    s16 field_0;   /* 0x0: -1 == free slot */
    s16 field_2;   /* 0x2: type/status */
    s32 field_4;   /* 0x4: data pointer / word value */
    u16 field_8;   /* 0x8 */
    u16 field_A;   /* 0xA */
} S_80086C00;

extern S_80086C00 D_80086C00[8];
extern s32 D_80085F98[4]; /* forced hi/lo access via size > 8 */

extern void func_80059D1C(void);
extern void func_80056A08(void);

/* Resets a sound sequence slot to its free/default state. */
void func_8005AFF4(s32 slot_id)
{
    s16 slot_index;

    D_80085F98[0] = 1;
    func_80059D1C();
    func_80056A08();
    slot_index = (s16)slot_id;

    D_80086C00[slot_index].field_0 = -1;
    D_80086C00[slot_index].field_2 = 0;
    D_80086C00[slot_index].field_A = 0x7F;
    D_80086C00[slot_index].field_8 = 0x7F;

    D_80085F98[0] = 0;
}
