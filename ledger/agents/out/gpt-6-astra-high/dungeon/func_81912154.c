#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80024170_arg0.h"


typedef struct S_80025954_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80025954_1;   /* temp_s7 in func_80025954 */

typedef struct S_80025954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80025954_2;   /* arg2 in func_80025954 */

typedef struct S_80025954_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80025954_3;   /* temp_s0 in func_80025954 */

typedef struct S_80025954_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80025954_4;   /* temp_a1 in func_80025954 */

typedef struct S_80025954_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025954_5;   /* arg1 in func_80025954 */

typedef struct S_80025954_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025954_6;   /* temp_v1_2 in func_80025954 */

typedef struct S_80025954_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80025954_7_pre;   /* the 0x18 bytes before temp_v0 in func_80025954, addressed as temp_v0[-1] */

typedef struct S_80025954_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80025954_8;   /* temp_a3 in func_80025954 */

typedef struct S_80025954_9 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} S_80025954_9;   /* temp_v1_4 in func_80025954 */

typedef struct S_80025954_10 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80025954_10;   /* var_a2 in func_80025954 */

typedef struct S_80025954_11 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80025954_11;   /* call_a1 in func_80025954 */

typedef struct S_80025954_12 {
    s32 unk_00;
} S_80025954_12;   /* stack.motion in func_80025954 */

typedef struct S_80025954_13 {
    s32 unk_00;
} S_80025954_13;   /* &D_800814A0 in func_80025954 */

typedef struct S_80025954_14 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025954_14;   /* ((S_80025954_3 *)temp_s0)->unk_0C in func_80025954 */

typedef struct S_80025954_15 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025954_15;   /* ((S_80025954_1 *)temp_s7)->unk_60 in func_80025954 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024028[];
s32 func_80024170(); /* extern */
M2C_UNK func_80025874();         /* extern */
s32 func_8003DE58();     /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
s32 func_800A56E0();                     /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];

typedef struct LocalStack {
    u8 motion[0x18];
    u16 distance[4];
    u16 saved_y;
} LocalStack;

