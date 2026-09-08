#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D54.h"

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80077854;
extern M2C_UNK D_801714AC;
extern s16 D_80173AFC[];
extern void *D_80175D54;
extern void *D_80175DB8;


typedef struct S_801715D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801715D0_1;   /* temp_v0 in func_801715D0 */

typedef struct S_801715D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801715D0_2;   /* temp_v1 in func_801715D0 */

typedef struct S_801715D0_3 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} S_801715D0_3;   /* temp_s3 in func_801715D0 */

typedef struct S_801715D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801715D0_4;   /* temp_a0 in func_801715D0 */

typedef struct S_801715D0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801715D0_5;   /* temp_s2 in func_801715D0 */

typedef struct S_801715D0_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801715D0_6;   /* temp_s1 in func_801715D0 */

typedef struct S_801715D0_7 {
    s16 unk_00;
    s16 unk_02;
} S_801715D0_7;   /* entry in func_801715D0 */

typedef struct S_801715D0_8 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_801715D0_8;   /* temp_v1_2 in func_801715D0 */

void func_801715D0(void) {
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 var_v0;
    s32 var_v0_2;
    register S_801715D0_4 *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_801715D0_6 *temp_s1;
    S_801715D0_5 *temp_s2;
    u8 *entry;
    u8 *table;
    register S_801715D0_3 *temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *temp_v0;
    S_801715D0_2 *temp_v1;
    register S_801715D0_8 *temp_v1_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    temp_s2 = ((Rec_D_80175D54 *)D_80175D54)->unk_08;
    temp_s1 = D_80175D54 + 0x20;
    temp_v0 = func_8003FD64(0x12, D_80175D54);
    if (temp_v0 != NULL) {
        ((S_801715D0_1 *)temp_v0)->unk_10 = &D_801714AC;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = ((S_801715D0_1 *)temp_v0)->unk_0C;
        temp_s3 = temp_v0 + 0x20;
        temp_v1->unk_14 = (u16) ((temp_v1->unk_14 & 0xFFF3) | 0x80);
        temp_s3->unk_24 = temp_s1;
        temp_a0 = ((S_801715D0_1 *)temp_v0)->unk_08;
        temp_a0->unk_02 = (u16) temp_s2->unk_02;
        temp_a0->unk_06 = (u16) temp_s2->unk_06;
        temp_a0->unk_0A = (u16) temp_s2->unk_0A;
        table = (u8 *) 0x80170000;
        ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table += 0x3AFC;
        entry = (u8 *) ((u32) (((u16) temp_s1->unk_2A >> 7) & 0x1C) + (u32) table);
        temp_a0->unk_02 = (u16) (temp_a0->unk_02 + (((S_801715D0_7 *)entry)->unk_00 * 6));
        entry = (u8 *) ((u32) (((u16) temp_s1->unk_2A >> 7) & 0x1C) + (u32) table);
        temp_a0->unk_06 = (u16) (temp_a0->unk_06 + (((S_801715D0_7 *)entry)->unk_02 * 6));
        temp_v1_2 = ((S_801715D0_1 *)temp_v0)->unk_0C;
        temp_v1_2->unk_1E = 0x1000;
        temp_v1_2->unk_1C = 0x1000;
        temp_a0_2 = (s16) temp_s2->unk_02;
        var_v0 = temp_a0_2 - 0x20;
        if (var_v0 < 0) {
            var_v0 = (s32) (temp_a0_2 + 0x1F) >> 6;
        } else {
            var_v0 >>= 6;
        }
        temp_s3->unk_58 = (s8) var_v0;
        temp_a0_3 = (s16) temp_s2->unk_06;
        var_v0_2 = temp_a0_3 - 0x20;
        if (var_v0_2 < 0) {
            var_v0_2 = (s32) (temp_a0_3 + 0x1F) >> 6;
        } else {
            var_v0_2 >>= 6;
        }
        temp_s3->unk_59 = (s8) var_v0_2;
        temp_v1_2->unk_0E = 0x80;
        temp_v1_2->unk_0D = 0x80;
        temp_v1_2->unk_0C = 0x80;
        temp_v1_2->unk_08 = &D_80077854;
        D_80175DB8 = temp_v0;
    }
}

/* MECHANISM: Last-use pins hold the object+0x20 base in s3 and the a0/v0/v1 live-range roles, yielding the retail 0x28 frame.
   A held 0x80170000 page plus addiu 0x3AFC prevents the table low half from folding into its signed halfword loads.
   Named integer-form index+base sums preserve addu v0,v0,a1; shared v0 normalization and u8 color stores close the tail. */
