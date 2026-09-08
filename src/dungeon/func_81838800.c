#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 rx;
    s32 ry;
    s32 rz;
} FixedCoords;

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s32);
extern s32 func_800A05A4(void *, s32, s32, s32, s32);
extern s16 func_800BCB04(s32, s32, s32);
extern s16 func_800A4688(s32, s32, s32, s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void func_800A56E0(s32);
extern void func_80044A50(void *);

extern u8 D_80024008[];
extern u8 D_80024B58[];
extern u8 D_800248F8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083498[];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern u8 D_800DEA68[];
__asm__(".set D_800DEA68, 0x800DEA68");

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), used, aligned(4))) = {
    0x80024020,
    0,
    0x80024310,
    0x800246B8,
    0x800246DC,
    0x800247D0,
    0x80024844,
    0x8002486C,
};
__asm__(".globl func_80024000\n.size func_80024000, 2296");
#define FUNC_80024000_BODY func_80024020
#else
#define FUNC_80024000_BODY func_80024000
#endif

void FUNC_80024000_BODY(void *effect, void *motion, void *effect_sprite)
    __attribute__((section(".text.func_80024000")));
/* Updates a projectile effect, spawning particles and moving toward its target before impact and cleanup. */
void FUNC_80024000_BODY(void *effect, void *motion, void *effect_sprite)
{
    void *caster;
    s32 particle_or_y;
    s32 sprite_or_x;
    void *particle_data;
    s32 index_or_x;
    s32 tile_dx;
    s32 tile_dy;
    FixedCoords target_pos;
    s16 launch_offset[3];
    void *caster_obj;
    void *caster_sprite;
    void *target;
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
    static void *const state_labels[] __attribute__((used)) = {
        &&launch, &&wait_launch, &&travel, &&impact, &&stop_motion, &&cleanup
    };

    register u8 *direction_x ASM_REG("$4") = D_8006CCD8;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 direction_offset ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register u32 direction ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    caster = FIELD(effect, void *, 0);
    direction = FIELD(caster, u16, 0x2A);
    caster_obj = (u8 *)caster - 0x20;
    caster_sprite = FIELD(caster, void *, -0x14);
    direction_offset = direction >> 8;
    direction_offset &= 0xE;
    step_x = *(s16 *)(direction_x + direction_offset);
    step_y = *(s16 *)(D_8006CCE8 + direction_offset);

    if ((u32)(FIELD(effect, u16, 0x0A) - 1) < 3) {
        index_or_x = 9;
        do {
            particle_or_y = (s32)func_8003FD64(0x312, &D_80083498);
            if (particle_or_y != 0) {
                sprite_or_x = (s32)FIELD((void *)particle_or_y, void *, 0x0C);
                FIELD((void *)particle_or_y, void *, 0x10) = D_80024B58;
                FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 0) =
                    FIELD(motion, s32, 0) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 4) =
                    FIELD(motion, s32, 4) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 8) =
                    FIELD(motion, s32, 8) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                if (FIELD(effect, s16, 0x0A) == 2) {
                    FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 0x0C) =
                        FIELD(motion, s32, 0x0C) >> 2;
                    FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 0x10) =
                        FIELD(motion, s32, 0x10) >> 2;
                    FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 0) +=
                        (step_x << 21) -
                        (((step_x * FIELD(effect, s32, 0x0C)) << 20) / 12);
                    FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 4) +=
                        (step_y << 21) -
                        (((step_y * FIELD(effect, s32, 0x0C)) << 20) / 12);
                    particle_data = (u8 *)particle_or_y + 0x20;
                } else {
                    particle_data = (u8 *)particle_or_y + 0x20;
                }
                FIELD(FIELD((void *)particle_or_y, void *, 8), s32, 0x14) = -func_80069EF8() << 1;
                FIELD((void *)sprite_or_x, u16, 0x1E) = 0x1000;
                FIELD((void *)sprite_or_x, u16, 0x1C) = 0x1000;
                FIELD((void *)sprite_or_x, u16, 0x14) |= 0xC;
                if (func_80069EF8() & 1) {
                    FIELD((void *)sprite_or_x, u16, 0x14) |= 1;
                }
                FIELD((void *)sprite_or_x, s16, 0x10) = 96;
                FIELD((void *)sprite_or_x, void *, 0) = D_800DEA68;
                FIELD((void *)sprite_or_x, void *, 8) = *(void **)(D_800DEA68 + 4);
                FIELD((void *)sprite_or_x, u8, 4) = 0;
                FIELD((void *)sprite_or_x, u8, 5) = 0;
                FIELD((void *)sprite_or_x, s32, 0x0C) = 0x3030C0;
                FIELD(particle_data, void *, 0) = effect;
                FIELD(particle_data, u16, 0x4C) = 0;
                FIELD(particle_data, u16, 0x48) = func_80069EF8() & 3;
                FIELD(particle_data, u16, 0x4A) = index_or_x + 40;
                FIELD(particle_data, s16, 4) = (s8)FIELD(caster, u8, 0x72);
                FIELD(particle_data, s16, 6) = (s8)FIELD(caster, u8, 0x73);
            }
            index_or_x--;
        } while (index_or_x >= 0);
    }

    FIELD(effect, u16, 0x50) = FIELD(effect, u16, 0x50) - 1;
    state = FIELD(effect, s16, 0x0A);
    if ((u32)state >= 6) {
        goto done;
    }
    goto *(void (**)(void))((void **)D_80024008)[state];