/* Updates movement toward a target or along a direction and advances the action phases. */
void func_80025954(void *state, void *motion_in, void *appearance) {
    static void *const phase_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    LocalStack stack;
    s8 *distance_cursor;
    register s32 y_delta ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    s16 floor_height;
    s32 phase;
    register s32 axis_delta ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 x_distance;
    register s32 motion_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 travel_frames;
    s32 direction;
    s32 step_direction;
    s32 step_count;
    s32 current_y;
    u32 origin_z;
    register s32 source_coord ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 end_tile_x;
    s32 tile_x;
    s32 tile_y;
    void *model;
    void *destination;
    void *owner_links;
    register void *owner ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    void *target;
    void *origin;
    void *entity;
    register void *motion ASM_REG("$22") = motion_in;   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *x_lookup_first;
    s16 *y_lookup_first;
    s16 *x_lookup_next;
    register s16 *y_lookup_next ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 height ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 *final_base ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s16 *final_ptr;
    register u32 end_tile_y ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
    void *motion_out;

    phase = ((Rec_func_80024170_arg0 *)state)->unk_0A;
    owner = ((Rec_func_80024170_arg0 *)state)->unk_00;
    ((Rec_func_80024170_arg0 *)state)->unk_10 = (u16) (((Rec_func_80024170_arg0 *)state)->unk_10 + 1);
    if ((u32) phase >= 7U) {
        goto finish;
    }
    (void)phase_labels; goto *D_80024028[(u32)(phase)];
jt_c0:
    ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
    ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
    ((Rec_func_80024170_arg0 *)state)->unk_0E = (u16) (((u16) ((S_80025954_1 *)owner)->unk_2A >> 9) & 7);
    ((S_80025954_2 *)appearance)->unk_0C = 0x808080;
jt_c1:
    owner_links = owner - 0x20;
    model = ((S_80025954_3 *)owner_links)->unk_0C;
    if (func_8003DE58(((S_80025954_4 *)model)->unk_08, model, stack.distance, 0) != 0) {
        goto set_origin;
    }
    if (!(((S_80025954_14 *)(((S_80025954_3 *)owner_links)->unk_0C))->unk_14 & 0x8000)) {
        goto finish;
    }
set_origin:
    origin = ((S_80025954_3 *)owner_links)->unk_08;
    ((S_80025954_5 *)motion)->unk_00.at02.v = (u16) ((S_80025954_6 *)origin)->unk_02;
    ((S_80025954_5 *)motion)->unk_04.at02.v = (u16) ((S_80025954_6 *)origin)->unk_06;
    origin_z = ((S_80025954_6 *)origin)->unk_0A;
    ((S_80025954_5 *)motion)->unk_08.at02.v = origin_z;
    if (((S_80025954_14 *)(((S_80025954_3 *)owner_links)->unk_0C))->unk_14 & 0x8000) {
        goto offset_origin_z;
    }
    ((S_80025954_5 *)motion)->unk_00.at02.v = (u16) (((S_80025954_5 *)motion)->unk_00.at02.v + stack.distance[0]);
    ((S_80025954_5 *)motion)->unk_04.at02.v = (u16) (((S_80025954_5 *)motion)->unk_04.at02.v + stack.distance[1]);
    ASM_MEM_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    motion_value = ((S_80025954_5 *)motion)->unk_08.at02.v;
    axis_delta = stack.distance[2];
    motion_value += axis_delta;
    goto store_origin_z;
offset_origin_z:
    motion_value = origin_z - 0x40;
store_origin_z:
    ((S_80025954_5 *)motion)->unk_08.at02.v = motion_value;
    if (!(*((Rec_func_80024170_arg0 *)state)->unk_04 & 0x80)) {
        goto finish;
    }
    target = ((S_80025954_1 *)owner)->unk_60;
    step_count = 1;
    if (target == NULL) {
        goto trace_direction;
    }
    destination = ((S_80025954_7_pre *)target)[-1].unk_00;
    x_distance = ((S_80025954_8 *)destination)->unk_00.at02.v;
    x_distance -= ((S_80025954_5 *)motion)->unk_00.at02u.v;
    if (x_distance >= 0) {
        goto store_x_distance;
    }
    x_distance = 0 - x_distance;
store_x_distance:
    stack.distance[0] = (u16) x_distance;
    motion_value = ((S_80025954_8 *)destination)->unk_04.at02.v;
    current_y = ((S_80025954_5 *)motion)->unk_04.at02u.v;
    ASM_CLOBBER("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    distance_cursor = (s8 *) &stack.motion[2];
    ASM_KEEP(distance_cursor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    motion_value -= current_y;
    if (motion_value >= 0) {
        goto store_y_distance;
    }
    motion_value = 0 - motion_value;
store_y_distance:
    stack.distance[1] = (u16) motion_value;
    entity = ((S_80025954_1 *)owner)->unk_60;
    axis_delta = D_800DDC40[((S_80025954_9 *)entity)->unk_13] << 0x10;
    motion_value = ((S_80025954_8 *)destination)->unk_08.at02.v - axis_delta;
    axis_delta = ((S_80025954_5 *)motion)->unk_08.at02u.v;
    axis_delta += 0x300000;
    motion_value -= axis_delta;
    if (motion_value >= 0) {
        goto store_z_distance;
    }
    motion_value = 0 - motion_value;
store_z_distance:
    stack.distance[2] = (u16) motion_value;
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = x_distance;
scan_distances:
    if (((S_80025954_10 *)distance_cursor)->unk_18 <= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
        goto next_distance;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) (u16) ((S_80025954_10 *)distance_cursor)->unk_18;
next_distance:
    step_count += 1;
    distance_cursor += 2;
    if (step_count < 3) {
        goto scan_distances;
    }
    travel_frames = (s32) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 << 0x10) >> 0x14;
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) travel_frames;
    if (travel_frames != 0) {
        goto aim_at_target;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = 1;
aim_at_target:
    motion_value = ((S_80025954_8 *)destination)->unk_00.at00.v;
    source_coord = ((S_80025954_5 *)motion)->unk_00.at00.v;
    motion_value -= source_coord;
    motion_value /= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
    source_coord = ((S_80025954_5 *)motion)->unk_04.at00.v;
    ((S_80025954_5 *)motion)->unk_0C = motion_value;
    motion_value = ((S_80025954_8 *)destination)->unk_04.at00.v - source_coord;
    motion_value /= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
    ((S_80025954_5 *)motion)->unk_10 = motion_value;
    entity = ((S_80025954_1 *)owner)->unk_60;
    motion_value = D_800DDC40[((S_80025954_9 *)entity)->unk_13] << 0x10;
    axis_delta = ((S_80025954_8 *)destination)->unk_08.at00.v - motion_value;
    motion_value = ((S_80025954_5 *)motion)->unk_08.at00.v;
    motion_value += 0x300000;
    axis_delta -= motion_value;
    axis_delta /= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
    motion_out = motion;
    ASM_KEEP(motion_out);   /* MATCH pin: retail delay-slot fill depends on it */
    ((S_80025954_11 *)motion_out)->unk_14 = axis_delta;
    ASM_JALDELAY_PIN(axis_delta);   /* MATCH pin: load-bearing for the whole function shape */
    func_80024170(state, motion_out, distance_cursor, destination);
    motion_value = (u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1;
    goto set_phase;
trace_direction:
    step_count = 0;
    entity = ((S_80025954_3 *)owner_links)->unk_0C;
    ASM_KEEP(entity);   /* MATCH pin: retail delay-slot fill depends on it */
    motion_value = 0x80070000;
    ASM_KEEP(motion_value);   /* MATCH pin: load-bearing for the whole function shape */
    tile_x = ((S_80025954_9 *)entity)->unk_24;
    tile_y = ((S_80025954_9 *)entity)->unk_25;
    end_tile_x = tile_x;
    stack.saved_y = (u16) tile_y;
scan_tiles:
    if ((func_800A44E0(((s16) tile_x << 6) & 0xFFC0, ((s16) tile_y << 6) & 0xFFC0, ((S_80025954_1 *)owner)->unk_88, (s16) (((Rec_func_80024170_arg0 *)state)->unk_0E << 9)) << 0x10) != 0) {
        goto use_endpoint;
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* MATCH pin: load-bearing for the whole function shape */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        direction = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
        height = (u16) ((S_80025954_1 *)owner)->unk_88;
        x_lookup_first = (s16 *) ((direction << 1) + (u32) lookup_base);
        ASM_KEEP(x_lookup_first);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    height = (s16) (height - 0x20);
    {
        register s16 *lookup_base ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* MATCH pin: load-bearing for the whole function shape */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        y_lookup_first = (s16 *) ((direction << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_first);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    }
    floor_height = func_800BCB04(((((s16) tile_x + *x_lookup_first) << 6) + 0x20) & 0xFFE0, ((((s16) tile_y + *y_lookup_first) << 6) + 0x20) & 0xFFE0, height);
    ASM_CLOBBER("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_CLOBBER("$18");   /* MATCH pin: retail register colouring depends on it */
    destination = stack.motion;
    if (floor_height >= 0x201) {
        goto build_endpoint;
    }
    if ((s16) (floor_height - (u16) ((S_80025954_1 *)owner)->unk_88) < -0x3F) {
        goto build_endpoint;
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* MATCH pin: load-bearing for the whole function shape */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        step_direction = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
        step_count += 1;
        x_lookup_next = (s16 *) ((step_direction << 1) + (u32) lookup_base);
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* MATCH pin: load-bearing for the whole function shape */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        y_lookup_next = (s16 *) ((step_direction << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_next);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    }
    source_coord = tile_x + (u16) *x_lookup_next;
    tile_x = source_coord;
    ASM_KEEP_NV(tile_x);   /* MATCH pin: retail register colouring depends on it */
    motion_value = tile_y + (u16) *y_lookup_next;
    tile_y = motion_value;
    stack.saved_y = (u16) motion_value;
    end_tile_x = source_coord;
    if (step_count < 8) {
        goto scan_tiles;
    }
use_endpoint:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    destination = stack.motion;
build_endpoint:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    axis_delta = (u32) end_tile_x << 0x10;
    final_base = D_8006CCD8;
    axis_delta >>= 0xA;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    motion_value = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
    motion_value <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + motion_value);
    final_base = D_8006CCE8;
    motion_value = *final_ptr;
    motion_value = (motion_value + 1) << 5;
    axis_delta += motion_value;
    ((S_80025954_8 *)destination)->unk_00.at02.v = axis_delta;
    axis_delta = (u32) axis_delta << 0x10;
    end_tile_y = stack.saved_y;
    motion_value = (s16) ((Rec_func_80024170_arg0 *)state)->unk_0E;
    y_delta = (u32) end_tile_y << 0x10;
    motion_value <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + motion_value);
    motion_value = *final_ptr;
    y_delta >>= 0xA;
    motion_value = (motion_value + 1) << 5;
    y_delta += motion_value;
    ((S_80025954_8 *)destination)->unk_04.at02.v = y_delta;
    motion_value = ((S_80025954_5 *)motion)->unk_08.at02.v;
    axis_delta >>= 0x10;
    ((S_80025954_8 *)destination)->unk_08.at02u.v = motion_value;
    motion_value = ((S_80025954_5 *)motion)->unk_00.at02u.v;
    ASM_KEEP_DEP_NV(y_delta, motion_value);   /* MATCH pin: retail delay-slot fill depends on it */
    y_delta = (u32) y_delta << 0x10;
    ASM_KEEP(y_delta);   /* MATCH pin: retail schedule: same instructions, different order without it */
    axis_delta -= motion_value;
    if (axis_delta >= 0) {
        goto store_end_x_distance;
    }
    axis_delta = 0 - axis_delta;
store_end_x_distance:
    stack.distance[0] = axis_delta;
    motion_value = ((S_80025954_5 *)motion)->unk_04.at02u.v;
    y_delta >>= 0x10;
    y_delta -= motion_value;
    if (y_delta >= 0) {
        goto store_end_y_distance;
    }
    y_delta = 0 - y_delta;
store_end_y_distance:
    stack.distance[1] = y_delta;
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = axis_delta;
    if ((s16) stack.distance[1] <= (s16) axis_delta) {
        goto set_travel_frames;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) (u16) stack.distance[1];
set_travel_frames:
    motion_value = (s32) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 << 0x10) >> 0x14;
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = (s16) motion_value;
    if (motion_value != 0) {
        goto aim_at_endpoint;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16 = 1;
aim_at_endpoint:
    motion_value = ((S_80025954_12 *)(stack.motion))->unk_00;
    source_coord = ((S_80025954_5 *)motion)->unk_00.at00.v;
    motion_value -= source_coord;
    motion_value /= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
    source_coord = ((S_80025954_5 *)motion)->unk_04.at00.v;
    ((S_80025954_5 *)motion)->unk_0C = motion_value;
    motion_value = ((S_80025954_8 *)destination)->unk_04.at00.v - source_coord;
    motion_value /= ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16;
    motion_out = motion;
    ((S_80025954_11 *)motion_out)->unk_14 = 0;
    ((S_80025954_11 *)motion_out)->unk_10 = motion_value;
    ASM_JALDELAY_PIN(motion_value);   /* MATCH pin: load-bearing for the whole function shape */
    func_80024170(state, motion_out);
    motion_value = 6;
    goto set_phase;
jt_c2:
    ((S_80025954_5 *)motion)->unk_00.at00.v = (s32) (((S_80025954_5 *)motion)->unk_00.at00.v + ((S_80025954_5 *)motion)->unk_0C);
    ((S_80025954_5 *)motion)->unk_04.at00.v = (s32) (((S_80025954_5 *)motion)->unk_04.at00.v + ((S_80025954_5 *)motion)->unk_10);
    ((S_80025954_5 *)motion)->unk_08.at00.v = (s32) (((S_80025954_5 *)motion)->unk_08.at00.v + ((S_80025954_5 *)motion)->unk_14);
    if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
        goto finish;
    }
    func_80025874(state, motion, ((S_80025954_15 *)(((S_80025954_1 *)owner)->unk_60))->unk_88);
    func_800A56E0(0x300);
    goto advance_phase;
jt_c3:
    if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 >= 8) {
        goto advance_phase;
    }
    ((Rec_func_80024170_arg0 *)state)->unk_14 = 0;
    return;
jt_c4:
    if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < 0x44) {
        goto finish;
    }
    func_8009CE1C(((S_80025954_1 *)owner)->unk_60, 0x18, ((Rec_func_80024170_arg0 *)state)->unk_09, 1, (s32) (s16) (((Rec_func_80024170_arg0 *)state)->unk_0E << 9), owner, 1);
advance_phase:
    ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
    ((Rec_func_80024170_arg0 *)state)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)state)->unk_0A + 1);
    goto finish;
