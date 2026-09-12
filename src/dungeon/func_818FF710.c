#include "common.h"
#include "m2c_compat.h"

typedef struct { u8 bytes[8]; } Packed8 __attribute__((packed));
typedef struct { u8 bytes[12]; } Packed12 __attribute__((packed));
typedef struct { u8 bytes[32]; } Packed32 __attribute__((packed));
typedef union {
    Packed8 packed;
    s16 half[6];
} Local28;
typedef union {
    Packed32 packed;
    struct {
        s16 first;
        u16 second;
    } pair[8];
} Local38;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024058[];
M2C_UNK func_8002407C();          /* extern */
M2C_UNK func_800244CC(); /* extern */
M2C_UNK func_80024DB8(); /* extern */
extern void func_80025158(void) __attribute__((noreturn));
extern void func_800252B4(void) __attribute__((noreturn));
extern void func_80025DF4(void) __attribute__((noreturn));
s32 func_8003DE58();     /* extern */
void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s16 func_80066460(); /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B8FC8(); /* extern */
extern Packed8 D_80024028;
extern Packed32 D_80024038;
extern M2C_UNK D_800245EC;
extern M2C_UNK D_800246F8;
extern M2C_UNK D_80024780;
extern M2C_UNK D_8002499C;
extern Packed12 D_80025E28;
extern Packed12 D_80025E34;
extern Packed12 D_80025E40;
extern Packed12 D_80025E58;
extern Packed12 D_80025E70;
extern M2C_UNK D_80025E80;
extern M2C_UNK D_80045340;
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];
extern u8 D_800E3D68;


typedef struct S_818FF710_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_818FF710_0;   /* temp_s0 in func_818FF710 */

typedef struct S_818FF710_1 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_1;   /* arg2 in func_818FF710 */

typedef struct S_818FF710_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818FF710_2_pre;   /* the 0x14 bytes before temp_s7 in func_818FF710, addressed as temp_s7[-1] */

typedef struct S_818FF710_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_818FF710_2;   /* temp_s7 in func_818FF710 */

typedef struct S_818FF710_3 {
    s16 unk_00;
} S_818FF710_3;   /* &D_80025E80 in func_818FF710 */

typedef struct S_818FF710_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818FF710_4;   /* temp_a1 in func_818FF710 */

typedef struct S_818FF710_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    union { s32 i; void * p; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_818FF710_5;   /* arg1 in func_818FF710 */

typedef struct S_818FF710_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818FF710_6;   /* temp_s2 in func_818FF710 */

typedef struct S_818FF710_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818FF710_7_pre;   /* the 0x18 bytes before temp_v1_3 in func_818FF710, addressed as temp_v1_3[-1] */

typedef struct S_818FF710_7 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_7;   /* temp_v1_3 in func_818FF710 */

typedef struct S_818FF710_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818FF710_8;   /* temp_a3_case1 in func_818FF710 */

typedef struct S_818FF710_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_818FF710_9;   /* temp_a0 in func_818FF710 */

typedef struct S_818FF710_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818FF710_10_pre;   /* the 0x14 bytes before temp_v1_9 in func_818FF710, addressed as temp_v1_9[-1] */

typedef struct S_818FF710_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_10;   /* temp_v1_9 in func_818FF710 */

typedef struct S_818FF710_11 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_11;   /* temp_v1_10 in func_818FF710 */

typedef struct S_818FF710_12 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_12;   /* temp_a0_2 in func_818FF710 */

typedef struct S_818FF710_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_818FF710_13;   /* temp_a3 in func_818FF710 */

typedef struct S_818FF710_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1E];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
    void * unk_40;
} S_818FF710_14;   /* temp_s1 in func_818FF710 */

typedef struct S_818FF710_15 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} S_818FF710_15;   /* temp_s0_2 in func_818FF710 */

typedef struct S_818FF710_16 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_16;   /* temp_v1_12 in func_818FF710 */

typedef struct S_818FF710_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_17;   /* temp_a3_3 in func_818FF710 */

typedef struct S_818FF710_18 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_18;   /* temp_s0_4 in func_818FF710 */

