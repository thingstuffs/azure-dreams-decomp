#include "common.h"
#include "m2c_compat.h"

typedef struct S_80167540_0 {
    u16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80167540_0;   /* arg0 in func_80167540; pointer addresses record offset 0x2 */

typedef struct S_80167540_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80167540_1;   /* arg2 in func_80167540 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
s32 rand();                   /* extern */
s16 func_80167088();                         /* extern */

void func_80167540(void *arg0, void *arg1, S_80167540_1 *arg2) {
    s16 temp_v0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v1;

    temp_v0 = func_80167088(3);
    var_a2 = 0x20;
    var_a1 = 0x20;
    ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1E = temp_v0;
    var_v1 = 0x20;
    if (temp_v0 == 0) {
        var_v1 = 0x50;
    }
    if (temp_v0 == 1) {
        var_a1 = 0x50;
    }
    if (temp_v0 == 2) {
        var_a2 = 0x50;
    }
    arg2->unk_0C = (s8) ((s32) (var_v1 * ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1C);
    arg2->unk_0D = (s8) ((s32) (var_a1 * ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1C);
    arg2->unk_0E = (s8) ((s32) (var_a2 * ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1C);
    ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A = (s16) ((u16) ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A - 1);
    if (rand(temp_v0, var_a1, var_a2) & 1) {
        arg2->unk_14 = (u16) (arg2->unk_14 | 1);
    } else {
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xFFFE);
    }
    if (rand() & 1) {
        arg2->unk_14 = (u16) (arg2->unk_14 | 2);
    } else {
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xFFFD);
    }
    func_800478B8(arg2);
    if (((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_1A <= 0) {
        ((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_80167540_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
