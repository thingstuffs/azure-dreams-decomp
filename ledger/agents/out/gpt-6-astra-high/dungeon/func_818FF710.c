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

/* Updates a traveling effect, its target impact visuals, and cleanup state. */
void func_818FF710(void *effect, void *motion, void *sprite) {
    u16 offset[3];
    Local28 texture_rects;
    Local38 direction_steps;
    static void *const state_labels[] = { &&state_init, &&state_launch, &&state_flight, &&state_impact, &&state_burst, &&state_apply, &&state_release, &&state_finish };
    s32 spawn_tick;
    s32 state;
    s32 effect_active;
    void *target;
    void *linked_target;
    s16 fade_tick;
    M2C_UNK red_tick;
    M2C_UNK green_tick;
    M2C_UNK blue_tick;
    s32 trail_count;
    s32 burst_count;
    s32 tile_distance;
    s32 parent_tile;
    register void *child_data ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s8 remaining_ticks;
    u16 burst_angle;
    u16 release_tick;
    u16 finish_tick;
    u16 flight_angle;
    u16 impact_angle;
    u16 impact_tick;
    u16 old_impact_angle;
    u16 old_burst_angle;
    u16 old_finish_tick;
    u16 parent_z;
    u16 old_flight_angle;
    u16 parent_flags;
    u16 start_z;
    u8 flight_ticks;
    register s32 origin_tile ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 owner_id;
    S_818FF710_9 *origin;
    S_818FF710_12 *hit_target;
    S_818FF710_28 *released_target;
    S_818FF710_4 *parent_sprite;
    register void *motion_aux ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *controller_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *sprite_setup;
    register void *target_position ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *impact_origin ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *linked_origin ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *burst_origin ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *controller_origin ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_818FF710_0 *parent_obj;
    S_818FF710_15 *impact_sprite;
    S_818FF710_18 *linked_sprite;
    register void *burst_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *controller_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_818FF710_14 *child_effect;
    S_818FF710_6 *parent_position;
    void *parent;
    void *burst_obj;
    register void *control_obj ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *impact_obj ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *linked_obj;
    S_818FF710_11 *hit_position;
    S_818FF710_16 *impact_position;
    S_818FF710_19 *linked_position;
    S_818FF710_22 *burst_position;
    S_818FF710_25 *control_position;
    S_818FF710_27 *target_sprite;
    void *flight_target;
    void *impact_target;

    void *effect_ptr = effect;
    register void *motion_ptr ASM_REG("$19") = motion;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *sprite_ptr ASM_REG("$17") = sprite;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(effect_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite_ptr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#define effect effect_ptr
#define motion motion_ptr
#define sprite sprite_ptr

    parent = (*(void **)((u8 *)effect + 0));
    texture_rects.packed = D_80024028;
    direction_steps.packed = D_80024038;
    state = (*(s16 *)((u8 *)effect + 0xA));
    parent_obj = parent - 0x20;
    parent_position = parent_obj->unk_08;
    if ((u32) state >= 9U) {
        goto done;
    }
    (void)state_labels; goto *D_80024058[(u32)(state)];
state_init:
    ((S_818FF710_1 *)sprite)->unk_0C.at00.v = 0x808080;
    (*(Packed12 *)((u8 *)effect + 0x96)) = D_80025E70;
    ((S_818FF710_1 *)sprite)->unk_08 = (void *) (effect + 0x96);
    parent_flags = ((S_818FF710_2 *)parent)->unk_2A;
    ((S_818FF710_3 *)(&D_80025E80))->unk_00 = 1;
    (*(s16 *)((u8 *)effect + 0x7E)) = (s16) ((parent_flags >> 9) & 7);
    (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
state_launch:
    parent_sprite = parent_obj->unk_0C;
    if (func_8003DE58(parent_sprite->unk_08, parent_sprite, &offset[0], 0) != 0) {
        goto set_start_position;
    }
    if (!(((S_818FF710_30 *)(parent_obj->unk_0C))->unk_14 & 0x8000)) {
        goto done;
    }
set_start_position:
    ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) parent_position->unk_02;
    ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) parent_position->unk_06;
    parent_z = parent_position->unk_0A;
    ((S_818FF710_5 *)motion)->unk_08.at02.v = parent_z;
    if (!(((S_818FF710_30 *)(parent_obj->unk_0C))->unk_14 & 0x8000)) {
        ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_00.at02.v + offset[0]);
        ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) (((S_818FF710_5 *)motion)->unk_04.at02.v + offset[1]);
        start_z = (u16) (((S_818FF710_5 *)motion)->unk_08.at02.v + offset[2]);
        ASM_TAILSLOT_PIN(start_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80025158();
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    start_z = (u16) (parent_z - 0x40);
    ((S_818FF710_5 *)motion)->unk_08.at02.v = start_z;
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
    if (flight_target != NULL) {
        target_position = ((S_818FF710_7_pre *)flight_target)[-1].unk_00;
        (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_8 *)target_position)->unk_0A - (D_800DDC40[((S_818FF710_7 *)flight_target)->unk_13] + 0x40));
        origin = ((S_818FF710_2_pre *)parent)[-1].unk_00;
        (*(s8 *)((u8 *)effect + 0xA2)) = (s8) (origin->unk_24 + D_8006CCD8[(*(s16 *)((u8 *)effect + 0x7E)) * 2]);
        (*(s8 *)((u8 *)effect + 0xA3)) = (s8) (origin->unk_25 + D_8006CCE8[(*(s16 *)((u8 *)effect + 0x7E)) * 2]);
        parent_tile = ((S_818FF710_2 *)parent)->unk_72;
        origin_tile = origin->unk_24;
        if (parent_tile != origin_tile) {
            tile_distance = parent_tile - origin_tile;
            goto absolute_distance;
        }
        parent_tile = ((S_818FF710_2 *)parent)->unk_73;
        origin_tile = origin->unk_25;
        tile_distance = parent_tile - origin_tile;