typedef struct S_818FF710_19 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_19;   /* temp_v1_13 in func_818FF710 */

typedef struct S_818FF710_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_20;   /* temp_a3_4 in func_818FF710 */

typedef struct S_818FF710_21 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_21;   /* temp_s0_6 in func_818FF710 */

typedef struct S_818FF710_22 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_22;   /* temp_v1_14 in func_818FF710 */

typedef struct S_818FF710_23 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_23;   /* temp_a3_5 in func_818FF710 */

typedef struct S_818FF710_24 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_24;   /* temp_s0_8 in func_818FF710 */

typedef struct S_818FF710_25 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_25;   /* temp_v1_15 in func_818FF710 */

typedef struct S_818FF710_26 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_26;   /* temp_a3_6 in func_818FF710 */

typedef struct S_818FF710_27 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_27;   /* temp_v1_18 in func_818FF710 */

typedef struct S_818FF710_28 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_28;   /* temp_a0_3 in func_818FF710 */

typedef struct S_818FF710_29 {
    s32 unk_00;
} S_818FF710_29;   /* &D_800814A0 in func_818FF710 */

typedef struct S_818FF710_30 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_30;   /* ((S_818FF710_0 *)temp_s0)->unk_0C in func_818FF710 */

typedef struct S_818FF710_31_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818FF710_31_pre;   /* the 0x18 bytes before ((S_818FF710_2 *)temp_s7)->unk_60 in func_818FF710, addressed as ((S_818FF710_2 *)temp_s7)->unk_60[-1] */

typedef struct S_818FF710_31 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_31;   /* ((S_818FF710_2 *)temp_s7)->unk_60 in func_818FF710 */

typedef struct S_818FF710_32 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_32;   /* ((S_818FF710_15 *)temp_s0_2)->unk_08 in func_818FF710 */

typedef struct S_818FF710_33 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_33;   /* ((S_818FF710_18 *)temp_s0_4)->unk_08 in func_818FF710 */

/* Updates an effect's movement, particles, target effects, and cleanup state. */
void func_818FF710(void *effect, void *motion, void *sprite) {
    u16 offset[3];
    Local28 texture_rect;
    Local38 direction_steps;
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c8 };
    s32 spawn_tick;
    s32 state;
    s32 effect_active;
    void *follow_target;
    void *linked_target;
    s16 fade_tick;
    M2C_UNK red_tick;
    M2C_UNK green_tick;
    M2C_UNK blue_tick;
    s32 launch_particle;
    s32 impact_particle;
    s32 tile_distance;
    s32 parent_tile;
    register void *child_data ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s8 remaining_ticks;
    u16 impact_angle;
    u16 release_tick;
    u16 cleanup_tick;
    u16 flight_angle;
    u16 hit_angle;
    u16 hit_tick;
    u16 old_hit_angle;
    u16 old_impact_angle;
    u16 old_cleanup_tick;
    u16 parent_height;
    u16 old_flight_angle;
    u16 parent_flags;
    u16 launch_height;
    u8 flight_ticks;
    register s32 origin_tile ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 source_id;
    S_818FF710_9 *origin;
    S_818FF710_12 *hit_target;
    S_818FF710_28 *released_target;
    S_818FF710_4 *parent_sprite;
    register void *target_pos_or_step ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *linked_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *sprite_resource;
    register void *target_position ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *first_source_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *second_source_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *third_source_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *fourth_source_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_818FF710_0 *parent_object;
    S_818FF710_15 *first_sprite;
    S_818FF710_18 *second_sprite;
    register void *third_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *fourth_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_818FF710_14 *child_effect;
    S_818FF710_6 *parent_position;
    void *parent;
    void *third_object;
    register void *fourth_object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *first_object ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *second_object;
    S_818FF710_11 *target_hit_flags;
    S_818FF710_16 *first_position;
    S_818FF710_19 *second_position;
    S_818FF710_22 *third_position;
    S_818FF710_25 *fourth_position;
    S_818FF710_27 *target_release_flags;
    void *flight_target;
    void *impact_target;

    register void *motion_ptr ASM_REG("$19") = motion;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *sprite_ptr ASM_REG("$17") = sprite;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite_ptr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#define effect effect
