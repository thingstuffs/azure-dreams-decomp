#ifndef DUNGEON_OVL_9C32D4_H
#define DUNGEON_OVL_9C32D4_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} ovl_9c32d4_809A32D4_S_80174AD4_0;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_1 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} ovl_9c32d4_809A32D4_S_80174AD4_1;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} ovl_9c32d4_809A32D4_S_80174AD4_2;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} ovl_9c32d4_809A32D4_S_80174AD4_3;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
} ovl_9c32d4_809A32D4_S_80174AD4_4;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_9c32d4_809A32D4_S_80174AD4_5;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} ovl_9c32d4_809A32D4_S_80174AD4_6;
typedef struct ovl_9c32d4_809A32D4_S_80174AD4_7 {
    u16 unk_00;
} ovl_9c32d4_809A32D4_S_80174AD4_7;
typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
} ovl_9c32d4_809A32D4_LocalArgs;
typedef struct {
    u8 pad00[0xC];
    u16 *field0C;
    u8 *field10;
    u8 pad14[2];
    u8 field16;
    u8 state;
    u8 pad18[4];
    void *field1C;
} ovl_9c32d4_809A32D4_Actor;
typedef struct {
    u8 pad00[2];
    u16 field02;
    u8 pad04[2];
    u16 field06;
    u8 pad08[2];
    s16 field0A;
} ovl_9c32d4_809A32D4_Output;
#define DUNGEON_INITIAL (g_game_work.draw_buffer)
#define DUNGEON_FROM_PAGE (g_game_work.draw_buffer)
typedef struct ovl_9c32d4_809A35A0_S_80174DA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} ovl_9c32d4_809A35A0_S_80174DA0_0;
typedef struct ovl_9c32d4_809A35A0_S_80174DA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} ovl_9c32d4_809A35A0_S_80174DA0_2;
typedef struct ovl_9c32d4_809A35A0_S_80174DA0_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} ovl_9c32d4_809A35A0_S_80174DA0_3;
typedef struct ovl_9c32d4_809A35A0_S_80174DA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 * unk_10;
    u8 pad_14[0x2];
    u8 unk_16;
    u8 pad_17[0x5];
    void * unk_1C;
} ovl_9c32d4_809A35A0_S_80174DA0_4;
typedef struct ovl_9c32d4_809A35A0_S_80174DA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ovl_9c32d4_809A35A0_S_80174DA0_5;
typedef union { s32 word; struct { u16 low, high; } ovl_9c32d4_809A3698_half; } ovl_9c32d4_809A3698_FixedCoord;
typedef struct { ovl_9c32d4_809A3698_FixedCoord x, y, z; } ovl_9c32d4_809A3698_MotionPosition;
typedef struct { u8 pad00[0x14]; s16 direction; u8 pad16[0x1C]; s16 speed; } ovl_9c32d4_809A3698_MotionState;
typedef union { s32 word; struct { u16 low, high; } ovl_9c32d4_809A37C0_half; } ovl_9c32d4_809A37C0_FixedCoord;
typedef struct { ovl_9c32d4_809A37C0_FixedCoord x, y, z; } ovl_9c32d4_809A37C0_MotionPosition;
typedef struct { u8 pad00[0x14]; s16 direction; u8 pad16[0x1C]; s16 speed; } ovl_9c32d4_809A37C0_MotionState;
typedef struct { u8 pad00[6]; u16 count; void *resource; s32 value; u8 pad10[12]; u16 scale_x, scale_y; } ovl_9c32d4_809A37C0_MotionDraw;
typedef struct { u8 pad00[8]; ovl_9c32d4_809A37C0_MotionPosition *position; ovl_9c32d4_809A37C0_MotionDraw *draw; void (*update)(ovl_9c32d4_809A37C0_MotionState *, ovl_9c32d4_809A37C0_MotionPosition *); u8 pad14[12]; ovl_9c32d4_809A37C0_MotionState state; } ovl_9c32d4_809A37C0_MotionObject;
typedef struct ovl_9c32d4_809A38E4_S_801750E4_0_pre {
    s16 unk_00;
    s16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x6];
    s16 unk_0C;
    s16 unk_0E;
    u8 unk_10;
    u8 unk_11;
} ovl_9c32d4_809A38E4_S_801750E4_0_pre;
typedef struct ovl_9c32d4_809A38E4_S_801750E4_0 {
    u16 unk_00;
    u8 pad_02[0x4];
    s16 unk_06;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x6];
    s16 unk_12;
    s16 unk_14;
    u8 unk_16;
    u8 unk_17;
} ovl_9c32d4_809A38E4_S_801750E4_0;
typedef struct ovl_9c32d4_809A38E4_GraphicsState {
    u8 pad[0x8D0];
    void *next_prim;
} ovl_9c32d4_809A38E4_GraphicsState;
typedef struct ovl_9c32d4_809A38E4_Elem {
    u32 color;
    s16 x;
    s16 y;
    u8  a;
    u8  b;
    u16 code;
} ovl_9c32d4_809A38E4_Elem;
typedef struct ovl_9c32d4_809A38E4_Block {
    u32 tag;
    ovl_9c32d4_809A38E4_Elem e[4];
} ovl_9c32d4_809A38E4_Block;
typedef struct ovl_9c32d4_809A38E4_RingRadii {
    u16 inner_x;
    u16 inner_y;
    u16 outer_x;
    u16 outer_y;
} ovl_9c32d4_809A38E4_RingRadii;
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
void emit_concentric_ellipse_quads(u16 radius_a_x, u16 radius_a_y, u16 radius_b_x, u16 radius_b_y,
                   u16 center_x, s16 center_y, s32 *color_b_ptr, s32 *color_a_ptr,
                   s32 draw_bucket, s32 start_segment, s32 end_segment);
extern void process_linked_mesh_states_mode_0(void);
extern u8 D_801C9E40[16];
extern void *allocate_list_node();
extern void *func_8003FD64();
extern u8 D_80175F90[12];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 height);
extern s32 D_800814A0;
extern void project_sprite_chain(void);
extern void func_80045340(void);
extern u32 func_80069EF8(void);
extern u8 D_80175F9C[12];
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8006671C(void *);
void update_actor_render_effect_and_position(u8 *actor_data, u8 *output_data, u8 *effect_data);
void create_parent_position_effect(EntityRec *parent, s32 effect_param, u8 *effect_data);
void advance_directional_effect_motion(ovl_9c32d4_809A3698_MotionState *state, ovl_9c32d4_809A3698_MotionPosition *position);
void spawn_randomized_directional_motion_object(ovl_9c32d4_809A37C0_MotionObject *parent, s16 direction, s32 value);
static __inline__ s16 project_ring_coordinate(s32 radius, s32 trig, u16 center);
#endif