launch:
    if ((FIELD(FIELD(effect, void *, 4), u16, 0) & 0x80) == 0) {
        goto done;
    }
    if (func_8003DE58(FIELD(FIELD(caster_obj, void *, 0x0C), void *, 8),
                      FIELD(caster_obj, void *, 0x0C), launch_offset, 0) == 0) {
        launch_offset[1] = 0;
        launch_offset[0] = 0;
        launch_offset[2] = (FIELD(caster_sprite, u16, 0x14) & 0x8000) ? -48 : 0;
    }
    FIELD(motion, s32, 0) = FIELD(FIELD(caster_obj, void *, 8), s32, 0) +
                          ((s32)launch_offset[0] << 16);
    FIELD(motion, s32, 4) = FIELD(FIELD(caster_obj, void *, 8), s32, 4) +
                          ((s32)launch_offset[1] << 16);
    FIELD(motion, s32, 8) = FIELD(FIELD(caster_obj, void *, 8), s32, 8) +
                          ((s32)launch_offset[2] << 16);
    func_8004491C((u8 *)effect - 0x20, D_800248F8);
    range = (s16)func_800A3820(7);
    target = (void *)func_800A05A4(caster, FIELD(caster_sprite, u8, 0x24),
                                FIELD(caster_sprite, u8, 0x25),
                                FIELD(caster, s16, 0x2A), range);
    FIELD(caster, void *, 0x60) = target;
    if (target != 0) {
        goto target_found;
    }
    {
        distance = 0;
        tile_dy = distance;
        tile_dx = distance;
        while (distance < func_800A3820(7)) {
            index_or_x = (FIELD(caster_sprite, u8, 0x24) + tile_dx) * 64 + 32;
            offset_y = (FIELD(caster_sprite, u8, 0x25) + tile_dy) * 64 + 32;
            sprite_or_x = index_or_x & 0xFFFF;
            {
                register s32 ground_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ground_x = sprite_or_x;
                particle_or_y = offset_y & 0xFFFF;
                ground_z = func_800BCB04(ground_x, particle_or_y,
                                   (s16)(FIELD(FIELD(caster_obj, void *, 8), u16, 0x0A) - 128));
            }
            if (func_800A4688(sprite_or_x, particle_or_y, ground_z, FIELD(caster, s16, 0x2A),
                              FIELD(caster, s32, 0x60)) != 0) {
                goto probe_done;
            }
            tile_dy += step_y;
            distance++;
            tile_dx += step_x;
        }
probe_done:
        FIELD(caster, u8, 0x72) = FIELD(caster_sprite, u8, 0x24) + step_x * distance;
        target_tile = FIELD(caster_sprite, u8, 0x25) + step_y * distance;
    }
    goto set_destination;

target_found:
    sprite_or_x = (s32)FIELD(target, void *, -0x14);
    if ((FIELD((void *)sprite_or_x, u16, 0x14) & 0x8000) && (FIELD(effect_sprite, u16, 0x14) & 0x8000)) {
        FIELD(effect, s16, 0x0A) = 3;
        goto done;
    }
    FIELD(caster, u8, 0x72) = FIELD((void *)sprite_or_x, u8, 0x24);
    target_tile = FIELD((void *)sprite_or_x, u8, 0x25);