#define motion motion_ptr
#define sprite sprite_ptr

    parent = (*(void **)((u8 *)effect + 0));
    texture_rect.packed = D_80024028;
    direction_steps.packed = D_80024038;
    state = (*(s16 *)((u8 *)effect + 0xA));
    parent_object = parent - 0x20;
    parent_position = parent_object->unk_08;
    if ((u32) state >= 9U) {
        goto done;
    }
    (void)state_labels; goto *D_80024058[(u32)(state)];
jt_c0:
    ((S_818FF710_1 *)sprite)->unk_0C.at00.v = 0x808080;
    (*(Packed12 *)((u8 *)effect + 0x96)) = D_80025E70;
    ((S_818FF710_1 *)sprite)->unk_08 = (void *) (effect + 0x96);
    parent_flags = ((S_818FF710_2 *)parent)->unk_2A;
    ((S_818FF710_3 *)(&D_80025E80))->unk_00 = 1;
    (*(s16 *)((u8 *)effect + 0x7E)) = (s16) ((parent_flags >> 9) & 7);
    (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
jt_c1:
    parent_sprite = parent_object->unk_0C;
    if (func_8003DE58(parent_sprite->unk_08, parent_sprite, &offset[0], 0) != 0) {
        goto set_launch_position;
    }
    if (!(((S_818FF710_30 *)(parent_object->unk_0C))->unk_14 & 0x8000)) {
        goto done;
    }
set_launch_position:
    ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) parent_position->unk_02;
    ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) parent_position->unk_06;
    parent_height = parent_position->unk_0A;
    ((S_818FF710_5 *)motion)->unk_08.at02.v = parent_height;
    if (!(((S_818FF710_30 *)(parent_object->unk_0C))->unk_14 & 0x8000)) {
        ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_00.at02.v + offset[0]);
        ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_04.at02.v + offset[1]);
        launch_height = (u16) (((S_818FF710_5 *)motion)->unk_08.at02.v + offset[2]);
        ASM_TAILSLOT_PIN(launch_height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80025158();
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    launch_height = (u16) (parent_height - 0x40);
    ((S_818FF710_5 *)motion)->unk_08.at02.v = launch_height;
    if ((*(u8 *)((u8 *)effect + 0x7A)) & 4) {
        goto check_launch;
    }
    func_8004491C(effect - 0x20, &D_80045340);
    ((S_818FF710_1 *)sprite)->unk_10 = 0x60;
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0x14;
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0x14;
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0x14;
    ((S_818FF710_1 *)sprite)->unk_1E = 0x1000;
    ((S_818FF710_1 *)sprite)->unk_1C = 0x1000;
    ((S_818FF710_1 *)sprite)->unk_14 = (u16) (((S_818FF710_1 *)sprite)->unk_14 | 0xC);
    (*(u8 *)((u8 *)effect + 0x7A)) = (u8) ((*(u8 *)((u8 *)effect + 0x7A)) | 4);
check_launch:
    if (!(*(*(u16 **)((u8 *)effect + 4)) & 0x80)) {
        goto done;
    }
    flight_target = ((S_818FF710_2 *)parent)->unk_60;
    if (flight_target == NULL) {
        goto set_untargeted_flight;
    }
    target_position = ((S_818FF710_7_pre *)flight_target)[-1].unk_00;
    (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_8 *)target_position)->unk_0A - (D_800DDC40[((S_818FF710_7 *)flight_target)->unk_13] + 0x40));
    origin = ((S_818FF710_2_pre *)parent)[-1].unk_00;
    (*(s8 *)((u8 *)effect + 0xA2)) = (s8) (origin->unk_24 + D_8006CCD8[(*(s16 *)((u8 *)effect + 0x7E)) * 2]);
    (*(s8 *)((u8 *)effect + 0xA3)) = (s8) (origin->unk_25 + D_8006CCE8[(*(s16 *)((u8 *)effect + 0x7E)) * 2]);
    parent_tile = ((S_818FF710_2 *)parent)->unk_72;
    origin_tile = origin->unk_24;
    if (parent_tile != origin_tile) {
        tile_distance = parent_tile - origin_tile;
        goto check_distance_sign;
    }
    parent_tile = ((S_818FF710_2 *)parent)->unk_73;
    origin_tile = origin->unk_25;
    tile_distance = parent_tile - origin_tile;
