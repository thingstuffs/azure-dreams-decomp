#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8182C800_0_pre {
    u16 unk_00;
} S_8182C800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */


typedef struct S_8182C800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8182C800_1_pre;   /* the 0x14 bytes before temp_s7 in BODY_NAME, addressed as temp_s7[-1] */

typedef struct S_8182C800_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8182C800_1;   /* temp_s7 in BODY_NAME */

typedef struct S_8182C800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8182C800_2;   /* sp68 in BODY_NAME */

typedef struct S_8182C800_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_3;   /* temp_a1_2 in BODY_NAME */

typedef struct S_8182C800_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8182C800_4;   /* temp_fp in BODY_NAME */

typedef struct S_8182C800_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182C800_5;   /* arg1 in BODY_NAME */

typedef struct S_8182C800_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_6;   /* work_s5 in BODY_NAME */

typedef struct S_8182C800_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_7;   /* page_a in BODY_NAME */

typedef struct S_8182C800_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8182C800_8;   /* temp_s4 in BODY_NAME */

typedef struct S_8182C800_9 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8182C800_9;   /* temp_s0_2 in BODY_NAME */

typedef struct S_8182C800_10 {
    s32 unk_00;
} S_8182C800_10;   /* temp_a1_3 in BODY_NAME */

typedef struct S_8182C800_11 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_11;   /* temp_a1_4 in BODY_NAME */

typedef struct S_8182C800_12 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_12;   /* temp_a0_7 in BODY_NAME */

typedef struct S_8182C800_13 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_13;   /* temp_s0_3 in BODY_NAME */

typedef struct S_8182C800_14 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_14;   /* state1_tex in BODY_NAME */

