/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58();
s32 func_80098920();
M2C_UNK func_8009A028();
s32 func_8009B164();
void *func_8009B25C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A7A7C();
M2C_UNK func_800B66C8();
s16 func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern M2C_UNK D_80081484;
extern s32 D_800814A0[3];
extern void *D_800814A8;
extern u16 D_80083460[6];
extern u8 D_800DD7DC[];
extern s32 D_800E3540;
extern void *D_800E3D7C[3];

#ifdef NON_MATCHING
#define DUNGEON_FLAGS_PAGE ((s8 *)D_800814A0 - 0x14A0)
#else
#define DUNGEON_FLAGS_PAGE ((s8 *)0x80080000)
#endif


typedef struct S_800A871C_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A871C_0;   /* temp_v1 in func_800A871C */

typedef struct S_800A871C_1_pre {
    u16 unk_00;
} S_800A871C_1_pre;   /* the 0x2 bytes before r_arg0 in func_800A871C, addressed as r_arg0[-1] */

typedef struct S_800A871C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    s32 * unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
} S_800A871C_1;   /* r_arg0 in func_800A871C */

typedef struct S_800A871C_2 {
    s16 unk_00;
} S_800A871C_2;   /* &sp18[2] in func_800A871C */

typedef struct S_800A871C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A871C_3;   /* r_arg1 in func_800A871C */

typedef struct S_800A871C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    union { u8 n; volatile u8 v; } unk_24;   /* accessed as both */
    union { u8 n; volatile u8 v; } unk_25;   /* accessed as both */
} S_800A871C_4;   /* r_arg2 in func_800A871C */

typedef struct S_800A871C_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_5;   /* temp_a1 in func_800A871C */

typedef struct S_800A871C_6 {
    s16 unk_00;
} S_800A871C_6;   /* temp_table_y_derived in func_800A871C */

typedef struct S_800A871C_7 {
    u8 unk_00;
} S_800A871C_7;   /* (u8 *)((unsigned long)temp_a0_5 + (unsigned long)temp_table_x_2) in func_800A871C */

typedef struct S_800A871C_8 {
    u8 unk_00;
} S_800A871C_8;   /* temp_a0_6 in func_800A871C */

typedef struct S_800A871C_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A871C_9;   /* temp_a1_2 in func_800A871C */

typedef struct S_800A871C_10 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800A871C_10;   /* temp_global_814A8 in func_800A871C */

typedef struct S_800A871C_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A871C_11_pre;   /* the 0x14 bytes before temp_v0_5 in func_800A871C, addressed as temp_v0_5[-1] */

typedef struct S_800A871C_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_11;   /* temp_v0_5 in func_800A871C */

typedef struct S_800A871C_12 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A871C_12;   /* temp_a1_3 in func_800A871C */

typedef struct S_800A871C_13 {
    u8 unk_00;
} S_800A871C_13;   /* (u8 *)((unsigned long)temp_a0_8 + (unsigned long)temp_table_x_3) in func_800A871C */

typedef struct S_800A871C_14 {
    u8 unk_00;
} S_800A871C_14;   /* (u8 *)&D_8006CCE8 + temp_a0_8 in func_800A871C */

typedef struct S_800A871C_15 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A871C_15;   /* temp_e_page in func_800A871C */

typedef struct S_800A871C_16 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A871C_16;   /* temp_flags_page in func_800A871C */

typedef struct S_800A871C_17 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
} S_800A871C_17;   /* temp_v0_2 in func_800A871C */

typedef struct S_800A871C_18 {
    u8 unk_00;
} S_800A871C_18;   /* (u8 *)((unsigned long)temp_a0_2 + (unsigned long)temp_table_x_4) in func_800A871C */

typedef struct S_800A871C_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A871C_19;   /* (*(void **)((u8 *)temp_s0 + (0x60))) in func_800A871C */

typedef struct S_800A871C_20 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 ** unk_28;
    void * unk_2C;
} S_800A871C_20;   /* ((S_800A871C_1 *)r_arg0)->unk_90 in func_800A871C */

typedef struct S_800A871C_21 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A871C_21;   /* ((S_800A871C_1 *)r_arg0)->unk_8C in func_800A871C */

typedef struct S_800A871C_22 {
    u8 pad_00[0x124];
    s32 unk_124;
} S_800A871C_22;   /* ((S_800A871C_15 *)temp_e_page)->unk_3D7C in func_800A871C */

