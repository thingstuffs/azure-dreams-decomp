#include "modules/dungeon_ovl_184c800.h"

/* The stack frame of the launch/trail states: a target point, a launch offset, a particle spec handed to func_800DBA90
 * and the particle's velocity vector (offsets are from the frame base; the frame starts at sp+0x20). */
typedef struct ParticleSpec {
    s16 *vec_a;         /* 0x40: both point at vel_x */
    s16 *vec_b;         /* 0x44 */
    s16 yaw;            /* 0x48 */
    s16 pad_4A;
    s16 pitch;          /* 0x4C */
    s16 pad_4E;
    s16 w0;             /* 0x50 */
    s16 w1;
    s16 w2;
    s16 pad_56;
    s16 flag;           /* 0x58 */
    s16 zero;           /* 0x5A */
} ParticleSpec;

typedef struct EffectFrame {
    s16 pad20;
    s16 target_x;       /* 0x22 */
    s16 pad24;
    s16 target_y;       /* 0x26 */
    union {
        s32 packed;
        struct { s16 pad28; s16 z; } half;
    } target_z;         /* 0x28 */
    u8 pad2C[12];
    s16 launch_x;       /* 0x38 */
    s16 launch_y;
    s16 launch_z;
    s16 pad3E;
    ParticleSpec spec;  /* 0x40 */
    u8 pad5C[4];
    s16 vel_x;          /* 0x60 */
    s16 vel_y;
    s16 vel_z;
    s16 pad66;
} EffectFrame;



