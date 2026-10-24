#ifndef TOWN_PERSON_CALLBACK_OBJECT_RESET_G00688_H
#define TOWN_PERSON_CALLBACK_OBJECT_RESET_G00688_H
/* G00688: shared declarations for callback object reset. */
/* Original-file evidence (G00688): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CEC24. */

#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"

typedef struct {
    u8 pad0[0xC];
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Func800CEC24Arg2;

s32 create_object_from_three_values(s32 *);
#include "town/person/object_setup.h"
extern u8 D_800D6CA8[];

/* Functions defined in this translation unit. */
void prepare_and_forward_callback(void *object, void *context, Func800CEC24Arg2 *callback_arg);
void reset_object_entry_and_brighten(void *object, void *draw_arg, Func800CEC24Arg2 *packet);

#endif