check_distance_sign:
    if (tile_distance >= 0) {
        goto set_flight_duration;
    }
    tile_distance = 0 - tile_distance;
set_flight_duration:
    (*(s8 *)((u8 *)effect + 0x7B)) = (s8) ((tile_distance * 2) - 1);
    func_800252B4();
set_untargeted_flight:
    (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_2 *)parent)->unk_88 - 0x50);
    (*(s8 *)((u8 *)effect + 0x7B)) = 0x20;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    ((S_818FF710_5 *)motion)->unk_0C = (s32) (direction_steps.pair[(*(s16 *)((u8 *)effect + 0x7E))].first << 0x10);
    ((S_818FF710_5 *)motion)->unk_10.i = (s32) (direction_steps.pair[(*(s16 *)((u8 *)effect + 0x7E))].second << 0x10);
    ((S_818FF710_5 *)motion)->unk_14 = (s32) ((s32) (((*(s16 *)((u8 *)effect + 0x78)) << 0x10) - ((S_818FF710_5 *)motion)->unk_08.at00.v) / (s8) (*(s8 *)((u8 *)effect + 0x7B)));
    flight_ticks = (u8) (*(s8 *)((u8 *)effect + 0x7B));
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
    (*(s16 *)((u8 *)effect + 0x88)) = (s16) (s8) (u8) (*(s8 *)((u8 *)effect + 0x7B));
    (*(s16 *)((u8 *)effect + 0x8A)) = (s16) ((s8) flight_ticks * (s8) flight_ticks);
    func_80024DB8(effect, motion, sprite);
    func_80025DF4();
    return;
jt_c2:
    launch_particle = 0;
launch_particles:
    launch_particle += 1;
    {
        register void *particle_owner ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 particle_direction;
        s32 particle_color;
        register s32 particle_size ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 random_value;
        random_value = func_80069EF8();
        particle_owner = effect - 0x20;
        particle_color = 0x2020E0;
        ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        particle_size = (random_value & 0xFF) | 0x80;
        ASM_KEEP_NV(particle_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        particle_direction = (*(s16 *)((u8 *)effect + 0x7E));
        func_800244CC(particle_owner, particle_direction, particle_color, particle_size, 0, 0, 0);
    }
    if (launch_particle < 4) {
        goto launch_particles;
    }
    old_flight_angle = ((S_818FF710_1 *)sprite)->unk_1A;
    flight_angle = old_flight_angle + 0x190;
    ((S_818FF710_1 *)sprite)->unk_1A = flight_angle;
    if ((u32) (flight_angle & 0xFFFF) < 0x1001U) {
        goto update_flight_color;
    }
    ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_flight_angle - 0xE70);
