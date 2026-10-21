#ifndef TOWN_PLAYER_POSITION_UPPER_BOUND_G00540_H
#define TOWN_PLAYER_POSITION_UPPER_BOUND_G00540_H
/* G00540: shared declarations for position upper bound. */
/* Original-file evidence (G00540): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80099028, CL:town/func_80099080, PD:town/engine:800FE5D4. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct {
    u32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[2];
} LocalVec;

/* extern */
struct EntityRec;

extern s16 max_adjusted_z_query();
extern s32 D_800D040C[];
/* cfail-repair: tf7-phase1-cache-v3 */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(EntityRec *);
/* extern */
extern s8 D_800CFCE8;

extern s32 D_800FE5D4;

/* Functions defined in this translation unit. */
s32 handle_query_position_after_subtracting_global_z_offset(Vec3i *position);
void set_the_clear_secondary_refresh_global_flag_set(EntityRec *record, s32 value);
void update_the_computed_upper_bound_global_state_permits(EntityRec *record);

#endif
