#ifndef DUNGEON_OVL_193C848_H
#define DUNGEON_OVL_193C848_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity_height_offsets.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
typedef struct Row_8191C848_S_8191C848_0_pre {
    u16 unk_00;
} Row_8191C848_S_8191C848_0_pre;   /* the 0x2 bytes before arg0 in func_80024048, addressed as arg0[-1] */

typedef struct Row_8191C848_S_8191C848_0 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
} Row_8191C848_S_8191C848_0;   /* arg0 in func_80024048 */

typedef struct Row_8191C848_S_8191C848_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_8191C848_S_8191C848_1;   /* temp_v1 in func_80024048 */

typedef struct Row_8191C848_S_8191C848_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_8191C848_S_8191C848_3;   /* arg1 in func_80024048 */

/* cfail-repair: tf7-phase1-cache-v3 */
                             /* extern */
                             /* extern */

/* Advance the motion counter, update status flags, and move the position. */
#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((u8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_8191C938_CopyBlock {
    s32 word[6];
} Row_8191C938_CopyBlock;

typedef struct Row_8191C938_S_8191C938_0 {
    u8 pad_00[0x8];
    Row_8191C938_CopyBlock * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} Row_8191C938_S_8191C938_0;   /* temp_v0 in func_80024138 */

typedef struct Row_8191C938_S_8191C938_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} Row_8191C938_S_8191C938_1;   /* temp_s0 in func_80024138 */

typedef struct Row_8191C938_S_8191C938_3 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x8];
    Row_8191C938_CopyBlock * unk_20;
} Row_8191C938_S_8191C938_3;   /* arg0 in func_80024138 */

typedef struct Row_8191C938_S_8191C938_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} Row_8191C938_S_8191C938_4;   /* temp_a0 in func_80024138 */

/* Allocate and initialize an object with randomized state and data copied from its source. */
typedef struct Row_8191CA88_S_8191CA88_0_pre {
    u16 unk_00;
} Row_8191CA88_S_8191CA88_0_pre;   /* the 0x2 bytes before object in func_80024288, addressed as object[-1] */

typedef struct Row_8191CA88_S_8191CA88_0 {
    void * unk_00;
    u8 pad_04[0xA];
    union { s16 s; u16 u; u16 p; } unk_0E;   /* accessed as both */
    union { u16 s; u16 u; s16 p; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
} Row_8191CA88_S_8191CA88_0;   /* object in func_80024288 */

typedef struct Row_8191CA88_S_8191CA88_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_8191CA88_S_8191CA88_1;   /* inner in func_80024288 */

typedef struct Row_8191CA88_S_8191CA88_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} Row_8191CA88_S_8191CA88_2;   /* arg2 in func_80024288 */

typedef struct Row_8191CA88_S_8191CA88_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8191CA88_S_8191CA88_3;   /* motion in func_80024288 */

typedef struct Row_8191CA88_S_8191CA88_4 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} Row_8191CA88_S_8191CA88_4;   /* global_base in func_80024288 */

/* Updates object motion and timers through movement, waiting, falling, and completion states. */
typedef struct Row_8191CBCC_S_8191CBCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} Row_8191CBCC_S_8191CBCC_0;   /* temp_v0 in func_800243CC */

typedef struct Row_8191CBCC_S_8191CBCC_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    union { u16 s; s16 u; } unk_14;   /* accessed as both */
    s16 unk_16;
} Row_8191CBCC_S_8191CBCC_1;   /* temp_s2 in func_800243CC */

typedef struct Row_8191CBCC_S_8191CBCC_2 {
    u8 pad_00[0x10];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u16 unk_12;
} Row_8191CBCC_S_8191CBCC_2;   /* held_arg0 in func_800243CC */

typedef struct Row_8191CBCC_S_8191CBCC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} Row_8191CBCC_S_8191CBCC_4;   /* copy_dst in func_800243CC */

           /* extern */
                             /* extern */
typedef struct { s32 w0, w1, w2, w3, w4, w5; } Blk24;

/* Creates an effect with randomized appearance and a depth-adjusted copy of the source transform. */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Row_8191CD78_Coord;

typedef struct Row_8191CD78_S_func_80024578_1 {
    void *caster;
    void *launch_flags;
    u8 pad_08[0x1];
    u8 variant;
    union {
        s16 s16;
        u16 u16;
    } phase;
    u8 pad_0C[0x2];
    u16 direction;
    union {
        s16 s16;
        u16 u16;
    } timer;
    s16 unk_12;
    union {
        s16 s16;
        u16 u16;
    } child_updates;
    union {
        s16 s16;
        u16 u16;
    } target_ground_height;
    u16 saved_facing;
    union {
        s16 s16;
        u16 u16;
    } added_property_flag;
    void *target;
    void *target_position;
    void *target_sprite;
    union {
        s32 s32;
        void *ptr;
    } saved_z;
} Row_8191CD78_S_func_80024578_1;