update_flight_color:
    red_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = (s8) (((s32) (red_tick * red_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
    green_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = (s8) (((s32) (green_tick * green_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
    blue_tick = ((*(s16 *)((u8 *)effect + 0x88)) - (*(s8 *)((u8 *)effect + 0x7B))) + 1;
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = (s8) (((s32) (blue_tick * blue_tick * 0x6C) / (s16) (*(s16 *)((u8 *)effect + 0x8A))) + 0x14);
    if ((func_800A4778(((S_818FF710_5 *)motion)->unk_00.at02.v, ((S_818FF710_5 *)motion)->unk_04.at02.v, (s16) ((S_818FF710_5 *)motion)->unk_08.at02.v, ((S_818FF710_2 *)parent)->unk_60) << 0x10) == 0) {
        goto advance_flight;
    }
    (*(s16 *)((u8 *)effect + 0xA)) = 8;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0;
    func_80025DF4();
    return;
advance_flight:
    remaining_ticks = (u8) (*(s8 *)((u8 *)effect + 0x7B)) - 1;
    (*(s8 *)((u8 *)effect + 0x7B)) = remaining_ticks;
    if ((remaining_ticks << 0x18) > 0) {
        goto move_effect;
    }
    if (((S_818FF710_2 *)parent)->unk_60 == NULL) {
        goto finish_untargeted_flight;
    }
    (*(s16 *)((u8 *)effect + 0xA)) = 3;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    func_800A56E0(0x300);
    impact_target = ((S_818FF710_2 *)parent)->unk_60;
    target_hit_flags = ((S_818FF710_10_pre *)impact_target)[-1].unk_00;
    if ((u32) (((S_818FF710_10 *)impact_target)->unk_13 - 0x33) < 4U) {
        goto snap_to_target;
    }
    target_hit_flags->unk_14 = (u16) (target_hit_flags->unk_14 | 0x800);
    hit_target = ((S_818FF710_2 *)parent)->unk_60;
    hit_target->unk_14 = (s32) (hit_target->unk_14 | 0x100000);
snap_to_target:
    target_pos_or_step = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) ((S_818FF710_13 *)target_pos_or_step)->unk_02;
    ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) ((S_818FF710_13 *)target_pos_or_step)->unk_06;
    ((S_818FF710_5 *)motion)->unk_08.at02.v = (u16) (*(s16 *)((u8 *)effect + 0x78));
    func_80024DB8(effect, motion, sprite, target_pos_or_step);
    func_80025DF4();
    return;
finish_untargeted_flight:
    (*(s16 *)((u8 *)effect + 0xA)) = 8;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0;
    func_80024DB8(effect, motion, sprite);
    func_80025DF4();
    return;
move_effect:
    target_pos_or_step = ((S_818FF710_5 *)motion)->unk_10.p;
    ((S_818FF710_5 *)motion)->unk_00.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_00.at00.v + ((S_818FF710_5 *)motion)->unk_0C);
    ((S_818FF710_5 *)motion)->unk_04.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_04.at00.v + (s32) target_pos_or_step);
    ((S_818FF710_5 *)motion)->unk_08.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_08.at00.v + ((S_818FF710_5 *)motion)->unk_14);
    func_80024DB8(effect, motion, sprite, target_pos_or_step);
    func_80025DF4();
    return;
jt_c3: {
    s32 impact_tick;
    s32 rect_value;
    register s16 *rect_start ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s16 *rect_end ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *texture_start ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 *texture_end ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 rect_right;
    s32 rect_height;
    s32 rect_left;
    old_hit_angle = ((S_818FF710_1 *)sprite)->unk_1A;
    hit_angle = old_hit_angle + 0x190;
    ((S_818FF710_1 *)sprite)->unk_1A = hit_angle;
    if ((u32) (hit_angle & 0xFFFF) < 0x1001U) {
        goto update_hit;
    }
    ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_hit_angle - 0xE70);
update_hit:
    func_80024DB8(effect, motion, sprite);
    hit_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = hit_tick;
    if ((s16) hit_tick != 1) {
        goto check_spawn_tick;
    }
    rect_start = &texture_rect.half[0];
    texture_start = rect_start;
    rect_end = &texture_rect.half[4];
    texture_end = rect_end;
    ASM_SET(rect_left);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    rect_left = 0x340;
    rect_value = 0x154;
    texture_rect.half[1] = (s16) rect_value;
    rect_value = 0x60;
    texture_rect.half[2] = (s16) rect_value;
    rect_height = 0x54;
    rect_right = 0x370;
    texture_rect.half[0] = (s16) rect_left;
    texture_rect.half[3] = (s16) rect_height;
    texture_rect.half[4] = (s16) rect_right;
    texture_rect.half[5] = (s16) 0x19A;
    func_800B8FC8(((S_818FF710_2 *)parent)->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
    texture_start = rect_start;
    texture_end = rect_end;
    ASM_KEEP_NV(texture_start);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(texture_end);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    rect_value = 0x1A8;
    texture_rect.half[1] = (s16) rect_value;
    rect_value = 0x60;
    texture_rect.half[2] = (s16) rect_value;
    texture_rect.half[0] = (s16) rect_left;
    texture_rect.half[3] = (s16) rect_height;
    texture_rect.half[4] = (s16) rect_right;
    rect_value = 0x1EF;
    texture_rect.half[5] = (s16) rect_value;
    func_800B8FC8(((S_818FF710_2 *)parent)->unk_60, texture_start, texture_end, 1, (s32) (s16) hit_tick);
check_spawn_tick:
    impact_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (impact_tick != 4) {
        goto done;
    }
    first_object = func_8003FC64(0x212);
    child_effect = first_object + 0x20;
    if (first_object == NULL) {
        goto spawn_second;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)first_object + 0x10)) = &D_800246F8;
    func_8004491C(first_object, &D_80045340);
    first_sprite = (*(void **)((u8 *)first_object + 0xC));
    first_sprite->unk_06 = 0;
    first_sprite->unk_14 |= 0xC;
    first_sprite->unk_10 = 0x40;
    sprite_flags = first_sprite->unk_14;
    first_sprite->unk_14 = (u16) (sprite_flags | 0x80);
    first_position = (*(void **)((u8 *)first_object + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    first_source_pos = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    first_position->unk_00 = (s32) ((S_818FF710_17 *)first_source_pos)->unk_00;
    first_position->unk_04 = (s32) ((S_818FF710_17 *)first_source_pos)->unk_04;
    first_position->unk_08 = (s32) ((S_818FF710_17 *)first_source_pos)->unk_08;
    first_sprite = (*(void **)((u8 *)first_object + 0xC));
    first_sprite->unk_1C = 0x1004;
    first_sprite->unk_1E = 0x1004;
    first_sprite->unk_22 = (s16) ((s32) (0 - D_800DDC40[((S_818FF710_31 *)(((S_818FF710_2 *)parent)->unk_60))->unk_13]) / 2);
    first_sprite->unk_0E = 0x80;
    first_sprite->unk_0D = 0x80;
    first_sprite->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)first_object + 0x40)) = D_80025E34;
    first_sprite->unk_08 = (void *) (first_object + 0x40);
    ((S_818FF710_32 *)(first_sprite->unk_08))->unk_04 = func_80066460(2, 2, 0x340, 0x154);