typedef struct S_800A871C_23 {
    s32 unk_00;
} S_800A871C_23;   /* ((S_800A871C_1 *)r_arg0)->unk_9C in func_800A871C */

typedef struct S_800A871C_24 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800A871C_24;   /* ((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C in func_800A871C */

typedef struct S_800A871C_25 {
    s32 unk_00;
} S_800A871C_25;   /* **((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4) in func_800A871C */

typedef struct S_800A871C_26 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A871C_26;   /* ((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00 in func_800A871C */

/* Updates an object's launch, movement, collisions, and landing. */
void func_800A871C(void *object_arg, void *motion_arg, void *tile_arg) {
    void *object = object_arg;
    register void *motion = motion_arg;
    register void *tile_input ASM_REG("$6") = tile_arg;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *tile;
    register void *object_data ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 offset[3];
    s16 move_ticks;
    s32 travel_steps;
    s16 ticks_left;
    s16 state;
    s16 land_height;
    s16 drop_height;
    s32 *payload;
    s32 next_dir_offset;
    register s32 launch_dir_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 drop_dir_offset;
    s32 axis_origin;
    s32 axis_target;
    register s32 direction ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 dir_offset;
    u16 drop_heading;
    u16 steps_left;
    u16 launch_heading;
    u8 *next_y_step;
    u8 *launch_y_step;
    register u8 *launch_x_steps ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *drop_x_steps;
    register u8 *next_x_steps ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    S_800A871C_5 *launch_source;
    S_800A871C_9 *source_sprite;
    void *drop_sprite;
    S_800A871C_17 *hit_object;
    void *drop_source;
    u8 *y_steps;
    u8 *y_step;
    s32 target_height;
    s32 height_delta;
    u8 *world_page;
    void *height_source;
    s32 source_height;
    s32 dungeon_flags;
    s32 height;

    ASM_KEEP4_NV(object, motion, tile, tile_input);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    object_data = object;
    tile = tile_input;
    payload = (*(s32 **)((u8 *)object_data + (0x9C)));
    if ((payload == &D_80081484) && (((S_800A871C_0 *)payload)->unk_01 == 0)) {
        (*(s32 **)((u8 *)object_data + (0x9C))) = &D_800E3540;
    }
    state = ((S_800A871C_1 *)object)->unk_A0;
    if (state != 0) {
        if (state != 1) {
            goto advance_position;
        }
        goto update_motion;
    }
    {
        if ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x200000) {
            (*(u16 *)((u8 *)object_data + (0x2A))) = (u16) ((S_800A871C_19 *)((*(void **)((u8 *)object_data + (0x60)))))->unk_2A;
            if (func_8003DE58(
                    ((S_800A871C_26 *)(((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00))->unk_04,
                    ((S_800A871C_1 *)object)->unk_90, offset, 0) == 0) {
                ((S_800A871C_2 *)(&offset[2]))->unk_00 = -0x30;
            }
            ((S_800A871C_3 *)motion)->unk_08.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)object)->unk_8C))->unk_0A + offset[2]);
            ((S_800A871C_4 *)tile)->unk_24.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_24;
            ((S_800A871C_4 *)tile)->unk_25.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_25;
            func_800A2B04(motion, ((S_800A871C_4 *)tile)->unk_24.v, ((S_800A871C_4 *)tile)->unk_25.v);
            ((S_800A871C_1 *)object)->unk_A0 = (s16) ((u16) ((S_800A871C_1 *)object)->unk_A0 + 1);
            launch_source = (*(void * volatile *)((u8 *)object_data + (0x60)));
            travel_steps = (*(s16 *)((u8 *)object_data + (0x8A)));
            launch_heading = launch_source->unk_2A;
            (*(s16 *)((u8 *)object_data + (0x6A))) = (s16) launch_heading;
            direction = (launch_heading >> 9) & 7;
            if (travel_steps != 0) {
                s16 *x_steps = (s16 *)&D_8006CCD8;
                dir_offset = direction * 2;
                y_steps = (u8 *)&D_8006CCE8;
                y_step = (u8 *)((unsigned long)dir_offset + (unsigned long)y_steps);
                target_height = func_800BCB04((((((S_800A871C_4 *)tile)->unk_24.n + (*(s16 *)((u8 *)x_steps + dir_offset) * travel_steps)) << 6) + 0x20) & 0xFFE0, (((((S_800A871C_4 *)tile)->unk_25.n + (((S_800A871C_6 *)y_step)->unk_00 * travel_steps)) << 6) + 0x20) & 0xFFE0, ((S_800A871C_3 *)motion)->unk_08.at02.v);
                if (target_height < 0x200) {
                    height_delta = target_height - ((S_800A871C_3 *)motion)->unk_08.at02.v;
                } else {
                    target_height = ((S_800A871C_3 *)motion)->unk_08.at02.v;
                    height_delta = ((S_800A871C_19 *)((*(void **)((u8 *)object_data + (0x60)))))->unk_88;
                    height_delta -= target_height;
                }
                ((S_800A871C_3 *)motion)->unk_14 = (s32) (height_delta << 0xF) / (s16) (*(u16 *)((u8 *)object_data + (0x8A)));
            }
            launch_x_steps = (u8 *)&D_8006CCD8;
            launch_dir_offset = direction * 2;
            ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_4 *)tile)->unk_24.n + ((S_800A871C_7 *)((u8 *)((unsigned long)launch_dir_offset + (unsigned long)launch_x_steps)))->unk_00);
            launch_y_step = (u8 *)&D_8006CCE8 + launch_dir_offset;
            ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_4 *)tile)->unk_25.n + ((S_800A871C_8 *)launch_y_step)->unk_00);
            ((S_800A871C_1 *)object)->unk_A4 = 2;
            return;
        }
        source_sprite = ((S_800A871C_1 *)object)->unk_90;
        if ((func_8003DE58(source_sprite->unk_08, source_sprite, offset, 0) != 0) && ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x80000)) {
            ((S_800A871C_1 *)object)->unk_A2 = 1;
            ((S_800A871C_3 *)motion)->unk_00.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)object)->unk_8C))->unk_02 + offset[0]);
            ((S_800A871C_3 *)motion)->unk_04.at02.v = (s16) (((S_800A871C_21 *)(((S_800A871C_1 *)object)->unk_8C))->unk_06 + offset[1]);
            source_height = ((S_800A871C_21 *)(((S_800A871C_1 *)object)->unk_8C))->unk_0A + offset[2];
            height_source = D_800814A8;
            ((S_800A871C_3 *)motion)->unk_08.at02.v = (s16) (source_height + 8);
            (*(u16 *)((u8 *)object_data + (0x88))) = ((S_800A871C_10 *)height_source)->unk_88;
            goto load_world_page;
        }
        if (((S_800A871C_1 *)object)->unk_A2 != 0) {
            if ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x80000) {
                world_page = (u8 *)0x800E0000;
                goto check_completion;
            }
            {
                drop_source = (*(void **)((u8 *)object_data + (0x60)));
                drop_x_steps = (u8 *)&D_8006CCD8;
                drop_heading = ((S_800A871C_11 *)drop_source)->unk_2A;
                drop_sprite = ((S_800A871C_11_pre *)drop_source)[-1].unk_00;
                (*(s16 *)((u8 *)object_data + (0x6A))) = (s16) drop_heading;
                drop_dir_offset = (drop_heading >> 8) & 0xE;
                ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_12 *)drop_sprite)->unk_24 + ((S_800A871C_13 *)((u8 *)((unsigned long)drop_dir_offset + (unsigned long)drop_x_steps)))->unk_00);
                ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_12 *)drop_sprite)->unk_25 + ((S_800A871C_14 *)((u8 *)&D_8006CCE8 + drop_dir_offset))->unk_00);
                func_800A2B04(motion, ((S_800A871C_4 *)tile)->unk_24.v, ((S_800A871C_4 *)tile)->unk_25.v);
                drop_height = func_800BCB04((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)tile)->unk_25.n << 6) | 0x20, ((S_800A871C_3 *)motion)->unk_08.at02.v);
                if (drop_height >= 0x201) {
                    drop_height = (s16) (u16) ((S_800A871C_3 *)motion)->unk_08.at02.v;
                }
                func_800A7A7C(((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n, drop_height, ((S_800A871C_4 *)tile)->unk_08, ((S_800A871C_1 *)object)->unk_9C);
                ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
                dungeon_flags = D_800814A0[0];
                height = ((S_800A871C_3 *)motion)->unk_08.at02.v;
                D_800814A0[0] = (s32) (dungeon_flags | 0x8000);
                ((S_800A871C_3 *)motion)->unk_08.at02.v = func_800BCB04((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)tile)->unk_25.n << 6) | 0x20, height);
                func_800B66C8(motion);
                func_8009A028(object_data);
                return;
            }
