#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8016EE8C_0 {
    u8 pad_00[0xAB];
    s8 unk_AB;
    u8 pad_AC[0x3];
    s8 unk_AF;
} S_8016EE8C_0;   /* temp_a3 in func_8016EE8C */

typedef struct S_8016EE8C_1 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_8016EE8C_1;   /* page_800e in func_8016EE8C */

typedef struct S_8016EE8C_2 {
    u8 pad_00[0x3714];
    u16 unk_3714;
    u8 pad_3716[0x6];
    s32 unk_371C;
} S_8016EE8C_2;   /* page_8001 in func_8016EE8C */


typedef struct S_8016EE8C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016EE8C_4;   /* temp_v1 in func_8016EE8C */

typedef struct S_8016EE8C_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016EE8C_5;   /* (temp_s0 + ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_s32.v) in func_8016EE8C */


M2C_UNK func_8009A028();                         /* extern */
M2C_UNK func_8016E998();                   /* extern */
extern u16 D_80013714;
extern s16 D_80013716;
extern s16 D_80013718;
extern s16 D_8001371A;
extern s32 D_8001371C;
extern s32 D_8008346C;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800E296C;
extern M2C_UNK D_800E3D7C;
extern s32 D_80173C94;
extern s32 D_80173D5C;
extern s32 D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

void func_8016EE8C(void) {
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s1;
    void *temp_a3;
    void *page_8001;
    void *page_800e;
    void *temp_v1;

    var_s1 = 0;
    page_8001 = (void *)0x80010000;
    page_800e = (void *)0x800E0000;
    temp_a3 = D_80175D50 + 0x20;
    ((S_8016EE8C_0 *)temp_a3)->unk_AF = 1;
    (*(s16 *)((u8 *)page_8001 + 0x371A)) = 0;
    (*(s16 *)((u8 *)page_8001 + 0x3718)) = 0;
    (*(s16 *)((u8 *)page_8001 + 0x3716)) = 0;
    D_8008346C = 0;
    D_80175DC8 = 0;
    ((S_8016EE8C_1 *)page_800e)->unk_296C = (s32) (((S_8016EE8C_1 *)page_800e)->unk_296C | 0x08000000);
    ((S_8016EE8C_2 *)page_8001)->unk_3714 = (u16) ((((S_8016EE8C_2 *)page_8001)->unk_3714 | 9) & 0xFFEF);
    ((S_8016EE8C_2 *)page_8001)->unk_371C = (s32) D_80173C94;
    D_80175DC4 = D_80173D5C;
    ((S_8016EE8C_0 *)temp_a3)->unk_AB = 0;
    do {
        temp_s0 = var_s1 * 4;
        temp_a0 = ((S_8016EE8C_5 *)((temp_s0 + ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_s32.v)))->unk_AC;
        if (temp_a0 != 0) {
            func_8009A028(temp_a0);
            temp_v1 = ((S_8016EE8C_5 *)((temp_s0 + ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_s32.v)))->unk_AC - 0x20;
            ((S_8016EE8C_4 *)temp_v1)->unk_10 = (s32) (((S_8016EE8C_4 *)temp_v1)->unk_10 | 0x80000000);
        }
        var_s1 += 1;
    } while (var_s1 < 2);
    func_8016E998(&D_80083780);
}

/* MECHANISM: A 40-byte frame falls out naturally from s0-s3: s2 holds the
   relocatable D_800E3D7C page across calls, while s3 holds 0x80000000.
   Short-lived 0x80010000/0x800E0000 page locals preserve direct displacements
   and avoid the extra address-add/register hold that caused the residue. */