set_destination:
    FIELD(caster, u8, 0x73) = target_tile;
    target_tile = FIELD(caster, s8, 0x72);
    HI16(target_pos.x) = (target_tile << 6) + 32;
    target_tile = FIELD(caster, s8, 0x73);
    HI16(target_pos.y) = (target_tile << 6) + 32;
    HI16(target_pos.z) = func_800BCB04(HI16U(target_pos.x), HI16U(target_pos.y),
                                   (s16)(FIELD(FIELD(caster_obj, void *, 8), u16, 0x0A) - 48));
    if (HI16(target_pos.z) >= 512) {
        HI16(target_pos.z) = FIELD(FIELD(caster_obj, void *, 8), u16, 0x0A);
    }
    HI16(target_pos.z) -= 48;
    index_or_x = HI16(target_pos.x) - FIELD(motion, s16, 2);
    offset_y = HI16(target_pos.y) - FIELD(motion, s16, 6);
    distance = index_or_x;
    if (index_or_x < 0) {
        ASM_KEEP_NV(distance);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        distance = -distance;
    }
    abs_dy = offset_y;
    if (offset_y < 0) {
        ASM_KEEP_NV(abs_dy);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        abs_dy = -abs_dy;
    }
    if (distance < abs_dy) {
        distance = abs_dy;
    }
    travel_frames = distance / 8;
    travel_frames++;
    FIELD(effect, s16, 0x50) = travel_frames;
    FIELD(motion, s32, 0x0C) = (index_or_x << 16) / FIELD(effect, s16, 0x50);
    FIELD(motion, s32, 0x10) = (offset_y << 16) / FIELD(effect, s16, 0x50);
    FIELD(motion, s32, 0x14) = (target_pos.z - FIELD(motion, s32, 8)) /
                             FIELD(effect, s16, 0x50);
    FIELD(effect, s32, 0x0C) = 8;
    FIELD(effect, u16, 0x50) = FIELD(effect, u16, 0x50) + FIELD(effect, u16, 0x0C);
    func_800A56E0(0x300);
    FIELD(effect, u16, 0x0A) = FIELD(effect, u16, 0x0A) + 1;
    goto done;

wait_launch:
    FIELD(effect, s32, 0x0C) = FIELD(effect, s32, 0x0C) - 1;
    if (FIELD(effect, s32, 0x0C) > 0) {
        goto done;
    }
    FIELD(effect, s32, 0x0C) = 12;
    FIELD(effect, u16, 0x0A) = FIELD(effect, u16, 0x0A) + 1;
    goto done;

travel:
    FIELD(effect, s32, 0x0C) = FIELD(effect, s32, 0x0C) - 1;
    if (FIELD(effect, s32, 0x0C) > 0) {
        FIELD(motion, s32, 0x0C) += step_x << 16;
        FIELD(motion, s32, 0x10) += step_y << 16;
    }
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0x0C);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    world_x = FIELD(motion, s16, 2);
    if (world_x < 0) {
        world_x += 63;
    }
    if ((world_x >> 6) == (s8)FIELD(caster, u8, 0x72)) {
        world_y = FIELD(motion, s16, 6);
        if (world_y < 0) {
            world_y += 63;
        }
        if ((world_y >> 6) == (s8)FIELD(caster, u8, 0x73)) {
            FIELD(effect, u16, 0x50) = 0;
        }
    }
    if (FIELD(effect, s16, 0x50) > 0) {
        goto done;
    }
    FIELD(effect, u16, 0x0A) = FIELD(effect, u16, 0x0A) + 1;
    FIELD(motion, s32, 0x0C) = step_x << 16;
    FIELD(motion, s32, 0x10) = step_y << 16;
    goto done;

impact:
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0x0C);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    if (FIELD(caster, s32, 0x60) != 0) {
        func_8009CE1C(FIELD(caster, void *, 0x60), 10, FIELD(effect, u8, 9), 1,
                      FIELD(caster, s16, 0x2A), caster, 2);
    }
    FIELD(effect, s16, 0x50) = 16;
    FIELD(effect, u16, 0x0A) = FIELD(effect, u16, 0x0A) + 1;
    goto done;

stop_motion:
    func_80044A50((u8 *)effect - 0x20);
    FIELD(motion, s32, 0x14) = 0;
    FIELD(motion, s32, 0x10) = 0;
    FIELD(motion, s32, 0x0C) = 0;
    FIELD(effect, u16, 0x0A) = FIELD(effect, u16, 0x0A) + 1;
    goto done;

cleanup:
    flags = FIELD(effect, s32, 0x10);
    if (flags & 0x8000) {
        FIELD(effect, s32, 0x10) = flags & ~0x8000;
        goto done;
    }
    if (FIELD(effect, s16, 0x50) > 0) {
        goto done;
    }
    D_8008346C[0] = 0;
    FIELD(effect, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
done:
    return;
}
