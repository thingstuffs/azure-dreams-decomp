#ifndef TOWN_PERSON_PERSON_RECORD_HISTORY_G00592_H
#define TOWN_PERSON_PERSON_RECORD_HISTORY_G00592_H
/* Person record history. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AD79C, CL:town/func_800AD7FC, PD:town/engine:80100E40. */

#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "m2c_compat.h"
struct TownObjectRecord;

typedef struct TownPositionHistoryEntry {
    u16 x;
    u16 y;
    u16 z;
    u16 heading;
} TownPositionHistoryEntry;

extern u16 scene_object_payload_alias[];
extern s16 D_800834C8;

extern TownPositionHistoryEntry town_position_history[8];
/* Functions defined in this translation unit. */
void fill_position_history(void);
void push_position_history(void);
void load_position_history_entry(Fixed1616 *destination, s32 entry_index);
void copy_history_entry_heading(struct TownObjectRecord *record, s32 entry_index);

#endif
