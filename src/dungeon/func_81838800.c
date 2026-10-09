#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])





/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_1858800_entry)(ProjectileState *, ProjectileMotion *, ProjectileSprite *) =
    func_80024020;

/* Updates a projectile effect, spawning particles and moving toward its target before impact and cleanup. */
void func_80024020(ProjectileState *effect, ProjectileMotion *motion, ProjectileSprite *effect_sprite)
{
    ProjectileActor *caster;
    s32 particle_or_y;
    s32 sprite_or_x;
    ProjectileParticle *particle_data;
    s32 index_or_x;
    s32 tile_dx;
    s32 tile_dy;
    FixedCoords target_pos;
    s16 launch_offset[3];
    ProjectileObject *caster_obj;
    ProjectileSprite *caster_sprite;
    ProjectileActor *target;
    s32 step_x;
    s32 step_y;
    s32 world_x;
    s32 range;
    s32 target_tile;
    s32 abs_dy;
    s32 world_y;
    s32 flags;
    s32 ground_z;
    s32 offset_y;
    s32 distance;
    s32 travel_frames;
    s32 state;

    u8 *direction_x = ((u8 *)dirStepX);
    s32 direction_offset;
    caster = effect->unk_00;
    target = (ProjectileActor *)caster->unk_2A.u;
    caster_obj = (ProjectileObject *)((u8 *)caster - 0x20);
    caster_sprite = ((ProjectileObject *)((u8 *)caster - 0x20))->unk_0C;
    direction_offset = ((u32)target) >> 8;
    direction_offset &= 0xE;
    step_x = *(s16 *)(direction_x + direction_offset);
    step_y = *(s16 *)(((u8 *)dirStepY) + direction_offset);

    if ((u32)(effect->unk_0A.u - 1) < 3) {
        index_or_x = 9;
        do {
            particle_or_y = (s32)func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (particle_or_y != 0) {
                sprite_or_x = (s32)((ProjectileObject *)particle_or_y)->unk_0C;
                ((ProjectileObject *)particle_or_y)->unk_10 = func_80024B58;
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_00.s =
                    motion->unk_00.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_04.s =
                    motion->unk_04.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_08.s =
                    motion->unk_08.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                if (effect->unk_0A.s == 2) {
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_0C =
                        motion->unk_0C >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_10 =
                        motion->unk_10 >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_00.s +=
                        (step_x << 21) -
                        (((step_x * effect->unk_0C.s) << 20) / 12);
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_04.s +=
                        (step_y << 21) -
                        (((step_y * effect->unk_0C.s) << 20) / 12);
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                } else {
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                }
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_14 = -func_80069EF8() << 1;
                ((ProjectileSprite *)sprite_or_x)->unk_1E = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_1C = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_14 |= 0xC;
                if (func_80069EF8() & 1) {
                    ((ProjectileSprite *)sprite_or_x)->unk_14 |= 1;
                }
                *(s16 *)((u8 *)sprite_or_x + 0x10) = 96;
                *(void * *)((u8 *)sprite_or_x + 0x00) = D_800DEA68;
                ((ProjectileSprite *)sprite_or_x)->unk_08 = *(void **)(D_800DEA68 + 4);
                ((ProjectileSprite *)sprite_or_x)->unk_04 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_05 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_0C.at00u.v = 0x3030C0;
                particle_data->unk_00 = effect;
                particle_data->unk_4C.u = 0;
                particle_data->unk_48 = func_80069EF8() & 3;
                particle_data->unk_4A = index_or_x + 40;
                particle_data->unk_04 = (s8)caster->unk_72.u;
                particle_data->unk_06 = (s8)caster->unk_73.u;
            }
            index_or_x--;
        } while (index_or_x >= 0);
    }

    effect->unk_50.u = effect->unk_50.u - 1;
    state = effect->unk_0A.s;
    switch (state) {
    case 0:
        if ((((AnimationFlags *)effect->unk_04)->unk_00 & 0x80) == 0) {
            return;
        }
        if (func_8003DE58(((ProjectileSprite *)caster_obj->unk_0C)->unk_08,
                          caster_obj->unk_0C, launch_offset, 0) == 0) {
            launch_offset[1] = 0;
            launch_offset[0] = 0;
            launch_offset[2] = (caster_sprite->unk_14 & 0x8000) ? -48 : 0;
        }
        motion->unk_00.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_00.s +
                              ((s32)launch_offset[0] << 16);
        motion->unk_04.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_04.s +
                              ((s32)launch_offset[1] << 16);
        motion->unk_08.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_08.s +
                              ((s32)launch_offset[2] << 16);
        func_8004491C((u8 *)effect - 0x20, func_800248F8);
        range = (s16)func_800A3820(7);
        offset_y = caster_sprite->unk_24;
        target = (void *)func_800A05A4(caster, offset_y,
                                       caster_sprite->unk_25,
                                       caster->unk_2A.s, range);
        caster->unk_60.p = target;
        if (target == 0) {
            distance = 0;
            tile_dy = distance;
            tile_dx = distance;
            while (distance < func_800A3820(7)) {
                index_or_x = (caster_sprite->unk_24 + tile_dx) * 64 + 32;
                offset_y = (caster_sprite->unk_25 + tile_dy) * 64 + 32;
                sprite_or_x = index_or_x & 0xFFFF;
                {
                    s32 probe_y;
                    direction_x = (u8 *)(sprite_or_x);
                    probe_y = offset_y & 0xFFFF;
                    ground_z = (s16)func_800BCB04((s32)direction_x, probe_y,
                                       (s16)(((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A - 128));
                }
                particle_or_y = offset_y & 0xFFFF;
                if ((s16)func_800A4688(sprite_or_x, particle_or_y, ground_z, caster->unk_2A.s,
                                  caster->unk_60.s) != 0) {
                    break;
                }
                tile_dy += step_y;
                distance++;
                tile_dx += step_x;
            }
            caster->unk_72.u = caster_sprite->unk_24 + step_x * distance;
            target_tile = caster_sprite->unk_25 + step_y * distance;
        } else {
            sprite_or_x = (s32)((ProjectileObject *)((u8 *)target - 0x20))->unk_0C;
            if ((((ProjectileSprite *)sprite_or_x)->unk_14 & 0x8000) && (effect_sprite->unk_14 & 0x8000)) {
                effect->unk_0A.s = 3;
                return;
            }
            caster->unk_72.u = ((ProjectileSprite *)sprite_or_x)->unk_24;
            target_tile = ((ProjectileSprite *)sprite_or_x)->unk_25;
        }
        caster->unk_73.u = target_tile;
        target_tile = caster->unk_72.s;
        HI16(target_pos.x) = (target_tile << 6) + 32;
        target_tile = caster->unk_73.s;
        HI16(target_pos.y) = (target_tile << 6) + 32;
        HI16(target_pos.z) = (s16)func_800BCB04(HI16U(target_pos.x), HI16U(target_pos.y),
                                           (s16)(((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A - 48));
        if (HI16(target_pos.z) >= 512) {
            HI16(target_pos.z) = ((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A;
        }
        HI16(target_pos.z) -= 48;
        index_or_x = HI16(target_pos.x) - motion->unk_00.h.unk_02;
        offset_y = HI16(target_pos.y) - motion->unk_04.h.unk_06;
        distance = index_or_x;
        distance = abs(distance);
        abs_dy = offset_y;
        abs_dy = abs(abs_dy);
        if (distance < abs_dy) {
            distance = abs_dy;
        }
        travel_frames = distance / 8;
        travel_frames++;
        effect->unk_50.s = travel_frames;
        motion->unk_0C = (index_or_x << 16) / effect->unk_50.s;
        motion->unk_10 = (offset_y << 16) / effect->unk_50.s;
        motion->unk_14 = (target_pos.z - motion->unk_08.s) /
                                 effect->unk_50.s;
        effect->unk_0C.s = 8;
        effect->unk_50.u = effect->unk_50.u + effect->unk_0C.u;
        func_800A56E0(0x300);
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 1:
        effect->unk_0C.s = effect->unk_0C.s - 1;
        if (effect->unk_0C.s > 0) {
            return;
        }
        effect->unk_0C.s = 12;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 2:
        effect->unk_0C.s = effect->unk_0C.s - 1;
        if (effect->unk_0C.s > 0) {
            motion->unk_0C += step_x << 16;
            motion->unk_10 += step_y << 16;
        }
        motion->unk_00.s += motion->unk_0C;
        motion->unk_04.s += motion->unk_10;
        motion->unk_08.s += motion->unk_14;
        world_x = motion->unk_00.h.unk_02;
        if (world_x < 0) {
            world_x += 63;
        }
        if ((world_x >> 6) == (s8)caster->unk_72.u) {
            world_y = motion->unk_04.h.unk_06;
            if (world_y < 0) {
                world_y += 63;
            }
            if ((world_y >> 6) == (s8)caster->unk_73.u) {
                effect->unk_50.u = 0;
            }
        }
        if (effect->unk_50.s > 0) {
            return;
        }
        effect->unk_0A.u = effect->unk_0A.u + 1;
        motion->unk_0C = step_x << 16;
        motion->unk_10 = step_y << 16;
        return;

    case 3:
        motion->unk_00.s += motion->unk_0C;
        motion->unk_04.s += motion->unk_10;
        motion->unk_08.s += motion->unk_14;
        if (caster->unk_60.s != 0) {
            func_8009CE1C(caster->unk_60.p, 10, effect->unk_09, 1,
                          caster->unk_2A.s, caster, 2);
        }
        effect->unk_50.s = 16;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 4:
        func_80044A50((u8 *)effect - 0x20);
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 5:
        flags = effect->unk_10;
        if (flags & 0x8000) {
            effect->unk_10 = flags & ~0x8000;
            return;
        }
        if (effect->unk_50.s > 0) {
            return;
        }
        dungeonStatus.unk_0C = 0;
        ((ObjectStatusPrefix *)((u8 *)effect - 0x20))->unk_1E |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
}
