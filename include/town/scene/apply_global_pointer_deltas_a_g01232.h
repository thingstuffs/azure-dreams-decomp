#ifndef TOWN_SCENE_APPLY_GLOBAL_POINTER_DELTAS_A_G01232_H
#define TOWN_SCENE_APPLY_GLOBAL_POINTER_DELTAS_A_G01232_H
/* Apply global pointer deltas a. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01232 - PR:town/ll34_3e5000_80016000:80017B90. */

#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 *D_80017B90;
void func_80019D60(void *);
/* extern */
extern M2C_UNK D_80017BA0;

/* Functions defined in this translation unit. */
void apply_global_pointer_deltas_a(void);
void apply_global_delta_record_a(void);
void apply_global_pointer_deltas_b(void);
void apply_global_pointer_deltas_c(void);

#endif