/* Updates a projectile effect through launch, flight, impact particles, and fading. */
void func_8002401C(void *effect, void *motion, void *sprite) {
    EffectFrame frame;
    S_8182C800_2 *owner_object;
    s32 direction_x;
    s32 direction_y;
    s32 target_tile;
    s32 tile_origin_x;
    s32 start_x;
    s32 tile_origin_y;
    s32 heading;
    s32 start_y;
    u8 *launch_texture;
    s32 travel_x;
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
    s32 target_y;
    s32 state;
    s16 floor_height;
    s32 step_count;
    s32 coord;
    s16 height_offset;
    s32 direction_offset;
    s32 distance_fixed;
    s32 spread_decay;
    M2C_UNK accel_x;
    s32 distance_x;
    s32 motion_extent;
    s32 target;
    s32 accel_y;
    s32 base_travel;
    s32 elapsed_steps;
    s32 distance_sum;
    s32 distance_y_abs;
    s32 covered_distance;
    s32 step_index;
    s32 sprite_or_step_x;
    s32 step_y;
    u8 *trail_texture;
    u16 steps_left;
    s32 probe_y;
    s32 probe_x;
    u16 sprite_flags;
    S_8182C800_18 *burst_motion_x;
    S_8182C800_19 *burst_motion_y;
    S_8182C800_12 *trail_pos_z;
    S_8182C800_3 *target_x;
    S_8182C800_10 *trail_pos_x;
    S_8182C800_11 *trail_pos_y;
    S_8182C800_4 *owner_sprite;
    s32 sprite_work;
    S_8182C800_20 *burst_sprite;
    S_8182C800_15 *particle;
    void *object;
    void *owner;
    s16 *direction_x_table;

    sprite_or_step_x = (s32) sprite;

    direction_x_table = dirStepX;
    owner = (*(void * *)&((EntityRec *)effect)->x);
    state = ((EntityRec *)effect)->z.w.i;
    owner_sprite = ((S_8182C800_1_pre *)owner)[-1].unk_00;

    motion_extent = (u16) ((S_8182C800_1 *)owner)->unk_2A.s >> 8;
    direction_offset = motion_extent & 0xE;
    direction_x = *(s16 *)((u8 *)direction_x_table + direction_offset);
    owner_object = owner - 0x20;
    sprite_work = *(s16 *)((u8 *)dirStepY + direction_offset);
    direction_y = (s32) ((s16)sprite_work);
    switch (state) {
    case 0:
        if (*(*(u16 * *)&((EntityRec *)effect)->y) & 0x80) {
            target_x = owner_object->unk_0C;
            if (func_8003DE58(target_x->unk_08, target_x, &frame.launch_x, 0) == 0) {
                frame.launch_y = 0;
                frame.launch_x = 0;
                height_offset = 0;
                if (owner_sprite->unk_14 & 0x8000) {
                    height_offset = -0x30;
                }
                frame.launch_z = height_offset;
            }
            ((S_8182C800_5 *)motion)->unk_00.at00.v = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_00
                + (frame.launch_x << 0x10));
            ((S_8182C800_5 *)motion)->unk_04.at00.v = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_04
                + (frame.launch_y << 0x10));
            ((S_8182C800_5 *)motion)->unk_08 = (s32) (((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at00.v
                + (frame.launch_z << 0x10));
            object = effect - 0x20;
            func_8004491C(object, func_80045340);
            ((S_8182C800_6 *)sprite_or_step_x)->unk_1E = 0x1000;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_1C = 0x1000;
            launch_texture = &D_800DEBD8;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_00 = launch_texture;
            launch_tpage = ((S_8182C800_7 *)launch_texture)->unk_04;
            sprite_color = 0x808080;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_0C = sprite_color;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_04 = 0;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_05 = 0;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_10 = 0x20;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_08 = launch_tpage;
            sprite_color = ((S_8182C800_6 *)sprite_or_step_x)->unk_14 | 0xC;
            ((S_8182C800_6 *)sprite_or_step_x)->unk_14 = sprite_color;
            target = func_800A05A4(owner, owner_sprite->unk_24, owner_sprite->unk_25, ((S_8182C800_1 *)owner)->unk_2A.u,
                (s16) (sprite_work = func_800A3820(5, launch_tpage)));
            ((S_8182C800_1 *)owner)->unk_60 = target;
            if (target == 0) {
                distance_sum = 0;
                step_y = 0;
                sprite_or_step_x = 0;
                while (distance_sum < func_800A3820(5)) {
                    tile_origin_x = (owner_sprite->unk_24 + sprite_or_step_x) << 6;
                    distance_x = tile_origin_x + 0x20;
                    tile_origin_y = (owner_sprite->unk_25 + step_y) << 6;
                    motion_extent = tile_origin_y + 0x20;
                    probe_y = (u16) motion_extent;
                    probe_x = (u16)distance_x;
                    if ((func_800A4688(probe_x, probe_y, (s16)func_800BCB04(probe_x, probe_y, -0x400),
                        ((S_8182C800_1 *)owner)->unk_2A.u, ((S_8182C800_1 *)owner)->unk_60) << 0x10) != 0) {
                        break;
                    }
                    step_y += direction_y;
                    distance_sum += 1;
                    sprite_or_step_x += direction_x;
                }
                ((S_8182C800_1 *)owner)->unk_72.s = (u8) (owner_sprite->unk_24 + (direction_x * distance_sum));
                ((S_8182C800_1 *)owner)->unk_73.s = (u8) (owner_sprite->unk_25 + (direction_y * distance_sum));
            } else {
                object = target - 0x20;
                sprite_work = (s32)((S_8182C800_8 *)object)->unk_0C;
                if ((((S_8182C800_9 *)sprite_work)->unk_14 & 0x8000) && (((S_8182C800_6 *)sprite_or_step_x)->unk_14 & 0x8000)) {
                    func_8009CE1C(((S_8182C800_1 *)owner)->unk_60, 8, (*(u8 *)((u8 *)&((EntityRec *)effect)->z + 1)), 2,
                        (s32) ((S_8182C800_1 *)owner)->unk_2A.u, owner, 2);
                    ((EntityRec *)effect)->z.w.i = 4;
                    return;
                }
                ((S_8182C800_1 *)owner)->unk_72.s = (u8) ((S_8182C800_9 *)sprite_work)->unk_24;
                ((S_8182C800_1 *)owner)->unk_73.s = (u8) ((S_8182C800_9 *)sprite_work)->unk_25;
            }
            target_tile = ((S_8182C800_1 *)owner)->unk_72.u;

            frame.target_x = (target_tile << 6) + 0x20;
            target_tile = ((S_8182C800_1 *)owner)->unk_73.u;

            frame.target_y = (target_tile << 6) + 0x20;
            if (((S_8182C800_1 *)owner)->unk_60 == 0) {
                floor_height = (s16)func_800BCB04((u16) frame.target_x, (u16) frame.target_y,
                    (s16) (((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at02.v - 0x30));
                frame.target_z.half.z = floor_height;
                if (floor_height >= 0x200) {
                    frame.target_z.half.z = ((S_8182C800_23 *)(owner_object->unk_08))->unk_08.at02.v;
                }
                frame.target_z.half.z -= 0x30;
            } else {
                frame.target_z.half.z = ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at02.v - 0x28;
            }
            target_x = (S_8182C800_3 *)frame.target_x;
            start_x = ((S_8182C800_5 *)motion)->unk_00.at02.v;
            target_y = frame.target_y;
            start_y = ((S_8182C800_5 *)motion)->unk_04.at02.v;
            distance_x = ((s32)target_x) - start_x;
            motion_extent = target_y - start_y;
            distance_sum = __builtin_abs(distance_x);
            distance_y_abs = __builtin_abs(motion_extent);
            if (distance_sum < distance_y_abs) {
                distance_sum = distance_y_abs;
            }
            covered_distance = 0;
            distance_fixed = distance_sum << 0x10;
            ((EntityRec *)effect)->unk_50 = 0U;
            if (distance_fixed > 0) {
                do {
                    covered_distance += 0xD6666;
                    ((EntityRec *)effect)->unk_50 = (u16) (((EntityRec *)effect)->unk_50 + 1);
                } while (covered_distance < distance_fixed);
            }
            distance_sum = 0;
            step_count = (s16) ((EntityRec *)effect)->unk_50;
            step_index = 1;
            if (step_count > 0) {
                step_limit = step_count;
                do {
                    distance_sum += step_index;
                } while (step_limit >= ++step_index);
            }
            base_travel = (s16) ((EntityRec *)effect)->unk_50 * 0x66666;
            travel_x = direction_x * base_travel;
            accel_x = (s32) ((distance_x << 0x10) - travel_x) / distance_sum;
            (*(s32 *)&((EntityRec *)effect)->unk_44) = accel_x;
            base_travel = (s16) ((EntityRec *)effect)->unk_50 * 0x66666;
            accel_y = (s32) ((s32) ((motion_extent << 0x10) - (direction_y * base_travel)) / distance_sum);
            (*(s32 *)&((EntityRec *)effect)->unk_48) = accel_y;
            ((EntityRec *)effect)->unk_4C = (s32) ((s32) ((s32) frame.target_z.packed
                - ((S_8182C800_5 *)motion)->unk_08) / distance_sum);
            ((S_8182C800_5 *)motion)->unk_0C = (s32) ((direction_x * 0x66666)
                + ((s16) ((EntityRec *)effect)->unk_50 * (*(s32 *)&((EntityRec *)effect)->unk_44)));
            ((S_8182C800_5 *)motion)->unk_10 = (s32) ((direction_y * 0x66666)
                + ((s16) ((EntityRec *)effect)->unk_50 * (*(s32 *)&((EntityRec *)effect)->unk_48)));
            ((S_8182C800_5 *)motion)->unk_14 =
                (s32) ((s16) ((EntityRec *)effect)->unk_50 * ((s32)((EntityRec *)effect)->unk_4C));
            ((EntityRec *)effect)->unk_52 = (u16) ((EntityRec *)effect)->unk_50;
            ((s32 (*)(s32, s32))func_800A56E0)(0x300, accel_x);
            ((EntityRec *)effect)->z.w.i += 1;
            return;
        }
        return;
    case 1:
        distance_x = 0x14;
        trail_texture = D_800DEC28;
spawn_trail:
        object = func_8003FD64(0x312, (ObjectNodeHeader **)&D_80083498);
        if (object != NULL) {
            sprite_work = (s32)(((S_8182C800_8 *)object)->unk_0C);
            ((S_8182C800_8 *)object)->unk_10 = (void *)func_80024D44;
            frame.vel_x = 0 - ((motion_extent = func_80069EF8()) & 0x1FF);
            frame.vel_z = 0;
            frame.vel_y = 0;
            frame.spec.vec_a = &frame.vel_x;
            frame.spec.vec_b = &frame.vel_x;
            elapsed_steps = (s16) ((EntityRec *)effect)->unk_52 - (s16) ((EntityRec *)effect)->unk_50;
            spread_decay = elapsed_steps * 8;
            spread_base = 0x300 - spread_decay;
            motion_extent = spread_base - (elapsed_steps << 5);
            particle = object + 0x20;
            if (motion_extent < 0x40) {
                motion_extent = 0x40;
            }
            frame.spec.yaw = (func_80069EF8() & 0xFF) - 0x80;
            frame.spec.pitch = (func_80069EF8() & 0xFF) - 0x80;
            angle_offset = frame.spec.yaw;
            if (angle_offset <= 0) {
                spread_angle = angle_offset - motion_extent;
            } else {
                spread_angle = angle_offset + motion_extent;
            }
            angle_offset = frame.spec.pitch;
            frame.spec.yaw = spread_angle;
            heading = ((S_8182C800_1 *)owner)->unk_2A.u;
            if (angle_offset <= 0) {
                spread_angle = heading - motion_extent;
            } else {
                spread_angle = motion_extent + heading;
            }
            coord = angle_offset + spread_angle;
            frame.spec.pitch = coord;
            frame.spec.w0 = 0;
            frame.spec.w1 = 0;
            frame.spec.w2 = 0;
            frame.spec.flag = 1;
            frame.spec.zero = 0;
            func_800DBA90(&frame.spec);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_00 =
                (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v + ((((motion_extent = func_80069EF8()) & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_04 =
                (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v + ((((motion_extent = func_80069EF8()) & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at00.v =
                (s32) (((S_8182C800_5 *)motion)->unk_08 + ((((motion_extent = func_80069EF8()) & 0x1FF) - 0xFF) << 9));
            trail_pos_x = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_x->unk_00 = (s32) (trail_pos_x->unk_00 + ((frame.vel_x << 0xC) + (direction_x << 0x15)));
            trail_pos_y = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_y->unk_04 = (s32) (trail_pos_y->unk_04 + ((frame.vel_y << 0xC) + (direction_y << 0x15)));
            trail_pos_z = ((S_8182C800_8 *)object)->unk_08;
            trail_pos_z->unk_08 = (s32) (trail_pos_z->unk_08 + (frame.vel_z << 0xC));
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_0C =
                (s32) ((s32) ((S_8182C800_5 *)motion)->unk_0C >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_10 =
                (s32) ((s32) ((S_8182C800_5 *)motion)->unk_10 >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_14 =
                (s32) ((s32) ((S_8182C800_5 *)motion)->unk_14 >> 3);
            ((S_8182C800_13 *)sprite_work)->unk_1E = 0x800;
            ((S_8182C800_13 *)sprite_work)->unk_1C = 0x800;
            ((S_8182C800_13 *)sprite_work)->unk_10 = 0x60;
            ((S_8182C800_13 *)sprite_work)->unk_00 = trail_texture;
            ((S_8182C800_13 *)sprite_work)->unk_14 = (u16) (((S_8182C800_13 *)sprite_work)->unk_14 | 0xC);
            ((S_8182C800_13 *)sprite_work)->unk_08 = (s32) ((S_8182C800_14 *)trail_texture)->unk_04;
            ((S_8182C800_13 *)sprite_work)->unk_04 = 0;
            ((S_8182C800_13 *)sprite_work)->unk_05 = 0;
            ((S_8182C800_13 *)sprite_work)->unk_0C = 0x808080;
            particle->unk_00 = effect;
            particle->unk_48 = (s16) ((sprite_work = func_80069EF8()) & 3);
            particle->unk_4C = 0;
        }
        distance_x -= 1;
        if (distance_x < 0) {
            ((S_8182C800_5 *)motion)->unk_0C = (s32) (((S_8182C800_5 *)motion)->unk_0C
                - (*(s32 *)&((EntityRec *)effect)->unk_44));
            ((S_8182C800_5 *)motion)->unk_10 = (s32) (((S_8182C800_5 *)motion)->unk_10
                - (*(s32 *)&((EntityRec *)effect)->unk_48));
            ((S_8182C800_5 *)motion)->unk_14 = (s32) (((S_8182C800_5 *)motion)->unk_14
                - ((s32)((EntityRec *)effect)->unk_4C));
            ((S_8182C800_5 *)motion)->unk_00.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v
                + ((S_8182C800_5 *)motion)->unk_0C);
            ((S_8182C800_5 *)motion)->unk_04.at00.v = (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v
                + ((S_8182C800_5 *)motion)->unk_10);
            ((S_8182C800_5 *)motion)->unk_08 = (s32) (((S_8182C800_5 *)motion)->unk_08
                + ((S_8182C800_5 *)motion)->unk_14);
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
            steps_left = ((EntityRec *)effect)->unk_50 - 1;
            ((EntityRec *)effect)->unk_50 = steps_left;
            coord = ((S_8182C800_5 *)motion)->unk_00.at02.v;
            if (coord < 0) {
                coord += 0x3F;
            }
            if (((coord >> 6) == (s8) ((S_8182C800_1 *)owner)->unk_72.s
                    && ((S_8182C800_5 *)motion)->unk_04.at02.v / 64 == (s8) ((S_8182C800_1 *)owner)->unk_73.s
                    && (s16) steps_left < 0)
                || (s16) ((EntityRec *)effect)->unk_50 < -0x20) {
                if (((S_8182C800_1 *)owner)->unk_60 == 0) {
                    ((EntityRec *)effect)->z.w.i = 3;
                    return;
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
                ((EntityRec *)effect)->z.w.i += 1;
                return;
            }
        } else {
            goto spawn_trail;
        }
        return;
    case 2:
        func_800478B8((void *) sprite_or_step_x);
        if (((S_8182C800_6 *)sprite_or_step_x)->unk_14 & 0x6000) {
            if (((S_8182C800_1 *)owner)->unk_60 != 0) {
                func_8009CE1C(((S_8182C800_1 *)owner)->unk_60, 0xA, (*(u8 *)((u8 *)&((EntityRec *)effect)->z + 1)), 2,
                    (s32) ((S_8182C800_1 *)owner)->unk_2A.u, owner, 2);
                distance_x = 0x50;
                do {
                    object = func_8003FD64(0x312, (ObjectNodeHeader **)&D_80083498);
                    if (object != NULL) {
                        burst_sprite = ((S_8182C800_8 *)object)->unk_0C;
                        ((S_8182C800_8 *)object)->unk_10 = (void *)func_80024E98;
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_00 =
                            (s32) (((S_8182C800_5 *)motion)->unk_00.at00.v
                                + ((((sprite_work = func_80069EF8()) & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_04 =
                            (s32) (((S_8182C800_5 *)motion)->unk_04.at00.v
                                + ((((sprite_work = func_80069EF8()) & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_08.at00.v =
                            (s32) (((S_8182C800_5 *)motion)->unk_08 + ((((sprite_work = func_80069EF8()) & 0x3FF) - 0x1FF) << 0xC));
                        burst_motion_x = ((S_8182C800_8 *)object)->unk_08;
                        burst_motion_x->unk_0C = (s32) ((s32) (((S_8182C800_5 *)motion)->unk_00.at00.v
                            - burst_motion_x->unk_00) >> 3);
                        burst_motion_y = ((S_8182C800_8 *)object)->unk_08;
                        burst_motion_y->unk_10 = (s32) ((s32) (((S_8182C800_5 *)motion)->unk_04.at00.v
                            - burst_motion_y->unk_04) >> 3);
                        ((S_8182C800_24 *)(((S_8182C800_8 *)object)->unk_08))->unk_14 =
                            (s32) (0 - (((sprite_work = func_80069EF8()) & 0x3FF) << 9));
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
                        particle->unk_48 = (s16) ((motion_extent = func_80069EF8()) & 3);
                    }
                    distance_x -= 1;
                } while (distance_x >= 0);
            }
            ((EntityRec *)effect)->z.w.i += 1;
            return;
        }
        return;
    case 3:
        ((S_8182C800_6 *)sprite_or_step_x)->unk_0C = (s32) (((S_8182C800_6 *)sprite_or_step_x)->unk_0C + 0xFFEFEFF0);
        if ((u8) ((S_8182C800_6 *)sprite_or_step_x)->unk_0C == 0) {
            ((EntityRec *)effect)->z.w.i += 1;
            return;
        }
        return;
    case 4:
        effect_flags = ((EntityRec *)effect)->unk_0C;
        if (effect_flags & 0x8000) {
            ((EntityRec *)effect)->unk_0C = effect_flags & 0xFFFF7FFF;
            return;
        }
        dungeonStatus.unk_0C = 0;
        ((S_8182C800_0_pre *)effect)[-1].unk_00 = (u16) (((S_8182C800_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((S_8182C800_22 *)((s32 *)(&objectFlagBlock)))->unk_00 =
            (s32) (((S_8182C800_22 *)((s32 *)(&objectFlagBlock)))->unk_00 | 0x8000);
        return;
    }
}