spawn_second:
    second_object = func_8003FC64(0x212);
    child_effect = second_object + 0x20;
    if (second_object == NULL) {
        goto spawn_third;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)second_object + 0x10)) = &D_80024780;
    func_8004491C(second_object, &D_80045340);
    second_sprite = (*(void **)((u8 *)second_object + 0xC));
    second_sprite->unk_14 &= 0xFFF3;
    second_sprite->unk_10 = 0x20;
    second_sprite->unk_14 |= 0x80;
    child_effect->unk_2C = parent;
    follow_target = ((S_818FF710_2 *)parent)->unk_60;
    child_effect->unk_34 = effect;
    child_effect->unk_30 = follow_target;
    second_sprite->unk_06 = 0;
    second_position = (*(void **)((u8 *)second_object + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    second_source_pos = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    second_position->unk_00 = (s32) ((S_818FF710_20 *)second_source_pos)->unk_00;
    second_position->unk_04 = (s32) ((S_818FF710_20 *)second_source_pos)->unk_04;
    second_position->unk_08 = (s32) ((S_818FF710_20 *)second_source_pos)->unk_08;
    second_sprite = (*(void **)((u8 *)second_object + 0xC));
    second_sprite->unk_1E = 0x1000;
    second_sprite->unk_1C = 0x1000;
    second_sprite->unk_0E = 0x80;
    second_sprite->unk_0D = 0x80;
    second_sprite->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)second_object + 0x40)) = D_80025E40;
    second_sprite->unk_08 = (void *) (second_object + 0x40);
    ((S_818FF710_33 *)(second_sprite->unk_08))->unk_04 = func_80066460(2, 1, 0x340, 0x1A8);
