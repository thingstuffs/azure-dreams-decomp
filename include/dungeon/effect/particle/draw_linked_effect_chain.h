#ifndef DUNGEON_OVL_19C088C_H
#define DUNGEON_OVL_19C088C_H
#include "shared/vector.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_part_command.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity_height_offsets.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
struct ObjectNodeHeader;

typedef struct Row_819A0DB8_S_func_819A0DB8_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} Row_819A0DB8_S_func_819A0DB8_1;

typedef struct RotatingDirectionalSpriteBody {
    u8 pad_00[0x3A];
    s16 unk_3A;
    s16 unk_3C;
} RotatingDirectionalSpriteBody;

typedef struct Row_819A0EF0_S_800246F0_3 {
    s32 unk_00;
} Row_819A0EF0_S_800246F0_3;   /* D_800814A0 in func_800246F0 */

/* Fade and move the effect, marking it finished when its countdown expires. */
typedef struct Row_819A0FC0_S_func_819A0FC0_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
} Row_819A0FC0_S_func_819A0FC0_0;

typedef struct Row_819A0FC0_S_func_819A0FC0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} Row_819A0FC0_S_func_819A0FC0_1;

typedef struct Row_819A0FC0_S_func_819A0FC0_2 {
    u16 unk_00;
} Row_819A0FC0_S_func_819A0FC0_2;

typedef struct {
    u8 pad00[0x0C];
    s8 c0;
    s8 c1;
    s8 c2;
    u8 pad0F[0x0B];
    u16 angle;
} Row_819A13D0_Obj;

/* Decrement the count, update the object angle and components, and flag completion. */
typedef struct Row_819A1450_S_819A1450_4 {
    u8 pad_00[0x36];
    s16 unk_36;
    u8 pad_38[0x4C];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
} Row_819A1450_S_819A1450_4;   /* arg0 in func_80024C50 */

typedef struct {
    s16 first;
    u16 second;
} Row_819A1450_LocalEntry;

typedef struct {
    Row_819A1450_LocalEntry entries[8];
} Row_819A1450_LocalTable;

