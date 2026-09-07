#include "common.h"
#include "m2c_compat.h"

typedef struct S_80921A44_0 {
    union { s32 s; volatile s32 u; } unk_00;   /* accessed as both */
    union { volatile s32 s; s32 u; } unk_04;   /* accessed as both */
    union { volatile s32 s; s32 u; } unk_08;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    s32 unk_10;
} S_80921A44_0;   /* arg1 in func_80921A44 */

typedef struct S_80921A44_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80921A44_1;   /* arg2 in func_80921A44 */

typedef struct S_80921A44_2_pre {
    u16 unk_00;
} S_80921A44_2_pre;   /* the 0x2 bytes before arg0 in func_80921A44, addressed as arg0[-1] */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0;
extern void func_800478B8(void *, void *, s32, s32);
void func_80921A44(void *arg0, void *arg1, void *arg2) {
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;

    temp_a3 = ((S_80921A44_0 *)arg1)->unk_0C.s;
    temp_a2 = ((S_80921A44_0 *)arg1)->unk_10;
    temp_v0 = ((S_80921A44_0 *)arg1)->unk_00.s + ((S_80921A44_0 *)arg1)->unk_0C.u;
    temp_v1 = ((S_80921A44_0 *)arg1)->unk_08.s;
    ((S_80921A44_0 *)arg1)->unk_00.u = temp_v0;
    ((S_80921A44_0 *)arg1)->unk_08.u = temp_v1 + 0xFFFE8000;
    ((S_80921A44_0 *)arg1)->unk_04.s = (s32) (((S_80921A44_0 *)arg1)->unk_04.u + ((S_80921A44_0 *)arg1)->unk_10);
    ((S_80921A44_0 *)arg1)->unk_0C.u = (s32) ((temp_a3 * 4) / 5);
    ((S_80921A44_0 *)arg1)->unk_10 = (s32) ((temp_a2 * 4) / 5);
    func_800478B8(arg2, arg1, (s32) (temp_a2 * 4) >> 0x1F, (s32) (temp_a3 * 4) >> 0x1F);
    if (((S_80921A44_1 *)arg2)->unk_14 & 0x6000) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80921A44_2_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