absolute_distance:
        if (tile_distance >= 0) {
            goto set_flight_ticks;
        }
        tile_distance = 0 - tile_distance;
set_flight_ticks:
        (*(s8 *)((u8 *)effect + 0x7B)) = (s8) ((tile_distance * 2) - 1);
    } else {
        (*(s16 *)((u8 *)effect + 0x78)) = (s16) (((S_818FF710_2 *)parent)->unk_88 - 0x50);
        (*(s8 *)((u8 *)effect + 0x7B)) = 0x20;
    }
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
    goto done;
state_flight:
    trail_count = 0;
emit_trail:
    trail_count += 1;
    {
        register void *trail_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 direction;
        s32 trail_color;
        register s32 trail_size ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 random_value;
        random_value = func_80069EF8();
        trail_obj = effect - 0x20;
        trail_color = 0x2020E0;
        ASM_KEEP_NV(trail_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        trail_size = (random_value & 0xFF) | 0x80;
        ASM_KEEP_NV(trail_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        direction = (*(s16 *)((u8 *)effect + 0x7E));
        func_800244CC(trail_obj, direction, trail_color, trail_size, 0, 0, 0);
    }
    if (trail_count < 4) {
        goto emit_trail;
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
    goto done;
advance_flight:
    remaining_ticks = (u8) (*(s8 *)((u8 *)effect + 0x7B)) - 1;
    (*(s8 *)((u8 *)effect + 0x7B)) = remaining_ticks;
    if ((remaining_ticks << 0x18) > 0) {
        goto move_effect;
    }
    if (((S_818FF710_2 *)parent)->unk_60 == NULL) {
        goto finish_flight;
    }
    (*(s16 *)((u8 *)effect + 0xA)) = 3;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    func_800A56E0(0x300);
    impact_target = ((S_818FF710_2 *)parent)->unk_60;
    hit_position = ((S_818FF710_10_pre *)impact_target)[-1].unk_00;
    if ((u32) (((S_818FF710_10 *)impact_target)->unk_13 - 0x33) < 4U) {
        goto snap_to_target;
    }
    hit_position->unk_14 = (u16) (hit_position->unk_14 | 0x800);
    hit_target = ((S_818FF710_2 *)parent)->unk_60;
    hit_target->unk_14 = (s32) (hit_target->unk_14 | 0x100000);
snap_to_target:
    motion_aux = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    ((S_818FF710_5 *)motion)->unk_00.at02.v = (u16) ((S_818FF710_13 *)motion_aux)->unk_02;
    ((S_818FF710_5 *)motion)->unk_04.at02.v = (u16) ((S_818FF710_13 *)motion_aux)->unk_06;
    ((S_818FF710_5 *)motion)->unk_08.at02.v = (u16) (*(s16 *)((u8 *)effect + 0x78));
    func_80024DB8(effect, motion, sprite, motion_aux);
    goto done;
finish_flight:
    (*(s16 *)((u8 *)effect + 0xA)) = 8;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = 0;
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = 0;
    func_80024DB8(effect, motion, sprite);
    goto done;
move_effect:
    motion_aux = ((S_818FF710_5 *)motion)->unk_10.p;
    ((S_818FF710_5 *)motion)->unk_00.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_00.at00.v + ((S_818FF710_5 *)motion)->unk_0C);
    ((S_818FF710_5 *)motion)->unk_04.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_04.at00.v + (s32) motion_aux);
    ((S_818FF710_5 *)motion)->unk_08.at00.v = (s32) (((S_818FF710_5 *)motion)->unk_08.at00.v + ((S_818FF710_5 *)motion)->unk_14);
    func_80024DB8(effect, motion, sprite, motion_aux);
    goto done;
state_impact: {
    s32 saved_tick;
    s32 rect_value;
    register s16 *source_rect ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s16 *dest_rect ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *source_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 *dest_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 dest_x;
    s32 rect_height;
    s32 source_x;
    old_impact_angle = ((S_818FF710_1 *)sprite)->unk_1A;
    impact_angle = old_impact_angle + 0x190;
    ((S_818FF710_1 *)sprite)->unk_1A = impact_angle;
    if ((u32) (impact_angle & 0xFFFF) < 0x1001U) {
        goto update_impact;
    }
    ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_impact_angle - 0xE70);
update_impact:
    func_80024DB8(effect, motion, sprite);
    impact_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = impact_tick;
    if ((s16) impact_tick != 1) {
        goto check_spawn_tick;
    }
    source_rect = &texture_rects.half[0];
    source_arg = source_rect;
    dest_rect = &texture_rects.half[4];
    dest_arg = dest_rect;
    ASM_SET(source_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_SET(rect_height);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_SET(dest_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    source_x = 0x340;
    rect_value = 0x154;
    texture_rects.half[1] = (s16) rect_value;
    rect_value = 0x60;
    texture_rects.half[2] = (s16) rect_value;
    rect_height = 0x54;
    dest_x = 0x370;
    texture_rects.half[0] = (s16) source_x;
    texture_rects.half[3] = (s16) rect_height;
    texture_rects.half[4] = (s16) dest_x;
    rect_value = 0x19A;
    texture_rects.half[5] = (s16) rect_value;
    func_800B8FC8(((S_818FF710_2 *)parent)->unk_60, source_arg, dest_arg, 1, (s32) (s16) impact_tick);
    source_arg = source_rect;
    dest_arg = dest_rect;
    ASM_KEEP_NV(source_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(dest_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    rect_value = 0x1A8;
    texture_rects.half[1] = (s16) rect_value;
    rect_value = 0x60;
    texture_rects.half[2] = (s16) rect_value;
    texture_rects.half[0] = (s16) source_x;
    texture_rects.half[3] = (s16) rect_height;
    texture_rects.half[4] = (s16) dest_x;
    rect_value = 0x1EF;
    texture_rects.half[5] = (s16) rect_value;
    func_800B8FC8(((S_818FF710_2 *)parent)->unk_60, source_arg, dest_arg, 1, (s32) (s16) impact_tick);
check_spawn_tick:
    saved_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (saved_tick != 4) {
        goto done;
    }
    impact_obj = func_8003FC64(0x212);
    child_effect = impact_obj + 0x20;
    if (impact_obj == NULL) {
        goto spawn_linked;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)impact_obj + 0x10)) = &D_800246F8;
    func_8004491C(impact_obj, &D_80045340);
    impact_sprite = (*(void **)((u8 *)impact_obj + 0xC));
    impact_sprite->unk_06 = 0;
    impact_sprite->unk_14 |= 0xC;
    impact_sprite->unk_10 = 0x40;
    sprite_flags = impact_sprite->unk_14;
    impact_sprite->unk_14 = (u16) (sprite_flags | 0x80);
    impact_position = (*(void **)((u8 *)impact_obj + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    impact_origin = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    impact_position->unk_00 = (s32) ((S_818FF710_17 *)impact_origin)->unk_00;
    impact_position->unk_04 = (s32) ((S_818FF710_17 *)impact_origin)->unk_04;
    impact_position->unk_08 = (s32) ((S_818FF710_17 *)impact_origin)->unk_08;
    impact_sprite = (*(void **)((u8 *)impact_obj + 0xC));
    impact_sprite->unk_1C = 0x1004;
    impact_sprite->unk_1E = 0x1004;
    impact_sprite->unk_22 = (s16) ((s32) (0 - D_800DDC40[((S_818FF710_31 *)(((S_818FF710_2 *)parent)->unk_60))->unk_13]) / 2);
    impact_sprite->unk_0E = 0x80;
    impact_sprite->unk_0D = 0x80;
    impact_sprite->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)impact_obj + 0x40)) = D_80025E34;
    impact_sprite->unk_08 = (void *) (impact_obj + 0x40);
    ((S_818FF710_32 *)(impact_sprite->unk_08))->unk_04 = func_80066460(2, 2, 0x340, 0x154);
spawn_linked:
    linked_obj = func_8003FC64(0x212);
    child_effect = linked_obj + 0x20;
    if (linked_obj == NULL) {
        goto spawn_burst;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)linked_obj + 0x10)) = &D_80024780;
    func_8004491C(linked_obj, &D_80045340);
    linked_sprite = (*(void **)((u8 *)linked_obj + 0xC));
    linked_sprite->unk_14 &= 0xFFF3;
    linked_sprite->unk_10 = 0x20;
    linked_sprite->unk_14 |= 0x80;
    child_effect->unk_2C = parent;
    target = ((S_818FF710_2 *)parent)->unk_60;
    child_effect->unk_34 = effect;
    child_effect->unk_30 = target;
    linked_sprite->unk_06 = 0;
    linked_position = (*(void **)((u8 *)linked_obj + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    linked_origin = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    linked_position->unk_00 = (s32) ((S_818FF710_20 *)linked_origin)->unk_00;
    linked_position->unk_04 = (s32) ((S_818FF710_20 *)linked_origin)->unk_04;
    linked_position->unk_08 = (s32) ((S_818FF710_20 *)linked_origin)->unk_08;
    linked_sprite = (*(void **)((u8 *)linked_obj + 0xC));
    linked_sprite->unk_1E = 0x1000;
    linked_sprite->unk_1C = 0x1000;
    linked_sprite->unk_0E = 0x80;
    linked_sprite->unk_0D = 0x80;
    linked_sprite->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)linked_obj + 0x40)) = D_80025E40;
    linked_sprite->unk_08 = (void *) (linked_obj + 0x40);
    ((S_818FF710_33 *)(linked_sprite->unk_08))->unk_04 = func_80066460(2, 1, 0x340, 0x1A8);
