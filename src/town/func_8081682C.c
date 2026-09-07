#include "common.h"

typedef struct S_8002082C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002082C_0;   /* (u8 *)arg0 + count * 4 in func_8002082C */

typedef struct S_8002082C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8002082C_1;   /* object in func_8002082C */

typedef struct S_8002082C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8002082C_2;   /* image in func_8002082C */

typedef struct S_8002082C_3 {
    u8 pad_00[0x34];
    s16 unk_34;
} S_8002082C_3;   /* arg0 in func_8002082C */

typedef struct S_8002082C_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002082C_4;   /* object_data in func_8002082C */



extern s32 func_8003DB94();
extern void *func_8003FD64();
extern s32 func_8004491C();

typedef struct {
    u16 field_0;
    u16 field_2;
} D_80026DE0Entry;

extern s32 D_80022698[3];
extern D_80026DE0Entry D_80026DE0[3][8];
extern s32 D_80045340;
extern s32 D_80083498[3];
extern s32 D_800F29B4[3];

void func_8002082C(void *arg0) {
    s32 offset;
    s32 count;
    S_8002082C_4 *object_data;
    S_8002082C_1 *object;
    S_8002082C_2 *image;

    count = 7;
    do {
        object = func_8003FD64(0x136, D_80083498);
        ((S_8002082C_0 *)((u8 *)arg0 + count * 4))->unk_08 = object;
        offset = count * 4;
        if (object != 0) {
            object->unk_10 = D_80022698;
            func_8004491C(object, &D_80045340);
            object->unk_20 = arg0;
            image = object->unk_08;
            object_data = object->unk_0C;
            image->unk_02 = D_80026DE0[((S_8002082C_3 *)arg0)->unk_34][count].field_0;
            image->unk_06 = D_80026DE0[((S_8002082C_3 *)arg0)->unk_34][count].field_2;
            object_data->unk_10 = 0x60;
            object_data->unk_0C = 0;
            object_data->unk_1E = 0x1000;
            object_data->unk_1C = 0x1000;
            object_data->unk_14 |= 0xC;
            func_8003DB94(object_data, D_800F29B4, 0);
        }
        count--;
    } while (count >= 0);
}

/* MECHANISM: Two-u16 table records force one D_80026DE0 base and lhu offsets 0/2.
   Array decay holds D_80022698 in s6; count-indexed slot access lets strength reduction
   place s3 after both held bases, reproducing the -0x30 frame, save order, and loop CFG. */
