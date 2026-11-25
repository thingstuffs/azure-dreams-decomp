#ifndef TOWN_EVENT_MESH_QUAD_TRANSFORM_G00591_H
#define TOWN_EVENT_MESH_QUAD_TRANSFORM_G00591_H
/* inferred-strong mesh_quad_transform_g00591; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC7B4, CL:town/func_800AC8E4, CL:town/func_800AC908, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D1C, PD:town/engine:80100D40. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "sdk/libgte_matrix.h"
#include "shared/gpu_packets.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"

/* Indexing the pointer changes where the renderer loads the vertex pointer. */
#define OTSLOT() (*(u32 *)((u8 *)scratch->ordering_table + scratch->ordering_depth * 4))

typedef struct S_800AA044_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800AA044_0;

/* arg0 in narrow_vector_to_svector */
typedef struct S_800AA044_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_800AA044_1;

struct S_800AA044_0;

struct S_800AA044_1;

typedef struct S_func_800AC9AC_0 {
    SVECTOR *vertices;
    s16 *unk_04;
    u8 pad_08[0x18];
    u32 *unk_20;
} S_func_800AC9AC_0;

typedef struct S_func_800AC9AC_3 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} S_func_800AC9AC_3;

/* extern */
extern s32 D_800D11C0[4];
extern void copy_menu_point(void *, void *);
extern void add_entity_position_to_menu_vector(SVECTOR *components, Fixed1616 increments[3]);

/* Functions defined in this translation unit. */
void narrow_vector_to_svector(SVECTOR *dst, VECTOR *src);
void transform_vector(s32 transform, SVECTOR *vector, VECTOR *transformed);

#endif