jt_c5:
    if (((Rec_func_80024170_arg0 *)state)->unk_14 != 0) {
        goto finish;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80025954_13 *)(&D_800814A0))->unk_00 | 0x8000);
    goto finish;
jt_c6:
    ((S_80025954_5 *)motion)->unk_00.at00.v = (s32) (((S_80025954_5 *)motion)->unk_00.at00.v + ((S_80025954_5 *)motion)->unk_0C);
    ((S_80025954_5 *)motion)->unk_04.at00.v = (s32) (((S_80025954_5 *)motion)->unk_04.at00.v + ((S_80025954_5 *)motion)->unk_10);
    ((S_80025954_5 *)motion)->unk_08.at00.v = (s32) (((S_80025954_5 *)motion)->unk_08.at00.v + ((S_80025954_5 *)motion)->unk_14);
    if ((s16) ((Rec_func_80024170_arg0 *)state)->unk_10 < ((Rec_func_80024170_arg0 *)state)->unk_12.as_s16) {
        goto finish;
    }
    motion_value = 5;
set_phase:
    ((Rec_func_80024170_arg0 *)state)->unk_0A = motion_value;
    ((Rec_func_80024170_arg0 *)state)->unk_10 = 0U;
finish:
    ((Rec_func_80024170_arg0 *)state)->unk_14 = 0;
    return;
}