spawn_burst:
    burst_obj = func_8003FC64(0x212);
    child_effect = burst_obj + 0x20;
    if (burst_obj == NULL) {
        goto spawn_controller;
    }
    child_effect->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)burst_obj + 0x10)) = &D_800245EC;
    func_8004491C(burst_obj, &D_80045340);
    burst_sprite = (*(void **)((u8 *)burst_obj + 0xC));
    ((S_818FF710_21 *)burst_sprite)->unk_06 = 0;
    ((S_818FF710_21 *)burst_sprite)->unk_14 &= 0xFFF3;
    ((S_818FF710_21 *)burst_sprite)->unk_10 = 0x20;
    sprite_flags = ((S_818FF710_21 *)burst_sprite)->unk_14;
    ((S_818FF710_21 *)burst_sprite)->unk_14 = (u16) (sprite_flags | 0x80);
    burst_position = (*(void **)((u8 *)burst_obj + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    burst_origin = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    burst_position->unk_00 = (s32) ((S_818FF710_23 *)burst_origin)->unk_00;
    burst_position->unk_04 = (s32) ((S_818FF710_23 *)burst_origin)->unk_04;
    burst_position->unk_08 = (s32) ((S_818FF710_23 *)burst_origin)->unk_08;
    burst_sprite = (*(void **)((u8 *)burst_obj + 0xC));
    ((S_818FF710_21 *)burst_sprite)->unk_0E = 0x80;
    ((S_818FF710_21 *)burst_sprite)->unk_0D = 0x80;
    ((S_818FF710_21 *)burst_sprite)->unk_0C = 0x80;
    ((S_818FF710_21 *)burst_sprite)->unk_1E = 0;
    ((S_818FF710_21 *)burst_sprite)->unk_1C = 0;
    (*(Packed12 *)((u8 *)burst_obj + 0x40)) = D_80025E58;
    ((S_818FF710_21 *)burst_sprite)->unk_08 = (void *) (burst_obj + 0x40);
spawn_controller:
    control_obj = func_8003FC64(0x212);
    child_effect = control_obj + 0x20;
    if (control_obj == NULL) {
        goto finish_spawning;
    }
    controller_obj = control_obj;
    sprite_setup = (void *) &D_80045340;
    ASM_KEEP_NV(sprite_setup);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    child_effect->unk_2C = parent;
    linked_target = ((S_818FF710_2 *)parent)->unk_60;
    child_data = (void *) (impact_obj + 0x20);
    child_effect->unk_38 = child_data;
    child_data = (void *) (burst_obj + 0x20);
    child_effect->unk_3C = child_data;
    child_data = (void *) (linked_obj + 0x20);
    child_effect->unk_40 = child_data;
    child_effect->unk_34 = effect;
    child_effect->unk_30 = linked_target;
    (*(M2C_UNK **)((u8 *)control_obj + 0x10)) = &D_8002499C;
    func_8004491C(controller_obj, sprite_setup);
    controller_sprite = (*(void **)((u8 *)control_obj + 0xC));
    ((S_818FF710_24 *)controller_sprite)->unk_06 = 0;
    ((S_818FF710_24 *)controller_sprite)->unk_14 |= 0xC;
    ((S_818FF710_24 *)controller_sprite)->unk_10 = 0x20;
    sprite_flags = ((S_818FF710_24 *)controller_sprite)->unk_14;
    ((S_818FF710_24 *)controller_sprite)->unk_14 = (u16) (sprite_flags | 0x80);
    control_position = (*(void **)((u8 *)control_obj + 8));
    child_effect->unk_0A = 0;
    child_effect->unk_0C = 0;
    controller_origin = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_00;
    control_position->unk_00 = (s32) ((S_818FF710_26 *)controller_origin)->unk_00;
    control_position->unk_04 = (s32) ((S_818FF710_26 *)controller_origin)->unk_04;
    control_position->unk_08 = (s32) ((S_818FF710_26 *)controller_origin)->unk_08;
    controller_sprite = (*(void **)((u8 *)control_obj + 0xC));
    ((S_818FF710_24 *)controller_sprite)->unk_1E = 0x1000;
    ((S_818FF710_24 *)controller_sprite)->unk_1C = 0x1000;
    ((S_818FF710_24 *)controller_sprite)->unk_0E = 0x80;
    ((S_818FF710_24 *)controller_sprite)->unk_0D = 0x80;
    ((S_818FF710_24 *)controller_sprite)->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)control_obj + 0x40)) = D_80025E28;
    ((S_818FF710_24 *)controller_sprite)->unk_08 = (void *) (control_obj + 0x40);
    ASM_KEEP(control_obj);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