spawn_third:
    third_object = func_8003FC64(0x212);
    child_effect = third_object + 0x20;
    if (third_object == NULL) {
        goto spawn_fourth;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)third_object + 0x10)) = &D_800245EC;
    func_8004491C(third_object, &D_80045340);
    third_sprite = (*(void **)((u8 *)third_object + 0xC));
    ((S_818FF710_21 *)third_sprite)->unk_06 = 0;
    ((S_818FF710_21 *)third_sprite)->unk_14 &= 0xFFF3;
    ((S_818FF710_21 *)third_sprite)->unk_10 = 0x20;
    sprite_flags = ((S_818FF710_21 *)third_sprite)->unk_14;
    ((S_818FF710_21 *)third_sprite)->unk_14 = (u16) (sprite_flags | 0x80);
    third_position = (*(void **)((u8 *)third_object + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    third_source_pos = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    third_position->unk_00 = (s32) ((S_818FF710_23 *)third_source_pos)->unk_00;
    third_position->unk_04 = (s32) ((S_818FF710_23 *)third_source_pos)->unk_04;
    third_position->unk_08 = (s32) ((S_818FF710_23 *)third_source_pos)->unk_08;
    third_sprite = (*(void **)((u8 *)third_object + 0xC));
    ((S_818FF710_21 *)third_sprite)->unk_0E = 0x80;
    ((S_818FF710_21 *)third_sprite)->unk_0D = 0x80;
    ((S_818FF710_21 *)third_sprite)->unk_0C = 0x80;
    ((S_818FF710_21 *)third_sprite)->unk_1E = 0;
    ((S_818FF710_21 *)third_sprite)->unk_1C = 0;
    (*(Packed12 *)((u8 *)third_object + 0x40)) = D_80025E58;
    ((S_818FF710_21 *)third_sprite)->unk_08 = (void *) (third_object + 0x40);
spawn_fourth:
    fourth_object = func_8003FC64(0x212);
    child_effect = fourth_object + 0x20;
    if (fourth_object == NULL) {
        goto finish_spawn;
    }
    linked_object = fourth_object;
    sprite_resource = (void *) &D_80045340;
    ASM_KEEP_NV(sprite_resource);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    child_effect->unk_2C = parent;
    linked_target = ((S_818FF710_2 *)parent)->unk_60;
    child_data = (void *) (first_object + 0x20);
    child_effect->unk_38 = child_data;
    child_data = (void *) (third_object + 0x20);
    child_effect->unk_3C = child_data;
    child_data = (void *) (second_object + 0x20);
    child_effect->unk_40 = child_data;
    child_effect->unk_34 = effect;
    child_effect->unk_30 = linked_target;
    (*(M2C_UNK **)((u8 *)fourth_object + 0x10)) = &D_8002499C;
    func_8004491C(linked_object, sprite_resource);
    fourth_sprite = (*(void **)((u8 *)fourth_object + 0xC));
    ((S_818FF710_24 *)fourth_sprite)->unk_06 = 0;
    ((S_818FF710_24 *)fourth_sprite)->unk_14 |= 0xC;
    ((S_818FF710_24 *)fourth_sprite)->unk_10 = 0x20;
    sprite_flags = ((S_818FF710_24 *)fourth_sprite)->unk_14;
    ((S_818FF710_24 *)fourth_sprite)->unk_14 = (u16) (sprite_flags | 0x80);
    fourth_position = (*(void **)((u8 *)fourth_object + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    fourth_source_pos = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    fourth_position->unk_00 = (s32) ((S_818FF710_26 *)fourth_source_pos)->unk_00;
    fourth_position->unk_04 = (s32) ((S_818FF710_26 *)fourth_source_pos)->unk_04;
    fourth_position->unk_08 = (s32) ((S_818FF710_26 *)fourth_source_pos)->unk_08;
    fourth_sprite = (*(void **)((u8 *)fourth_object + 0xC));
    ((S_818FF710_24 *)fourth_sprite)->unk_1E = 0x1000;
    ((S_818FF710_24 *)fourth_sprite)->unk_1C = 0x1000;
    ((S_818FF710_24 *)fourth_sprite)->unk_0E = 0x80;
    ((S_818FF710_24 *)fourth_sprite)->unk_0D = 0x80;
    ((S_818FF710_24 *)fourth_sprite)->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)fourth_object + 0x40)) = D_80025E28;
    ((S_818FF710_24 *)fourth_sprite)->unk_08 = (void *) (fourth_object + 0x40);
    ASM_KEEP(fourth_object);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
finish_spawn:
    spawn_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (spawn_tick != impact_tick) {
        goto done;
    }
    (*(s16 *)((u8 *)effect + 0xA)) = spawn_tick;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    (*(s16 *)((u8 *)effect + 0x90)) = 0;
    func_80025DF4();
    return;
}
jt_c4:
    impact_particle = 0;
    (*(u16 *)((u8 *)effect + 0x82)) = (u16) ((*(u16 *)((u8 *)effect + 0x82)) + 1);
