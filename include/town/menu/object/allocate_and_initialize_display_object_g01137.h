#ifndef TOWN_MENU_OBJECT_ALLOCATE_AND_INITIALIZE_DISPLAY_OBJECT_G01137_H
#define TOWN_MENU_OBJECT_ALLOCATE_AND_INITIALIZE_DISPLAY_OBJECT_G01137_H
/* Allocate and initialize display object. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01137 - CL:town/func_800A48A0. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/vector.h"

typedef struct S_800A2000_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800A2000_0;

/* obj in allocate_and_initialize_display_object */
typedef struct S_800A2000_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
} S_800A2000_1;

typedef struct Func800A4A20Object {
    void (*callback)(void);
    u8 pad04[0x3c];
    u8 *state;
} Func800A4A20Object;

typedef struct S_800A21EC_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800A21EC_0;

/* arg2 in initialize_directional_object_state */
typedef struct S_800A21EC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_1;

/* arg1 in initialize_directional_object_state */
typedef struct S_800A21EC_2 {
    s32 * unk_00;
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A21EC_2;

struct Func800A4B70Output;

struct Func800A4B70Object;

typedef struct Func800A4B70Inner {
    u8 pad_00[0x6e];
    u16 value;
} Func800A4B70Inner;

typedef struct Func800A4B70Object {
    u8 pad_00[0x10];
    Func800A4B70Inner *inner;
    u8 pad_14[0x0c];
    s16 flag;
} Func800A4B70Object;

typedef struct Func800A4B70Output {
    u8 pad_00[0x1a];
    s16 value;
} Func800A4B70Output;

/* payload in allocate_and_initialize_display_object */
extern void *allocate_list_node();
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;
/* arg0 in initialize_directional_object_state */
/* ((S_800A21EC_2 *)arg0)->unk_14 in initialize_directional_object_state */
extern s32 register_node();
extern u8 lit_mesh_renderer_address[];
extern s32 D_800A2338;
extern s32 D_800A23D0;

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
void *allocate_and_initialize_display_object(s32 object_key, s32 payload_value, s32 payload_param, s32 payload_halfword, s32 object_param, s32 object_value);
s32 create_objects_descending_by_count(s32 object_key, s32 payload_value, s32 payload_param, s32 count);
void update_menu_node_or_retire_on_zero_state(Func800A4A20Object *object);
s32 initialize_directional_object_state(void *object, S_800A21EC_1 *placement, S_800A21EC_0 *state);
void copy_signed_inner_value_by_flag(Func800A4B70Object *object, s32 unused, Func800A4B70Output *out);
void *create_object_with_shared_data(s32 input_first, s32 input_second, s32 input_third, s32 input_fourth);

#endif
