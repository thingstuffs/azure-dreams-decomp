#ifndef TOWN_EVENT_MESH_QUAD_TRANSFORM_G00591_H
#define TOWN_EVENT_MESH_QUAD_TRANSFORM_G00591_H
/* inferred-strong G00591: mesh_quad_transform_g00591; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC7B4, CL:town/func_800AC8E4, CL:town/func_800AC908, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D1C, PD:town/engine:80100D40. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"

#define OTSLOT() (*(u32 *)((u8 *)scratch->unk_24 + scratch->unk_C4 * 4))

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800AA044_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800AA044_0;

/* arg0 in copy_even_halfwords_3 */
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
    u8 *unk_00;
    s16 *unk_04;
    u8 pad_08[0x18];
    u32 *unk_20;
} S_func_800AC9AC_0;

typedef struct S_func_800AC9AC_1 {
    u8 pad_00[0x24];
    u32 *unk_24;
    u8 pad_28[0x9C];
    s32 unk_C4;
    u8 pad_C8[0x20];
    u16 unk_E8;
    u16 unk_EA;
    u16 unk_EC;
    u16 unk_EE;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
} S_func_800AC9AC_1;


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

s32 TransMatrix(void *, void *);
s32 ScaleMatrix(void *, void *);
s32 SetRotMatrix(void *);
s32 SetTransMatrix(void *);
s32 RotTrans(void *, void *, s32 *);
s32 RotMatrix(void *, void *);
/* extern */
extern s32 D_800D11C0[4];
extern void PushMatrix(void);
extern void PopMatrix(void);
extern s32 RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetSemiTrans(void *, s32);
extern void SetLineG4(void *);
extern void SetDrawMode(void *, s32, s32, u16, s32);
extern s32 rand(void);
extern void copy_menu_vector_halfwords(void *, void *);
extern void add_entity_position_to_menu_vector(void *, void *);

/* Functions defined in this translation unit. */
void copy_even_halfwords_3(S_800AA044_0 *dst, S_800AA044_1 *src);
void transform_vector(s32 transform, void *vector, void *transformed);
void transform_and_queue_mesh_quads(S_func_800AC9AC_0 *mesh, void *transform);

#endif