typedef struct S_8182C800_15 {
    void * unk_00;
    u8 pad_04[0x44];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_8182C800_15;   /* temp_s3 in BODY_NAME */

typedef struct S_8182C800_16 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_16;   /* page_e in BODY_NAME */

typedef struct S_8182C800_17 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_17;   /* page_b in BODY_NAME */

typedef struct S_8182C800_18 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8182C800_18;   /* temp_a0_11 in BODY_NAME */

typedef struct S_8182C800_19 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8182C800_19;   /* temp_a0_12 in BODY_NAME */

typedef struct S_8182C800_20 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_20;   /* temp_s0_4 in BODY_NAME */

typedef struct S_8182C800_21 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_21;   /* page_d in BODY_NAME */

typedef struct S_8182C800_22 {
    s32 unk_00;
} S_8182C800_22;   /* D_800814A0 in BODY_NAME */

typedef struct S_8182C800_23 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8182C800_23;   /* ((S_8182C800_2 *)sp68)->unk_08 in BODY_NAME */

typedef struct S_8182C800_24 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182C800_24;   /* ((S_8182C800_8 *)temp_s4)->unk_08 in BODY_NAME */


#ifdef __mips__
static const u32 data_bank[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C, 0x00000000,
    0x800240C8, 0x8002467C, 0x80024AB0,
    0x80024C78, 0x80024CB8,
};
__asm__(".globl func_80024000\n.size func_80024000,3396");
#define BODY_NAME func_8002401C
#else
#define BODY_NAME func_80024000
#endif

/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_800DEC28[];
extern u8 D_800DEC00[];
extern s32 D_800DEB70;
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
s32 func_8003DE58();     /* extern */
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8(void);            /* extern */
void func_800478B8(void *);          /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A05A4();        /* extern */
s32 func_800A3820();                    /* extern */
s32 func_800A4688();         /* extern */
M2C_UNK func_800A56E0();                /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024D44;
extern M2C_UNK D_80024E98;
extern u8 D_800DEBD8;
extern void *D_80024008[];

typedef struct Func80024000Frame {
    s16 pad20;
    s16 sp22;
    s16 pad24;
    s16 sp26;
    union {
        s32 sp28;
        struct { s16 pad28; s16 sp2A; } half;
    } u28;
    u8 pad2C[12];
    s16 sp38;
    s16 sp3A;
    s16 sp3C;
    s16 pad3E;
    s16 *sp40;
    s16 *sp44;
    s16 sp48;
    s16 pad4A;
    s16 sp4C;
    s16 pad4E;
    s16 sp50;
    s16 sp52;
    s16 sp54;
    s16 pad56;
    s16 sp58;
    s16 sp5A;
    u8 pad5C[4];
    s16 sp60;
    s16 sp62;
    s16 sp64;
    s16 pad66;
} Func80024000Frame;

void BODY_NAME(void *effect, void *motion, void *sprite) __attribute__((section(".text.func_80024000")));
/* Updates a projectile effect through launch, flight, impact particles, and fading. */
void BODY_NAME(void *effect, void *motion, void *sprite) {
    Func80024000Frame frame;
    S_8182C800_2 *owner_object;
    s32 direction_x;
    s32 direction_y;
    s32 target_tile;
    register s32 tile_origin_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tile_origin_y;
    s32 heading;
    register s32 start_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 start_y;
    u8 *launch_texture;
    s32 travel_x;
    void *effect_alias;
    s32 spread_angle;
    s32 target_tile_y;
    u8 *flight_texture;
    s32 flight_tpage;
    u8 *hit_texture;
    s32 hit_tpage;
    s32 step_limit;
    u8 *burst_texture;
    s32 burst_tpage;
    s32 spread_base;
    s32 launch_tpage;
    s32 sprite_color;
    s32 angle_offset;
    s32 effect_flags;
    s16 direction_y_entry;
    s32 target_x;
    s32 target_y;
    s32 state;
    s16 floor_height;
    s32 step_count;
    s32 coord;
    s32 tile_y_coord;
    s16 height_offset;
    s32 direction_offset;
    s32 distance_fixed;
    s32 spread_decay;
    M2C_UNK accel_x;
    register s32 distance_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 motion_extent;
    s32 target;
    s32 accel_y;
    s32 base_travel;
    s32 elapsed_steps;
    s32 trail_count;
    s32 burst_count;
    register s32 distance_sum ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 step_sum;
    s32 distance_y_abs;
    s32 covered_distance;
    s32 step_index;
    register s32 move_count ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 sprite_or_step_x;
    s32 step_y;
    u8 *trail_texture;
    u16 steps_left;
    s32 probe_y_full;
    s32 probe_y;
    register u16 probe_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 sprite_flags;
    S_8182C800_18 *burst_motion_x;
    S_8182C800_19 *burst_motion_y;
    S_8182C800_12 *trail_pos_z;
    S_8182C800_3 *owner_model;
    S_8182C800_10 *trail_pos_x;
    S_8182C800_11 *trail_pos_y;
    S_8182C800_4 *owner_sprite;
    register S_8182C800_9 *target_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_8182C800_13 *trail_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8182C800_20 *burst_sprite;
    S_8182C800_15 *particle;
    void *object;
    void *owner;
    s16 *direction_x_table;

    sprite_or_step_x = (s32) sprite;

    direction_x_table = D_8006CCD8;
    owner = ((Rec_D_800E3D7C *)effect)->unk_00.at00_pv.v;
    state = ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v;
    owner_sprite = ((S_8182C800_1_pre *)owner)[-1].unk_00;

    motion_extent = (u16) ((S_8182C800_1 *)owner)->unk_2A.s >> 8;
    direction_offset = motion_extent & 0xE;
    direction_x = *(s16 *)((u8 *)direction_x_table + direction_offset);
    owner_object = owner - 0x20;
    direction_y_entry = *(s16 *)((u8 *)D_8006CCE8 + direction_offset);
    direction_y = (s32) direction_y_entry;
    if ((u32) state >= 5) {
        goto done;
    }
    {
        static void *const state_labels[] = {
            &&state_launch, &&state_flight, &&state_hit, &&state_fade, &&state_finish
        };
        (void) state_labels;
        goto *D_80024008[(u32) state];
    }
state_launch:
        if (*((Rec_D_800E3D7C *)effect)->unk_04.at00_pu16.v & 0x80) {
            owner_model = owner_object->unk_0C;
            if (func_8003DE58(owner_model->unk_08, owner_model, &frame.sp38, 0) == 0) {
                frame.sp3A = 0;
                frame.sp38 = 0;
                height_offset = 0;
                if (owner_sprite->unk_14 & 0x8000) {
                    height_offset = -0x30;
                }
                frame.sp3C = height_offset;
            }
            ((S_8182C800_5 *)motion)->unk_00.at00.v = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_00 + (frame.sp38 << 0x10));
            ((S_8182C800_5 *)motion)->unk_04.at00.v = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_04 + (frame.sp3A << 0x10));
            ((S_8182C800_5 *)motion)->unk_08 = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at00.v + (frame.sp3C << 0x10));
            object = effect - 0x20;
            func_8004491C(object, D_80045340);
            ((S_8182C800_6 *)sprite_or_step_x)->unk_1E = 0x1000;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_1C = 0x1000;
            launch_texture = &D_800DEBD8;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_00 = launch_texture;
            launch_tpage = ((S_8182C800_7 *)launch_texture)->unk_04;
            sprite_color = 0x808080;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_8182C800_6 *)sprite_or_step_x)->unk_0C = sprite_color;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_04 = 0;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_05 = 0;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_10 = 0x20;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_08 = launch_tpage;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_14 = (u16) (((S_8182C800_6 *)sprite_or_step_x)->unk_14 | 0xC);
            target = func_800A05A4(owner, owner_sprite->unk_24, owner_sprite->unk_25, ((S_8182C800_1 *)owner)->unk_2A.u, (s16) func_800A3820(5, launch_tpage));
            ((S_8182C800_1 *)owner)->unk_60 = target;
            if (target == 0) {
                move_count = 0;
                step_y = 0;
                sprite_or_step_x = 0;
                while (move_count < func_800A3820(5)) {
                    tile_origin_x = (owner_sprite->unk_24 + sprite_or_step_x) << 6;
                    ASM_KEEP_NV(tile_origin_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    probe_x = tile_origin_x + 0x20;
                    tile_origin_y = (owner_sprite->unk_25 + step_y) << 6;
                    probe_y_full = tile_origin_y + 0x20;
                    probe_y = (u16) probe_y_full;
                    if ((func_800A4688(probe_x, probe_y, func_800BCB04(probe_x, probe_y, -0x400), ((S_8182C800_1 *)owner)->unk_2A.u, ((S_8182C800_1 *)owner)->unk_60) << 0x10) != 0) {
                        break;
                    }
                    step_y += direction_y;
                    ASM_KEEP(probe_y_full);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    move_count += 1;
                    sprite_or_step_x += direction_x;
                }
                ((S_8182C800_1 *)owner)->unk_72.s = (u8) (owner_sprite->unk_24 + (direction_x * move_count));
                ((S_8182C800_1 *)owner)->unk_73.s = (u8) (owner_sprite->unk_25 + (direction_y * move_count));
            } else {
                object = target - 0x20;
                target_sprite = ((S_8182C800_8 *)object)->unk_0C;
                if ((target_sprite->unk_14 & 0x8000) && (((S_8182C800_6 *)sprite_or_step_x)->unk_14 & 0x8000)) {
                    func_8009CE1C(((S_8182C800_1 *)owner)->unk_60, 8, ((Rec_D_800E3D7C *)effect)->unk_08.at01_u8.v, 2, (s32) ((S_8182C800_1 *)owner)->unk_2A.u, owner, 2);
                    ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v = 4;
                    goto done;
                }
                ((S_8182C800_1 *)owner)->unk_72.s = (u8) target_sprite->unk_24;
                ((S_8182C800_1 *)owner)->unk_73.s = (u8) target_sprite->unk_25;
            }
            target_tile = ((S_8182C800_1 *)owner)->unk_72.u;

            frame.sp22 = (target_tile << 6) + 0x20;
            target_tile = ((S_8182C800_1 *)owner)->unk_73.u;

            frame.sp26 = (target_tile << 6) + 0x20;
            if (((S_8182C800_1 *)owner)->unk_60 == 0) {
                floor_height = func_800BCB04((u16) frame.sp22, (u16) frame.sp26, (s16) (((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at02.v - 0x30));
                frame.u28.half.sp2A = floor_height;
                if (floor_height >= 0x200) {
                    frame.u28.half.sp2A = ((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at02.v;
                }
                frame.u28.half.sp2A -= 0x30;
            } else {
                frame.u28.half.sp2A = ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at02.v - 0x28;
            }
            target_x = frame.sp22;
            start_x = ((S_8182C800_5 *)motion)->unk_00.at02.v;
            target_y = frame.sp26;
            start_y = ((S_8182C800_5 *)motion)->unk_04.at02.v;
            distance_x = target_x - start_x;
            motion_extent = target_y - start_y;
            ASM_SET(target_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            distance_sum = distance_x;
            if (distance_x < 0) {
                distance_sum = 0 - distance_sum;
            }
            distance_y_abs = __builtin_abs(motion_extent);
            if (distance_sum < distance_y_abs) {
                distance_sum = distance_y_abs;
            }
            covered_distance = 0;
            distance_fixed = distance_sum << 0x10;
            ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v = 0U;
            if (distance_fixed > 0) {
                do {
                    effect_alias = effect;
                    effect = effect_alias;
                    covered_distance += 0xD6666;
                    ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v = (u16) (((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v + 1);
                } while (covered_distance < distance_fixed);
            }
            ASM_USE_NV(distance_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            distance_sum = 0;
            step_count = (s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v;
            step_index = 1;
            if (step_count > 0) {
                step_limit = step_count;
                ASM_KEEP_NV(distance_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(step_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                step_sum = distance_sum + step_index;
                do {
                    step_index += 1;
                    step_sum += step_index;
                } while (step_limit >= step_index);
                distance_sum = step_sum - step_index;
            }
            base_travel = (s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v * 0x66666;
            travel_x = direction_x * base_travel;
            accel_x = (s32) ((distance_x << 0x10) - travel_x) / distance_sum;
            ((Rec_D_800E3D7C *)effect)->unk_44.at00_s32.v = accel_x;
            base_travel = (s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v * 0x66666;
            accel_y = (s32) ((s32) ((motion_extent << 0x10) - (direction_y * base_travel)) / distance_sum);
            ((Rec_D_800E3D7C *)effect)->unk_48.at00_s32.v = accel_y;
            ((Rec_D_800E3D7C *)effect)->unk_4C.as_s32 = (s32) ((s32) ((s32) frame.u28.sp28 - ((S_8182C800_5 *)motion)->unk_08) / distance_sum);
            ((S_8182C800_5 *)motion)->unk_0C = (s32) ((direction_x * 0x66666) + ((s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)effect)->unk_44.at00_s32.v));
            ((S_8182C800_5 *)motion)->unk_10 = (s32) ((direction_y * 0x66666) + ((s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)effect)->unk_48.at00_s32.v));
            ((S_8182C800_5 *)motion)->unk_14 = (s32) ((s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)effect)->unk_4C.as_s32);
            ((Rec_D_800E3D7C *)effect)->unk_50.at02_u16.v = (u16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v;
            func_800A56E0(0x300, accel_x);
            ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v += 1;
            goto done;
        }
        goto done;
state_flight:
        trail_count = 0x14;
        trail_texture = D_800DEC28;
spawn_trail:
        object = func_8003FD64(0x312, D_80083498);
        if (object != NULL) {
            trail_sprite = ((S_8182C800_8 *)object)->unk_0C;
            ((S_8182C800_8 *)object)->unk_10 = &D_80024D44;
            frame.sp60 = 0 - (func_80069EF8() & 0x1FF);
            frame.sp64 = 0;
            frame.sp62 = 0;
            frame.sp40 = &frame.sp60;
            frame.sp44 = &frame.sp60;
            elapsed_steps = (s16) ((Rec_D_800E3D7C *)effect)->unk_50.at02_u16.v - (s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v;
            spread_decay = elapsed_steps * 8;
            spread_base = 0x300 - spread_decay;
            motion_extent = spread_base - (elapsed_steps << 5);
            particle = object + 0x20;
            if (motion_extent < 0x40) {
                motion_extent = 0x40;
            }
            frame.sp48 = (func_80069EF8() & 0xFF) - 0x80;
            frame.sp4C = (func_80069EF8() & 0xFF) - 0x80;
            angle_offset = frame.sp48;
            if (angle_offset <= 0) {
                spread_angle = angle_offset - motion_extent;
            } else {
                spread_angle = angle_offset + motion_extent;
            }
            angle_offset = frame.sp4C;
            frame.sp48 = spread_angle;
            heading = ((S_8182C800_1 *)owner)->unk_2A.u;
            if (angle_offset <= 0) {
                spread_angle = heading - motion_extent;
            } else {
                spread_angle = motion_extent + heading;
            }
            coord = angle_offset + spread_angle;
            frame.sp4C = coord;
            frame.sp50 = 0;
            frame.sp52 = 0;
            frame.sp54 = 0;
            frame.sp58 = 1;
            frame.sp5A = 0;
            func_800DBA90(&frame.sp40);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_00 = (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_04 = (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_08 + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            trail_pos_x = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_x->unk_00 = (s32) (trail_pos_x->unk_00 + ((frame.sp60 << 0xC) + (direction_x << 0x15)));
            trail_pos_y = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_y->unk_04 = (s32) (trail_pos_y->unk_04 + ((frame.sp62 << 0xC) + (direction_y << 0x15)));
            trail_pos_z = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_z->unk_08 = (s32) (trail_pos_z->unk_08 + (frame.sp64 << 0xC));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_0C = (s32) ((s32) ((S_8182C800_5 *)motion)->unk_0C >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_10 = (s32) ((s32) ((S_8182C800_5 *)motion)->unk_10 >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_14 = (s32) ((s32) ((S_8182C800_5 *)motion)->unk_14 >> 3);
            trail_sprite->unk_1E = 0x800;
            trail_sprite->unk_1C = 0x800;
            trail_sprite->unk_10 = 0x60;
            trail_sprite->unk_00 = trail_texture;
            trail_sprite->unk_14 = (u16) (trail_sprite->unk_14 | 0xC);
            trail_sprite->unk_08 = (s32) ((S_8182C800_14 *)trail_texture)->unk_04;
            trail_sprite->unk_04 = 0;
            trail_sprite->unk_05 = 0;
            trail_sprite->unk_0C = 0x808080;
            particle->unk_00 = effect;
            particle->unk_48 = (s16) (func_80069EF8() & 3);
            particle->unk_4C = 0;
            goto next_trail;
        }
next_trail:
        trail_count -= 1;
        if (trail_count < 0) {
            ((S_8182C800_5 *)motion)->unk_0C = (s32) (((S_8182C800_5 *)motion)->unk_0C - ((Rec_D_800E3D7C *)effect)->unk_44.at00_s32.v);
            ((S_8182C800_5 *)motion)->unk_10 = (s32) (((S_8182C800_5 *)motion)->unk_10 - ((Rec_D_800E3D7C *)effect)->unk_48.at00_s32.v);
            ((S_8182C800_5 *)motion)->unk_14 = (s32) (((S_8182C800_5 *)motion)->unk_14 - ((Rec_D_800E3D7C *)effect)->unk_4C.as_s32);
            ((S_8182C800_5 *)motion)->unk_00.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v + ((S_8182C800_5 *)motion)->unk_0C);
            ((S_8182C800_5 *)motion)->unk_04.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v + ((S_8182C800_5 *)motion)->unk_10);
            ((S_8182C800_5 *)motion)->unk_08 = (s32) (((S_8182C800_5 *)motion)->unk_08 + ((S_8182C800_5 *)motion)->unk_14);
            func_800478B8((void *) sprite_or_step_x);
            sprite_flags = ((S_8182C800_6 *)sprite_or_step_x)->unk_14;
            if (sprite_flags & 0x6000) {
                ((S_8182C800_6 *)sprite_or_step_x)->unk_14 = (u16) (sprite_flags & 0x9FFF);
                flight_texture = D_800DEC00;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_00 = flight_texture;
                flight_tpage = ((S_8182C800_16 *)flight_texture)->unk_04;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_04 = 0;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_05 = 0;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_08 = flight_tpage;
            }
            steps_left = ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v - 1;
            ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v = steps_left;
            coord = ((S_8182C800_5 *)motion)->unk_00.at02.v;
            if (coord < 0) {
                coord += 0x3F;
            }
            if ((coord >> 6) == (s8) ((S_8182C800_1 *)owner)->unk_72.s) {
                tile_y_coord = ((S_8182C800_5 *)motion)->unk_04.at02.v;
                if (tile_y_coord < 0) {
                    tile_y_coord += 0x3F;
                }
                if (((tile_y_coord >> 6) != (s8) ((S_8182C800_1 *)owner)->unk_73.s) || ((s16) steps_left >= 0)) {
                    goto check_timeout;
                }
                goto arrive;
            }
check_timeout:
            if ((s16) ((Rec_D_800E3D7C *)effect)->unk_50.at00_u16.v < -0x20) {
arrive:
                if (((S_8182C800_1 *)owner)->unk_60 == 0) {
                    ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v = 3;
                    goto done;
                }
                hit_texture = (u8 *) &D_800DEB70;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_00 = hit_texture;
                hit_tpage = ((S_8182C800_17 *)hit_texture)->unk_04;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_04 = 0;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_05 = 0;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_0C = 0xC0C0C0;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_10 = 0x20;
                ((S_8182C800_6 *)sprite_or_step_x)->unk_08 = hit_tpage;
                target_tile = ((S_8182C800_1 *)owner)->unk_72.u;

                ((S_8182C800_5 *)motion)->unk_00.at02.v = (s16) ((target_tile << 6) + 0x20);
                target_tile_y = ((S_8182C800_1 *)owner)->unk_73.u;
                ((S_8182C800_5 *)motion)->unk_14 = 0;
                ((S_8182C800_5 *)motion)->unk_10 = 0;
                ((S_8182C800_5 *)motion)->unk_0C = 0;
                ((S_8182C800_5 *)motion)->unk_04.at02.v = (s16) ((target_tile_y << 6) + 0x20);
                ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v += 1;
                goto done;
            }
        } else {
            goto spawn_trail;
        }
        goto done;
state_hit:
        func_800478B8((void *) sprite_or_step_x);
        if (((S_8182C800_6 *)sprite_or_step_x)->unk_14 & 0x6000) {
            if (((S_8182C800_1 *)owner)->unk_60 != 0) {
                func_8009CE1C(((S_8182C800_1 *)owner)->unk_60, 0xA, ((Rec_D_800E3D7C *)effect)->unk_08.at01_u8.v, 2, (s32) ((S_8182C800_1 *)owner)->unk_2A.u, owner, 2);
                burst_count = 0x50;
                do {
                    object = func_8003FD64(0x312, D_80083498);
                    if (object != NULL) {
                        burst_sprite = ((S_8182C800_8 *)object)->unk_0C;
                        ((S_8182C800_8 *)object)->unk_10 = &D_80024E98;
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_00 = (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_04 = (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_08 + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xC));
                        burst_motion_x = ((S_8182C800_8 *)object)->unk_08;
                        burst_motion_x->unk_0C = (s32) ((s32) (((S_8182C800_5 *)motion)->unk_00.at00.v - burst_motion_x->unk_00) >> 3);
                        burst_motion_y = ((S_8182C800_8 *)object)->unk_08;
                        burst_motion_y->unk_10 = (s32) ((s32) (((S_8182C800_5 *)motion)->unk_04.at00.v - burst_motion_y->unk_04) >> 3);
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_14 = (s32) (0 - ((func_80069EF8() & 0x3FF) << 9));
                        burst_sprite->unk_1E = 0x800;
                        burst_sprite->unk_1C = 0x800;
                        burst_sprite->unk_10 = 0x20;
                        burst_texture = D_800DEC28;
                        burst_sprite->unk_00 = burst_texture;
                        burst_sprite->unk_14 = (u16) (burst_sprite->unk_14 | 0xC);
                        burst_tpage = ((S_8182C800_21 *)burst_texture)->unk_04;
                        burst_sprite->unk_04 = 0;
                        burst_sprite->unk_05 = 0;
                        burst_sprite->unk_0C = 0x808080;
                        burst_sprite->unk_08 = burst_tpage;
                        ((S_8182C800_8 *)object)->unk_20 = effect;
                        particle = object + 0x20;
                        particle->unk_48 = (s16) (func_80069EF8() & 3);
                    }
                    burst_count -= 1;
                } while (burst_count >= 0);
            }
            ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v += 1;
            goto done;
        }
        goto done;
state_fade:
        ((S_8182C800_6 *)sprite_or_step_x)->unk_0C = (s32) (((S_8182C800_6 *)sprite_or_step_x)->unk_0C + 0xFFEFEFF0);
        if ((u8) ((S_8182C800_6 *)sprite_or_step_x)->unk_0C == 0) {
            ((Rec_D_800E3D7C *)effect)->unk_08.at02_s16.v += 1;
            goto done;
        }
        goto done;
state_finish:
        effect_flags = ((Rec_D_800E3D7C *)effect)->unk_0C.as_s32;
        if (effect_flags & 0x8000) {
            ((Rec_D_800E3D7C *)effect)->unk_0C.as_s32 = effect_flags & 0xFFFF7FFF;
            goto done;
        }
        *D_8008346C = 0;
        ((S_8182C800_0_pre *)effect)[-1].unk_00 = (u16) (((S_8182C800_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((S_8182C800_22 *)D_800814A0)->unk_00 = (s32) (((S_8182C800_22 *)D_800814A0)->unk_00 | 0x8000);
done:
        return;
}
