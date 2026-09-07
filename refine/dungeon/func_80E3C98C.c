#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80E3C98C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x40];
    s32 unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80E3C98C_0;   /* arg3 in func_80E3C98C */

typedef struct S_80E3C98C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80E3C98C_1;   /* arg2 in func_80E3C98C */

typedef struct S_80E3C98C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_2_pre;   /* the 0x14 bytes before var_s0 in func_80E3C98C, addressed as var_s0[-1] */

typedef struct S_80E3C98C_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_80E3C98C_2;   /* var_s0 in func_80E3C98C */

typedef struct S_80E3C98C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_3_pre;   /* the 0x14 bytes before var_s1 in func_80E3C98C, addressed as var_s1[-1] */

typedef struct S_80E3C98C_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80E3C98C_3;   /* var_s1 in func_80E3C98C */

typedef struct S_80E3C98C_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80E3C98C_4;   /* var_s0_2 in func_80E3C98C */

typedef struct S_80E3C98C_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x34];
    void * unk_E4;
} S_80E3C98C_5;   /* temp_v0 in func_80E3C98C */

typedef struct S_80E3C98C_6 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80E3C98C_6;   /* ((S_80E3C98C_2_pre *)var_s0)[-1].unk_00 in func_80E3C98C */

typedef struct S_80E3C98C_7 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80E3C98C_7;   /* ((S_80E3C98C_3_pre *)var_s1)[-1].unk_00 in func_80E3C98C */



extern s32 func_8003F320();
extern s32 func_80042640();
extern s32 func_80042710();
extern s32 func_8004397C();
extern void *(*func_800A0B94())(s32, u8, u8, s16);
extern void *func_800A1618();
extern s32 func_800A1BD0();
extern s32 func_800A7A38();
extern void *func_800B23F8();
extern void func_80176368(void) __attribute__((noreturn));
extern s8 D_800E2968;
extern u8 D_800E3548[];
extern u8 *D_800E3D7C;

/* Create an entity from spawn data and update its tracked reference. */
void *func_80E3C98C(void *unused0, void *unused1, S_80E3C98C_1 *position, S_80E3C98C_0 *spawn_data) {
    s32 spawn_mode;
    s32 source_ref;
    u8 *table_base;
    void *(*create_entity)(s32, u8, u8, s16);
    s32 table_offset;
    S_80E3C98C_5 *table_entry;
    void *previous_entity;
    void *source_entity;
    void *entity;
    S_80E3C98C_4 *type_data;
    void *result;

    source_ref = spawn_data->unk_60;
    if (source_ref > 0) {
        entity = func_800B23F8(((u32)spawn_data->unk_1C >> 0xD) & 1,
                               position->unk_24, position->unk_25,
                               spawn_data->unk_88,
                               func_800A7A38(((s32)(((u16)spawn_data->unk_60 - 1) << 0x10) >> 0xE) + D_800E3548));
        if (entity != NULL) {
            ((S_80E3C98C_2 *)entity)->unk_14 = 0;
            ((S_80E3C98C_2 *)entity)->unk_1C = 0;
            func_80042710(entity, spawn_data);
            ((S_80E3C98C_2 *)entity)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)entity)->unk_1C =
                (((S_80E3C98C_2 *)entity)->unk_1C | 0x02000200) & 0xFFFEFFFF;
            func_80176368();
        }
        goto update_reference;
    }
    D_800E2968 = 1;
    source_entity = (void *)source_ref;
    
    type_data = func_800A1618(((S_80E3C98C_3 *)source_entity)->unk_13, 1);
    if (((type_data != NULL) && (type_data->unk_01 != 0)) ||
        (type_data = func_800A1618(((S_80E3C98C_3 *)source_entity)->unk_13, 3),
         result = NULL, type_data != NULL)) {
        func_8004397C(source_entity);
        create_entity = func_800A0B94(((S_80E3C98C_3 *)source_entity)->unk_13, type_data, 1);
        func_8003F320();
        spawn_mode = 4;
        if (spawn_data->unk_1C & 0x2000) {
            spawn_mode = 7;
        }
        entity = create_entity(spawn_mode, position->unk_24, position->unk_25, spawn_data->unk_88);
        if (entity != NULL) {
            func_80042640(entity, ((S_80E3C98C_2 *)entity)->unk_13);
            ((S_80E3C98C_2 *)entity)->unk_14 = 0;
            ((S_80E3C98C_2 *)entity)->unk_1C = 0;
            func_80042710(entity, spawn_data);
            ((S_80E3C98C_2 *)entity)->unk_28++;
            ((S_80E3C98C_2 *)entity)->unk_13 = ((S_80E3C98C_3 *)source_entity)->unk_13;
            ((S_80E3C98C_6 *)(((S_80E3C98C_2_pre *)entity)[-1].unk_00))->unk_12 =
                ((S_80E3C98C_7 *)(((S_80E3C98C_3_pre *)source_entity)[-1].unk_00))->unk_12 & 3;
            ((S_80E3C98C_2 *)entity)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)entity)->unk_1C = (((S_80E3C98C_2 *)entity)->unk_1C | 0x02000000) & 0xFFFEFFFF;
        }
update_reference:
        if (spawn_data->unk_14 & 0x4000) {
            table_offset = func_800A1BD0(spawn_data);
            table_base = D_800E3D7C;
            table_entry = (void *)(((s32)(table_offset << 0x10) >> 0xE) +
                               (s32)table_base);
            
            previous_entity = table_entry->unk_AC;
            table_entry->unk_AC = entity;
            table_entry->unk_E4 = previous_entity;
        }
        result = NULL;
        if (entity != NULL) {
            result = (u8 *)entity - 0x20;
        }
    }
    return result;
}
