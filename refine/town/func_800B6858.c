/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B3FB8_3 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800B3FB8_3;   /* arg0 in func_800B3FB8 */

typedef struct S_800B3FB8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B3FB8_4;   /* temp_s3 in func_800B3FB8 */

typedef struct S_800B3FB8_5 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x14];
    void * unk_30;
    u8 pad_34[0x14];
    void * unk_48;
} S_800B3FB8_5;   /* (temp_s1 + arg0->unk_5C) in func_800B3FB8 */

typedef struct S_800B3FB8_6 {
    void * unk_00;
} S_800B3FB8_6;   /* temp_s1 + ((S_800B3FB8_3 *)arg0)->unk_5C in func_800B3FB8 */

typedef struct S_800B3FB8_7 {
    u8 pad_00[0x8];
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800B3FB8_7;   /* ((S_800B3FB8_4 *)temp_s3)->unk_04 in func_800B3FB8 */


s32 func_8004DC14();                    /* extern */

typedef struct S_800B3FB8_0 {
    s32 unk_00;
} S_800B3FB8_0;   /* temp_s3 in func_800B3FB8 */

typedef struct S_800B3FB8_1 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x38];
    s32 unk_5C;
} S_800B3FB8_1;   /* arg0 in func_800B3FB8 */

typedef struct S_800B3FB8_2 {
    s32 unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    s32 unk_10;
} S_800B3FB8_2;   /* arg1 in func_800B3FB8 */

/* Updates the values and positions of four elements in the selected slot. */
void func_800B3FB8(S_800B3FB8_1 *owner, S_800B3FB8_2 *layout, s32 slot_index) {
    s32 slot_offset;
    S_800B3FB8_0 *element;

    slot_offset = slot_index * 4;
    element = ((S_800B3FB8_6 *)(slot_offset + ((S_800B3FB8_3 *)owner)->unk_5C))->unk_00;
    element->unk_00 = (s32) owner->unk_20;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_08.s = (u16) layout->unk_04;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_0A.s = (u16) layout->unk_06;
    element = ((S_800B3FB8_5 *)((slot_offset + owner->unk_5C)))->unk_30;
    element->unk_00 = (s32) layout->unk_10;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_08.s = (u16) layout->unk_08;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_0A.s = (u16) layout->unk_0A;
    element = ((S_800B3FB8_5 *)((slot_offset + owner->unk_5C)))->unk_18;
    element->unk_00 = func_8004DC14(layout->unk_00, 1);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_08.s = (u16) layout->unk_0C;
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_0A.s = (u16) layout->unk_0E;
    element = ((S_800B3FB8_5 *)((slot_offset + owner->unk_5C)))->unk_48;
    element->unk_00 = func_8004DC14(layout->unk_00, 0x90);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_08.u = (s16) (layout->unk_0C - 1);
    ((S_800B3FB8_7 *)(((S_800B3FB8_4 *)element)->unk_04))->unk_0A.u = (s16) (layout->unk_0E + 1);
}