typedef struct Row_8191CD78_S_func_80024578_2 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts_02;
    } x;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts_06;
    } y;
    union {
        s32 s32;
        void *ptr;
        struct {
            u8 pad_08[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0A;
        } parts_0A;
    } z;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
} Row_8191CD78_S_func_80024578_2;

typedef struct Row_8191CD78_S_func_80024578_3 {
    u8 pad_00[0x13];
    u8 species;
    s32 property_flags;
    u8 pad_18[0x12];
    u16 facing;
    u8 pad_2C[0x34];
    void *target;
    u8 pad_64[0x24];
    union {
        s16 s16;
        u16 u16;
    } ground_height;
} Row_8191CD78_S_func_80024578_3;

typedef struct Row_8191CD78_S_func_80024578_4 {
    u8 pad_00[0xC];
    s32 color;
    u8 pad_10[0xA];
    u16 angle_z;
} Row_8191CD78_S_func_80024578_4;

typedef struct Row_8191CD78_S_func_80024578_5 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts_02;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts_06;
    } unk_04;
    union {
        s32 s32;
        void *ptr;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A;
        } parts_0A;
    } unk_08;
    void *unk_0C;
} Row_8191CD78_S_func_80024578_5;

typedef struct Row_8191CD78_S_func_80024578_6 {
    u8 pad_00[0x8];
    void *source;
    u8 pad_0C[0x8];
    u16 flags;
    u8 pad_16[0xE];
    u8 tile_x;
    u8 tile_y;
} Row_8191CD78_S_func_80024578_6;

typedef struct Row_8191CD78_S_func_80024578_7 {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
} Row_8191CD78_S_func_80024578_7;

typedef struct Row_8191CD78_S_func_80024578_8 {
    u16 flags;
} Row_8191CD78_S_func_80024578_8;

typedef struct Row_8191CD78_S_func_80024578_9 {
    u8 pad_00[0x18];
    union {
        s16 s16;
        u16 u16;
    } unk_18;
} Row_8191CD78_S_func_80024578_9;

typedef struct Row_8191CD78_S_func_80024578_10 {
    u8 unk_00;
} Row_8191CD78_S_func_80024578_10;

typedef struct Row_8191CD78_S_func_80024578_11 {
    u8 pad_00[0x8];
    void *position;
    void *sprite;
} Row_8191CD78_S_func_80024578_11;

typedef struct Row_8191CD78_S_func_80024578_12 {
    u16 flags;
} Row_8191CD78_S_func_80024578_12;

typedef struct Row_8191CD78_S_func_80024578_13 {
    u8 pad_00[0x18];
    s16 unk_18[3];
} Row_8191CD78_S_func_80024578_13;

#define DELTA(i) (((Row_8191CD78_S_func_80024578_13 *)scratch)->unk_18[(i)])

/* Updates effect movement, target spinning, and completion across animation states. */
s32 rsin();
s32 rcos();
void select_record_entry_and_value(void *state, void *entries, short index);
s32 register_node(void *, void *);
s32 func_8004491C(void *, void *);
s32 rand(void);
int abs(int);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
s32 check_layer_offset_height(s32, s32, s16, s32);
s16 sample_terrain_surface_height(s32, s32, s16);
void initialize_timed_motion_step(u16, u16);
s32 read_sound_mode_blocking_status(s32);
void drain_audio_commands_and_service_channels(void);
void apply_attack_power_and_element_effects(void *, s32, u8, s32, s32, void *, s32);
void play_sound_if_enabled(s32);
extern u8 D_80024048[];
extern u8 homing_particle_sprite_entries[];
extern M2C_UNK D_80024288;
extern M2C_UNK D_80024F74;
extern s32 clipped_sprite_renderer_address();
void move_sprite_in_radial_direction(void *motion, Row_8191C848_S_8191C848_3 *position, SpriteFrameState *status);
void *create_randomized_source_effect(Row_8191C938_S_8191C938_3 *source);
void advance_timed_effect_motion(void *object, Row_8191CA88_S_8191CA88_3 *motion, Row_8191CA88_S_8191CA88_2 *effect);
void * create_scaled_rotating_effect(void *params_input, void *transform_input);
void update_actor_effect_sequence(Row_8191CD78_S_func_80024578_1 *effect, Row_8191CD78_S_func_80024578_2 *position, void *render_data);
#endif