load_world_page:
            world_page = (u8 *)0x800E0000;
check_completion:
            if (((S_800A871C_22 *)(((S_800A871C_15 *)world_page)->unk_3D7C))->unk_124 == 0) {
                void *finished_object = object_data;
                s8 *flags_page = DUNGEON_FLAGS_PAGE;
                s32 dungeon_flags;
                ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
                dungeon_flags = ((S_800A871C_16 *)flags_page)->unk_14A0;
                dungeon_flags |= 0x8000;
                func_8009A028((((S_800A871C_16 *)flags_page)->unk_14A0 = dungeon_flags, finished_object));
                return;
            }
            goto advance_position;
        }
        return;
    }
update_motion:
    move_ticks = ((S_800A871C_1 *)object)->unk_A4;
    if (move_ticks != 0) {
        axis_target = ((S_800A871C_4 *)tile)->unk_24.n;
        axis_origin = ((S_800A871C_3 *)motion)->unk_00.at02.v;
        axis_target <<= 6;
        axis_origin -= 0x20;
        ((S_800A871C_3 *)motion)->unk_0C = (s32) (((axis_target - axis_origin) << 0x10) / move_ticks);
        axis_target = ((S_800A871C_4 *)tile)->unk_25.n;
        axis_origin = ((S_800A871C_3 *)motion)->unk_04.at02.v;
        axis_origin -= 0x20;
        axis_target <<= 6;
        ((S_800A871C_3 *)motion)->unk_10 = (s32) (((axis_target - axis_origin) << 0x10) / (s16) ((S_800A871C_1 *)object)->unk_A4);
    }
    ticks_left = (u16) ((S_800A871C_1 *)object)->unk_A4 - 1;
    ((S_800A871C_1 *)object)->unk_A4 = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        goto advance_position;
    }
    hit_object = func_8009B25C(object_data, ((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n, (*(s16 *)((u8 *)object_data + (0x88))));
    if (hit_object != NULL) {
        if ((hit_object->unk_13 == 0x1F) && !(hit_object->unk_1C & 0x228) && (D_800DD7DC[0] != 0)) {
            hit_object->unk_14 = (s32) (hit_object->unk_14 | 0x800000);
            hit_object->unk_48 = ((S_800A871C_23 *)(((S_800A871C_1 *)object)->unk_9C))->unk_00;
            goto finish_collision;
        }
        if (func_80098920(hit_object, ((S_800A871C_1 *)object)->unk_9C, 0xD, object_data) != 0) {
finish_collision:
            ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            func_8009A028(object_data);
            D_80083460[5] = (u16) (D_80083460[5] - 1);
            return;
        }
    }
    if ((func_8009B164((*(s16 *)((u8 *)object_data + (0x6A))), motion, tile) << 0x10) != 0) {
        steps_left = (*(u16 *)((u8 *)object_data + (0x8A))) - 1;
        (*(u16 *)((u8 *)object_data + (0x8A))) = steps_left;
        if ((steps_left << 0x10) > 0) {
            func_800A2B04(motion, ((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n);
            next_x_steps = (u8 *)&D_8006CCD8;
            next_dir_offset = ((u16) (*(s16 *)((u8 *)object_data + (0x6A))) >> 8) & 0xE;
            ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_4 *)tile)->unk_24.n + ((S_800A871C_18 *)((u8 *)((unsigned long)next_dir_offset + (unsigned long)next_x_steps)))->unk_00);
            next_y_step = (u8 *)&D_8006CCE8 + next_dir_offset;
            ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_4 *)tile)->unk_25.n + *next_y_step);
            ((S_800A871C_1 *)object)->unk_A4 = 2;
            goto advance_position;
        }
    }
    land_height = func_800BCB04((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)tile)->unk_25.n << 6) | 0x20, ((S_800A871C_3 *)motion)->unk_08.at02.v);
    if (land_height >= 0x201) {
        land_height = (s16) (u16) ((S_800A871C_3 *)motion)->unk_08.at02.v;
    }
    func_800A7A7C(((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n, land_height, ((S_800A871C_4 *)tile)->unk_08, ((S_800A871C_1 *)object)->unk_9C);
    ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
    D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    func_8009A028(object_data);
    D_80083460[5] = (u16) (D_80083460[5] - 1);
advance_position:
    ((S_800A871C_3 *)motion)->unk_00.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_00.at00.v + ((S_800A871C_3 *)motion)->unk_0C);
    ((S_800A871C_3 *)motion)->unk_04.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_04.at00.v + ((S_800A871C_3 *)motion)->unk_10);
    ((S_800A871C_3 *)motion)->unk_08.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_08.at00.v + ((S_800A871C_3 *)motion)->unk_14);
}
