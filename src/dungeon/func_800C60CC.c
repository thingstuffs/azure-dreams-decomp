#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800287A4.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800CB82C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800CB82C_0;   /* temp_v0 in func_800CB82C */

typedef struct S_800CB82C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB82C_1;   /* temp_a1 in func_800CB82C */

typedef struct S_800CB82C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CB82C_2;   /* arg0 in func_800CB82C */

typedef struct S_800CB82C_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
} S_800CB82C_3;   /* temp_a0_2 in func_800CB82C */

typedef struct S_800CB82C_4 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0x9];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    u8 pad_8A[0x6];
    s32 unk_90;
} S_800CB82C_4;   /* temp_a0_3 in func_800CB82C */

typedef struct S_800CB82C_5 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800CB82C_5;   /* &D_800E3CC8 in func_800CB82C */

typedef struct S_800CB82C_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CB82C_6_pre;   /* the 0x14 bytes before arg2 in func_800CB82C, addressed as arg2[-1] */


typedef struct S_800CB82C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CB82C_7;   /* temp_v1 in func_800CB82C */



/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_80099FDC();                      /* extern */
s32 func_800A94A0(); /* extern */
extern M2C_UNK D_800CB600;
extern M2C_UNK D_800E03BC;
extern u8 D_800E3CC8;

/* Create and register an object using the spawn position, source state, and owner. */
void *func_800CB82C(void *spawn_pos, void *source_state, void *owner) {
    u16 object_flags;
    s32 global_flags;
    void *map_data;
    void *object_state;
    void *position;
    void *object;
    void *owner_map;
    u16 *object_counts;
    u16 object_count;

    object = func_8003FC64(0x102);
    if (object != NULL) {
        ((S_800CB82C_0 *)object)->unk_10 = &D_800CB600;
        func_8004491C(object, D_80045340);
        position = ((S_800CB82C_0 *)object)->unk_08;
        ((S_800CB82C_1 *)position)->unk_02 = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_02;
        ((S_800CB82C_1 *)position)->unk_06 = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_06;
        ((S_800CB82C_1 *)position)->unk_0A = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_08.at02.v;
        map_data = ((S_800CB82C_0 *)object)->unk_0C;
        ((S_800CB82C_3 *)map_data)->unk_08 = &D_800E03BC;
        ((S_800CB82C_3 *)map_data)->unk_14 = (u16) (((S_800CB82C_3 *)map_data)->unk_14 | 0xC);
        ((S_800CB82C_3 *)map_data)->unk_24 = (s8) ((u16) ((S_800CB82C_1 *)position)->unk_02 >> 6);
        ((S_800CB82C_3 *)map_data)->unk_25 = (s8) ((u16) ((S_800CB82C_1 *)position)->unk_06 >> 6);
        object_state = object + 0x20;
        (*(s16 *)((u8 *)object_state + 0x96)) = 0x10;
        ((S_800CB82C_4 *)object_state)->unk_08 = (u8) D_800E3CC8;
        ((S_800CB82C_4 *)object_state)->unk_09 = (u8) ((S_800CB82C_5 *)(&D_800E3CC8))->unk_01;
        ((S_800CB82C_4 *)object_state)->unk_60 = owner;
        owner_map = ((S_800CB82C_6_pre *)owner)[-1].unk_00;
        ((S_800CB82C_4 *)object_state)->unk_72 = (u8) ((S_800CB82C_7 *)owner_map)->unk_24;
        ((S_800CB82C_4 *)object_state)->unk_73 = (u8) ((S_800CB82C_7 *)owner_map)->unk_25;
        ((S_800CB82C_4 *)object_state)->unk_88 = (u16) ((Rec_D_800E3D7C *)source_state)->unk_88.as_u16;
        ((S_800CB82C_4 *)object_state)->unk_13 = 0xFF;
        ((S_800CB82C_4 *)object_state)->unk_14 = (s32) ((Rec_D_800E3D7C *)source_state)->unk_14.as_s32;
        ((S_800CB82C_4 *)object_state)->unk_1C = (s32) ((Rec_D_800E3D7C *)source_state)->unk_1C.as_s32;
        ((S_800CB82C_4 *)object_state)->unk_2A = (s16) (((Rec_D_800287A4 *)owner)->unk_2A - 0x800);
        ((S_800CB82C_4 *)object_state)->unk_90 = (s32) ((S_800CB82C_2 *)spawn_pos)->unk_08.at00.v;
        if (func_800A94A0(object_state, object + 0x28, 0, object + 0xB8) == 0) {
            object_flags = ((S_800CB82C_0 *)object)->unk_1E | 0x8000;
            global_flags = D_800814A0[0] | 0x8000;
            ((S_800CB82C_0 *)object)->unk_1E = object_flags;
            D_800814A0[0] = global_flags;
            return NULL;
        }
        func_80099FDC(object);
        object_counts = (u16 *)D_80083460;
        object_count = object_counts[5];
        object_count = (u16) (object_count + 1);
        object_counts[5] = object_count;
    }
    return object;
}