/* Creates an effect at an offset from the source with direction-based motion. */
typedef struct Row_819A1654_Coord {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Row_819A1654_Coord;

typedef struct EntityEffectSequencePrefix {
    u8 pad0[0xC];
    SpriteColor colors[4];
    SpriteColor initial_colors[4];
    u8 pad2C[0xE];
    s16 timer3A;
    s16 timer3C;
    s16 mode3E;
    u16 random40;
    u8 pad42[0x12];
    s16 path[18];
} EntityEffectSequencePrefix;

/* The inline commands start at body +0x8A, two bytes past word alignment. */
typedef struct Row_819A1654_Blob12 {
    SpritePartCommand command;
} __attribute__((packed)) Row_819A1654_Blob12;

typedef struct EntityEffectSequenceBody {
    EntityEffectSequencePrefix prefix;
    u8 pad78[0x12];
    Row_819A1654_Blob12 sprite_source[2];
} EntityEffectSequenceBody;

typedef struct Row_819A1654_Task {
    ObjectNodeHeader header;
    EntityEffectSequenceBody effect;
} Row_819A1654_Task;

typedef struct Row_819A1654_Entity {
    u8 pad0[4];
    u16 *header;
    u8 type;
    u8 pad9;
    s16 state;
    u8 padC[0x20];
    s16 x;
    s16 y;
    s16 z;
    s16 timer;
    u8 pad34[2];
    s16 point_index;
    u8 pad38[2];
    u16 age;
    u8 pad3C[0x18];
    s16 path[24];
    s16 base[3];
} Row_819A1654_Entity;

typedef struct Row_819A1654_World {
    u8 pad0[0x2A];
    u16 angle;
    u8 pad2C[0x34];
    void *focus;
    u8 pad64[0x32];
    s16 field96;
    u8 pad98[0xE];
    u16 fieldA6;
    u8 fieldA8;
    u8 padA9[0x4B];
    s32 fieldF4;
} Row_819A1654_World;

typedef struct Row_819A1654_GlobalState {
    s32 flags;
    s32 pad4;
    Row_819A1654_World *world;
} Row_819A1654_GlobalState;

typedef struct Row_819A1654_LookupGlobal {
    u8 pad0[6];
    s16 field6;
    void *found;
    u8 padC[8];
    u16 flags;
} Row_819A1654_LookupGlobal;

typedef struct Row_819A1654_ControlGlobal {
    u8 pad0[0xA];
    u16 count;
    s32 active;
} Row_819A1654_ControlGlobal;

typedef struct Row_819A1654_Point {
    s16 x;
    u16 y;
} Row_819A1654_Point;

typedef struct Row_819A1654_PointTable {
    Row_819A1654_Point point[8];
} Row_819A1654_PointTable;


typedef struct Row_819A1654_Blob8 {
    u8 bytes[8];
} __attribute__((packed)) Row_819A1654_Blob8;

typedef struct Row_819A1654_Blob24 {
    Row_819A1654_Blob12 entries[2];
} __attribute__((packed)) Row_819A1654_Blob24;

/* Advance the entity effect sequence, spawning particles and trails before cleanup. */
void advance_sprite_animation_and_textures(void *);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
void select_record_entry_and_value(void *state, void *entries, short index);
struct SpriteAttachmentEntry *get_sprite_attachment_vector(void *, void *, void *, s32);
s32 func_8003DF74(void *, void *, void *, s32);
s32 func_80069EF8(void);
s32 read_sound_mode_blocking_status(s32);
void D_80024C50(void *, void *, void *, s32, s32, s32);

extern const Row_819A1450_LocalTable D_80024034;
extern u8 D_800246F0[];
#include "dungeon/effect/sprite/directional_entries.h"
extern Row_819A1654_GlobalState D_800814A0[];
extern Row_819A1654_LookupGlobal reference_tile_object[];
extern s16 linked_effect_chain_count[6];
extern u16 D_80082E94;

extern const Row_819A1654_PointTable linked_effect_octant_offsets[1];
extern Row_819A1654_Blob12 D_80026180[];
extern Row_819A1654_Blob12 linked_effect_task_values[];
extern Row_819A1654_Blob24 D_80026198[];
void project_vertex_shaded_effect_quad(EntityEffectSequencePrefix *quad, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias);
s32 draw_linked_effect_chain(EntityEffectSequencePrefix *state, ObjectPosition *position, SpriteFrameState *appearance);
void update_effect_countdown_fields(EntityEffectSequenceBody *object);
void fade_moving_effect(RotatingDirectionalSpriteBody *effect, ObjectPosition *motion, SpriteFrameState *primitive);
void fade_gray_sprite_by_remaining_life(Row_819A0FC0_S_func_819A0FC0_0 *fadeState, void *unused, Row_819A0FC0_S_func_819A0FC0_1 *primitive);
void fade_quad_vertex_colors(EntityEffectSequencePrefix *fade);
void interpolate_quad_geometry_and_fade_colors(EntityEffectSequencePrefix *effect);
void fade_and_rotate_effect_sprite(EntityEffectSequenceBody *effect, s32 unused, SpriteFrameState *primitive);
void rotate_and_fade_timed_sprite(EntityEffectSequencePrefix *work, ObjectPosition *unused, SpriteFrameState *obj);
void create_rotating_directional_sprite(Row_819A1450_S_819A1450_4 *source, ObjectPosition *unused_1, SpriteFrameState *unused_2, s16 offset_x, s16 offset_y,
                   s16 offset_z);
void advance_entity_effect_sequence(Row_819A1654_Entity *entity, ObjectPosition *saved_context, SpriteFrameState *saved_data);
extern s16 linked_effect_update_flag[];
#endif