impact_particles:
    impact_particle += 1;
    {
        register void *particle_owner ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 particle_direction;
        s32 particle_color;
        register s32 particle_size ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 random_value;
        random_value = func_80069EF8();
        particle_owner = effect - 0x20;
        particle_color = 0x2020E0;
        ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        particle_size = (random_value & 0xFF) | 0x80;
        ASM_KEEP_NV(particle_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        particle_direction = (*(s16 *)((u8 *)effect + 0x7E));
        func_800244CC(particle_owner, particle_direction, particle_color, particle_size, 0, 0, 0);
    }
    if (impact_particle < 3) {
        goto impact_particles;
    }
    old_impact_angle = ((S_818FF710_1 *)sprite)->unk_1A;
    impact_angle = old_impact_angle + 0x190;
    ((S_818FF710_1 *)sprite)->unk_1A = impact_angle;
    if ((u32) (impact_angle & 0xFFFF) < 0x1001U) {
        goto fade_impact;
    }
    ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_impact_angle - 0xE70);
fade_impact:
    fade_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (fade_tick < 0x51) {
        goto check_impact_duration;
    }
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = (s8) (((0x64 - fade_tick) << 7) / 20);
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
check_impact_duration:
    func_80024DB8(effect, motion, sprite);
    if ((s16) (*(u16 *)((u8 *)effect + 0x82)) >= 0x64) {
        goto next_state;
    }
    func_80025DF4();
    return;
jt_c5:
    if ((*(s16 *)((u8 *)effect + 0x90)) == 0) {
        goto done;
    }
    source_id = 0xFF;
    if (D_800E3D68 == 0xFF) {
        goto apply_target_effect;
    }
    source_id = (*(u8 *)((u8 *)effect + 9));
apply_target_effect:
    func_8002407C(((S_818FF710_2 *)parent)->unk_60, source_id, parent);
next_state:
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
    func_80025DF4();
    return;
jt_c6:
    release_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = release_tick;
    if ((s16) release_tick < 0x1F) {
        goto done;
    }
    target_release_flags = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_04;
    target_release_flags->unk_14 = (u16) (target_release_flags->unk_14 & 0xF7FF);
    released_target = ((S_818FF710_2 *)parent)->unk_60;
    released_target->unk_14 = (s32) (released_target->unk_14 & 0xFFEFFFFF);
    (*(s16 *)((u8 *)effect + 0xA)) = 8;
    (*(u16 *)((u8 *)effect + 0x82)) = 0x1EU;
    func_80025DF4();
    return;
jt_c8:
    old_cleanup_tick = (*(u16 *)((u8 *)effect + 0x82));
    cleanup_tick = old_cleanup_tick + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = cleanup_tick;
    if ((s16) cleanup_tick < 0x1F) {
        goto done;
    }
    effect_active = (s32) ((S_818FF710_3 *)(&D_80025E80))->unk_00;
    (*(u16 *)((u8 *)effect + 0x82)) = old_cleanup_tick;
    if (effect_active != 0) {
        goto clear_active;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_818FF710_29 *)(&D_800814A0))->unk_00 | 0x8000);
    func_80025DF4();
    return;
clear_active:
    (*(s16 *)&D_80025E80) = 0;
done:
    return;
}
