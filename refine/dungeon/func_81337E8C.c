#include "common.h"
#include "m2c_compat.h"

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

typedef struct S_8016EE8C_3 {
    s32 unk_00;
} S_8016EE8C_3;   /* &D_800E3D7C in func_8016EE8C */

typedef struct S_8016EE8C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016EE8C_4;   /* temp_v1 in func_8016EE8C */

typedef struct S_8016EE8C_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016EE8C_5;   /* (temp_s0 + ((S_8016EE8C_3 *)(&D_800E3D7C))->unk_00) in func_8016EE8C */


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

/* Reset shared state and update the two occupied object slots. */
void func_8016EE8C(void) {
    s32 object_data;
    s32 slot_offset;
    s32 slot_index;
    void *active_data;
    void *page_8001;
    void *page_800e;
    void *object_header;

    slot_index = 0;
    page_8001 = (void *)0x80010000;
    page_800e = (void *)0x800E0000;
    active_data = D_80175D50 + 0x20;
    ((S_8016EE8C_0 *)active_data)->unk_AF = 1;
    (*(s16 *)((u8 *)page_8001 + 0x371A)) = 0;
    (*(s16 *)((u8 *)page_8001 + 0x3718)) = 0;
    (*(s16 *)((u8 *)page_8001 + 0x3716)) = 0;
    D_8008346C = 0;
    D_80175DC8 = 0;
    ((S_8016EE8C_1 *)page_800e)->unk_296C = (s32) (((S_8016EE8C_1 *)page_800e)->unk_296C | 0x08000000);
    ((S_8016EE8C_2 *)page_8001)->unk_3714 = (u16) ((((S_8016EE8C_2 *)page_8001)->unk_3714 | 9) & 0xFFEF);
    ((S_8016EE8C_2 *)page_8001)->unk_371C = (s32) D_80173C94;
    D_80175DC4 = D_80173D5C;
    ((S_8016EE8C_0 *)active_data)->unk_AB = 0;
    do {
        slot_offset = slot_index * 4;
        object_data = ((S_8016EE8C_5 *)((slot_offset + ((S_8016EE8C_3 *)(&D_800E3D7C))->unk_00)))->unk_AC;
        if (object_data != 0) {
            func_8009A028(object_data);
            object_header = ((S_8016EE8C_5 *)((slot_offset + ((S_8016EE8C_3 *)(&D_800E3D7C))->unk_00)))->unk_AC - 0x20;
            ((S_8016EE8C_4 *)object_header)->unk_10 = (s32) (((S_8016EE8C_4 *)object_header)->unk_10 | 0x80000000);
        }
        slot_index += 1;
    } while (slot_index < 2);
    func_8016E998(&D_80083780);
}

/* MECHANISM: A 40-byte frame falls out naturally from s0-s3: s2 holds the
   relocatable D_800E3D7C page across calls, while s3 holds 0x80000000.
   Short-lived 0x80010000/0x800E0000 page locals preserve direct displacements
   and avoid the extra address-add/register hold that caused the residue. */
