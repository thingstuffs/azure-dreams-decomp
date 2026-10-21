#ifndef TOWN_PERSON_PERSON_RECORD_HISTORY_G00592_H
#define TOWN_PERSON_PERSON_RECORD_HISTORY_G00592_H
/* Person record history (G00592). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AD79C, CL:town/func_800AD7FC, PD:town/engine:80100E40. */

#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB014_arg0.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} Record;

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} TownRecord;

typedef struct S_800AB014_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800AB014_1;

extern u16 scene_object_payload_alias[];
extern s16 D_800834C8;

extern Record town_position_history[8];
/* Functions defined in this translation unit. */
void fill_person_records(void);
void shift_history_and_store_current_values(void);
void load_record_halfwords_3(void *destination, s32 entry_index);
void copy_person_table_value(Rec_func_800AB014_arg0 *record, s32 entry_index);

#endif
