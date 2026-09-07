#include "common.h"
#include "m2c_compat.h"

typedef struct S_80F606C0_0_pre {
    u16 unk_00;
} S_80F606C0_0_pre;   /* the 0x2 bytes before arg0 in func_80F606C0, addressed as arg0[-1] */

typedef struct S_80F606C0_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80F606C0_0;   /* arg0 in func_80F606C0 */

typedef struct S_80F606C0_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80F606C0_1;   /* arg1 in func_80F606C0 */

typedef struct S_80F606C0_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80F606C0_2;   /* arg2 in func_80F606C0 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern int   D_800814A0[];
void func_80F606C0(void *arg0, S_80F606C0_1 *arg1, S_80F606C0_2 *arg2) {
    s16 temp_v1;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v0_2;

    var_v0 = ((S_80F606C0_0 *)arg0)->unk_0C - arg1->unk_00.at02.v;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v + ((var_v0 >> 2) << 0x10));
    arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v + (((s32) (((S_80F606C0_0 *)arg0)->unk_0E - arg1->unk_04.at02.v) / 4) << 0x10));
    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + (((s32) (((S_80F606C0_0 *)arg0)->unk_10 - arg1->unk_08.at02.v) / 4) << 0x10));
    func_800478B8(arg2);
    temp_v1 = ((S_80F606C0_0 *)arg0)->unk_4C;
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = arg2->unk_1E - 0x80;
        arg2->unk_1E = temp_v0;
        arg2->unk_1C = temp_v0;
        temp_v0_2 = ((S_80F606C0_0 *)arg0)->unk_48 - 1;
        ((S_80F606C0_0 *)arg0)->unk_48 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            ((S_80F606C0_0 *)arg0)->unk_4C = (s16) ((u16) ((S_80F606C0_0 *)arg0)->unk_4C + 1);
            return;
        }
        return;
    case 1:
        ((S_80F606C0_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80F606C0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
        break;
    }
}