finish_spawning:
    spawn_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (spawn_tick != saved_tick) {
        goto done;
    }
    (*(s16 *)((u8 *)effect + 0xA)) = spawn_tick;
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    (*(s16 *)((u8 *)effect + 0x90)) = 0;
    goto done;
}
state_burst:
    burst_count = 0;
    (*(u16 *)((u8 *)effect + 0x82)) = (u16) ((*(u16 *)((u8 *)effect + 0x82)) + 1);
emit_burst:
    burst_count += 1;
    {
        register void *trail_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 direction;
        s32 trail_color;
        register s32 trail_size ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 random_value;
        random_value = func_80069EF8();
        trail_obj = effect - 0x20;
        trail_color = 0x2020E0;
        ASM_KEEP_NV(trail_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        trail_size = (random_value & 0xFF) | 0x80;
        ASM_KEEP_NV(trail_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        direction = (*(s16 *)((u8 *)effect + 0x7E));
        func_800244CC(trail_obj, direction, trail_color, trail_size, 0, 0, 0);
    }
    if (burst_count < 3) {
        goto emit_burst;
    }
    old_burst_angle = ((S_818FF710_1 *)sprite)->unk_1A;
    burst_angle = old_burst_angle + 0x190;
    ((S_818FF710_1 *)sprite)->unk_1A = burst_angle;
    if ((u32) (burst_angle & 0xFFFF) < 0x1001U) {
        goto fade_burst;
    }
    ((S_818FF710_1 *)sprite)->unk_1A = (u16) (old_burst_angle - 0xE70);
fade_burst:
    fade_tick = (s16) (*(u16 *)((u8 *)effect + 0x82));
    if (fade_tick < 0x51) {
        goto update_burst;
    }
    ((S_818FF710_1 *)sprite)->unk_0C.at00u.v = (s8) (((0x64 - fade_tick) << 7) / 20);
    ((S_818FF710_1 *)sprite)->unk_0C.at01.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
    ((S_818FF710_1 *)sprite)->unk_0C.at02.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)effect + 0x82))) << 7) / 20);
