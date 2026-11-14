#ifndef TOWN_PLAYER_POSITION_UPPER_BOUND_G00540_H
#define TOWN_PLAYER_POSITION_UPPER_BOUND_G00540_H
/* shared declarations for position upper bound. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80099028, CL:town/func_80099080, PD:town/engine:800FE5D4. */

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

extern s16 max_position_minus_z();
extern s32 D_800D040C[];
/* extern */
extern s8 D_800CFCE8;

extern s32 D_800FE5D4;

/* Functions defined in this translation unit. */
s32 query_position_upper_bound(ObjectPosition *position);
void set_player_z_and_sync_collision(ObjectPosition *record, s32 value);
void update_position_upper_bound(ObjectPosition *record);

#endif