update_burst:
    func_80024DB8(effect, motion, sprite);
    if ((s16) (*(u16 *)((u8 *)effect + 0x82)) >= 0x64) {
        goto next_state;
    }
    goto done;
state_apply:
    if ((*(s16 *)((u8 *)effect + 0x90)) == 0) {
        goto done;
    }
    owner_id = 0xFF;
    if (D_800E3D68 == 0xFF) {
        goto apply_effect;
    }
    owner_id = (*(u8 *)((u8 *)effect + 9));
apply_effect:
    func_8002407C(((S_818FF710_2 *)parent)->unk_60, owner_id, parent);
next_state:
    (*(u16 *)((u8 *)effect + 0x82)) = 0U;
    (*(s16 *)((u8 *)effect + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)effect + 0xA)) + 1);
    goto done;
state_release:
    release_tick = (*(u16 *)((u8 *)effect + 0x82)) + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = release_tick;
    if ((s16) release_tick < 0x1F) {
        goto done;
    }
    target_sprite = ((S_818FF710_31_pre *)(((S_818FF710_2 *)parent)->unk_60))[-1].unk_04;
    target_sprite->unk_14 = (u16) (target_sprite->unk_14 & 0xF7FF);
    released_target = ((S_818FF710_2 *)parent)->unk_60;
    released_target->unk_14 = (s32) (released_target->unk_14 & 0xFFEFFFFF);
    (*(s16 *)((u8 *)effect + 0xA)) = 8;
    (*(u16 *)((u8 *)effect + 0x82)) = 0x1EU;
    goto done;
state_finish:
    old_finish_tick = (*(u16 *)((u8 *)effect + 0x82));
    finish_tick = old_finish_tick + 1;
    (*(u16 *)((u8 *)effect + 0x82)) = finish_tick;
    if ((s16) finish_tick < 0x1F) {
        goto done;
    }
    effect_active = (s32) ((S_818FF710_3 *)(&D_80025E80))->unk_00;
    (*(u16 *)((u8 *)effect + 0x82)) = old_finish_tick;
    if (effect_active != 0) {
        goto clear_active;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_818FF710_29 *)(&D_800814A0))->unk_00 | 0x8000);
    goto done;
clear_active:
    (*(s16 *)&D_80025E80) = 0;
done:
    return;
}
