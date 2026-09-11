#include "common.h"
extern int abs(int);

#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])

typedef struct S_func_81838800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    union { s32 s; u16 u; } unk_0C;
    s32 unk_10;
    u8 pad_14[0x3C];
    union { s16 s; u16 u; } unk_50;
} S_func_81838800_1;

typedef struct S_func_81838800_2 {
    union {
        s32 s;
        struct { u8 pad_00[2]; s16 unk_02; } h;
    } unk_00;
    union {
        s32 s;
        struct { u8 pad_04[2]; s16 unk_06; } h;
    } unk_04;
    union {
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81838800_2;

typedef struct S_func_81838800_3 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[4];
    u8 unk_24;
    u8 unk_25;
} S_func_81838800_3;

typedef struct S_func_81838800_4 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x34];
    union { void *p; s32 s; } unk_60;
    u8 pad_64[0x0E];
    union { s8 s; u8 u; } unk_72;
    union { s8 s; u8 u; } unk_73;
} S_func_81838800_4;

typedef struct S_func_81838800_5 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_81838800_5;

typedef struct S_func_81838800_6 {
    void *unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x40];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_func_81838800_6;

typedef struct S_func_81838800_7 {
    u16 unk_00;
} S_func_81838800_7;

typedef struct S_func_81838800_8 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_func_81838800_8;

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

void FUNC_80024000_BODY(S_func_81838800_1 *effect, S_func_81838800_2 *motion, S_func_81838800_3 *effect_sprite)
    __attribute__((section(".text.func_80024000")));
/* Updates a projectile effect, spawning particles and moving toward its target before impact and cleanup. */
void FUNC_80024000_BODY(S_func_81838800_1 *effect, S_func_81838800_2 *motion, S_func_81838800_3 *effect_sprite)
{
    S_func_81838800_4 *caster;
    s32 particle_or_y;
    s32 sprite_or_x;
    S_func_81838800_6 *particle_data;
    s32 index_or_x;
    s32 tile_dx;
    s32 tile_dy;
    FixedCoords target_pos;
    s16 launch_offset[3];
    S_func_81838800_5 *caster_obj;
    S_func_81838800_3 *caster_sprite;
    S_func_81838800_4 *target;
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
    caster = effect->unk_00;
    direction = caster->unk_2A.u;
    caster_obj = (S_func_81838800_5 *)((u8 *)caster - 0x20);
    caster_sprite = ((S_func_81838800_5 *)((u8 *)caster - 0x20))->unk_0C;
    direction_offset = direction >> 8;
    direction_offset &= 0xE;
    step_x = *(s16 *)(direction_x + direction_offset);
    step_y = *(s16 *)(D_8006CCE8 + direction_offset);

    if ((u32)(effect->unk_0A.u - 1) < 3) {
        index_or_x = 9;
        do {
            particle_or_y = (s32)func_8003FD64(0x312, &D_80083498);
            if (particle_or_y != 0) {
                sprite_or_x = (s32)((S_func_81838800_5 *)particle_or_y)->unk_0C;
                ((S_func_81838800_5 *)particle_or_y)->unk_10 = D_80024B58;
                ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_00.s =
                    motion->unk_00.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_04.s =
                    motion->unk_04.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_08.s =
                    motion->unk_08.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                if (effect->unk_0A.s == 2) {
                    ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_0C =
                        motion->unk_0C >> 2;
                    ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_10 =
                        motion->unk_10 >> 2;
                    ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_00.s +=
                        (step_x << 21) -
                        (((step_x * effect->unk_0C.s) << 20) / 12);
                    ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_04.s +=
                        (step_y << 21) -
                        (((step_y * effect->unk_0C.s) << 20) / 12);
                    particle_data = (S_func_81838800_6 *)((u8 *)particle_or_y + 0x20);
                } else {
                    particle_data = (S_func_81838800_6 *)((u8 *)particle_or_y + 0x20);
                }
                ((S_func_81838800_2 *)((S_func_81838800_5 *)particle_or_y)->unk_08)->unk_14 = -func_80069EF8() << 1;
                ((S_func_81838800_3 *)sprite_or_x)->unk_1E = 0x1000;
                ((S_func_81838800_3 *)sprite_or_x)->unk_1C = 0x1000;
                ((S_func_81838800_3 *)sprite_or_x)->unk_14 |= 0xC;
                if (func_80069EF8() & 1) {
                    ((S_func_81838800_3 *)sprite_or_x)->unk_14 |= 1;
                }
                *(s16 *)((u8 *)sprite_or_x + 0x10) = 96;
                *(void * *)((u8 *)sprite_or_x + 0x00) = D_800DEA68;
                ((S_func_81838800_3 *)sprite_or_x)->unk_08 = *(void **)(D_800DEA68 + 4);
                ((S_func_81838800_3 *)sprite_or_x)->unk_04 = 0;
                ((S_func_81838800_3 *)sprite_or_x)->unk_05 = 0;
                ((S_func_81838800_3 *)sprite_or_x)->unk_0C = 0x3030C0;
                particle_data->unk_00 = effect;
                particle_data->unk_4C = 0;
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
    if ((u32)state >= 6) {
        goto done;
    }
    goto *(void (**)(void))((void **)D_80024008)[state];

launch:
    if ((((S_func_81838800_7 *)effect->unk_04)->unk_00 & 0x80) == 0) {
        goto done;
    }
    if (func_8003DE58(((S_func_81838800_3 *)caster_obj->unk_0C)->unk_08,
                      caster_obj->unk_0C, launch_offset, 0) == 0) {
        launch_offset[1] = 0;
        launch_offset[0] = 0;
        launch_offset[2] = (caster_sprite->unk_14 & 0x8000) ? -48 : 0;
    }
    motion->unk_00.s = ((S_func_81838800_2 *)caster_obj->unk_08)->unk_00.s +
                          ((s32)launch_offset[0] << 16);
    motion->unk_04.s = ((S_func_81838800_2 *)caster_obj->unk_08)->unk_04.s +
                          ((s32)launch_offset[1] << 16);
    motion->unk_08.s = ((S_func_81838800_2 *)caster_obj->unk_08)->unk_08.s +
                          ((s32)launch_offset[2] << 16);
    func_8004491C((u8 *)effect - 0x20, D_800248F8);
    range = (s16)func_800A3820(7);
    target = (void *)func_800A05A4(caster, caster_sprite->unk_24,
                                caster_sprite->unk_25,
                                caster->unk_2A.s, range);
    caster->unk_60.p = target;
    if (target != 0) {
        goto target_found;
    }
    {
        distance = 0;
        tile_dy = distance;
        tile_dx = distance;
        while (distance < func_800A3820(7)) {
            index_or_x = (caster_sprite->unk_24 + tile_dx) * 64 + 32;
            offset_y = (caster_sprite->unk_25 + tile_dy) * 64 + 32;
            sprite_or_x = index_or_x & 0xFFFF;
            {
                register s32 ground_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ground_x = sprite_or_x;
                particle_or_y = offset_y & 0xFFFF;
                ground_z = func_800BCB04(ground_x, particle_or_y,
                                   (s16)(((S_func_81838800_2 *)caster_obj->unk_08)->unk_08.h.unk_0A - 128));
            }
            if (func_800A4688(sprite_or_x, particle_or_y, ground_z, caster->unk_2A.s,
                              caster->unk_60.s) != 0) {
                goto probe_done;
            }
            tile_dy += step_y;
            distance++;
            tile_dx += step_x;
        }
probe_done:
        caster->unk_72.u = caster_sprite->unk_24 + step_x * distance;
        target_tile = caster_sprite->unk_25 + step_y * distance;
    }
    goto set_destination;

target_found:
    sprite_or_x = (s32)((S_func_81838800_5 *)((u8 *)target - 0x20))->unk_0C;
    if ((((S_func_81838800_3 *)sprite_or_x)->unk_14 & 0x8000) && (effect_sprite->unk_14 & 0x8000)) {
        effect->unk_0A.s = 3;
        goto done;
    }
    caster->unk_72.u = ((S_func_81838800_3 *)sprite_or_x)->unk_24;
    target_tile = ((S_func_81838800_3 *)sprite_or_x)->unk_25;
set_destination:
    caster->unk_73.u = target_tile;
    target_tile = caster->unk_72.s;
    HI16(target_pos.x) = (target_tile << 6) + 32;
    target_tile = caster->unk_73.s;
    HI16(target_pos.y) = (target_tile << 6) + 32;
    HI16(target_pos.z) = func_800BCB04(HI16U(target_pos.x), HI16U(target_pos.y),
                                   (s16)(((S_func_81838800_2 *)caster_obj->unk_08)->unk_08.h.unk_0A - 48));
    if (HI16(target_pos.z) >= 512) {
        HI16(target_pos.z) = ((S_func_81838800_2 *)caster_obj->unk_08)->unk_08.h.unk_0A;
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
    goto done;

wait_launch:
    effect->unk_0C.s = effect->unk_0C.s - 1;
    if (effect->unk_0C.s > 0) {
        goto done;
    }
    effect->unk_0C.s = 12;
    effect->unk_0A.u = effect->unk_0A.u + 1;
    goto done;

travel:
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
        goto done;
    }
    effect->unk_0A.u = effect->unk_0A.u + 1;
    motion->unk_0C = step_x << 16;
    motion->unk_10 = step_y << 16;
    goto done;

impact:
    motion->unk_00.s += motion->unk_0C;
    motion->unk_04.s += motion->unk_10;
    motion->unk_08.s += motion->unk_14;
    if (caster->unk_60.s != 0) {
        func_8009CE1C(caster->unk_60.p, 10, effect->unk_09, 1,
                      caster->unk_2A.s, caster, 2);
    }
    effect->unk_50.s = 16;
    effect->unk_0A.u = effect->unk_0A.u + 1;
    goto done;

stop_motion:
    func_80044A50((u8 *)effect - 0x20);
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    effect->unk_0A.u = effect->unk_0A.u + 1;
    goto done;

cleanup:
    flags = effect->unk_10;
    if (flags & 0x8000) {
        effect->unk_10 = flags & ~0x8000;
        goto done;
    }
    if (effect->unk_50.s > 0) {
        goto done;
    }
    D_8008346C[0] = 0;
    ((S_func_81838800_8 *)((u8 *)effect - 0x20))->unk_1E |= 0x8000;
    D_800814A0[0] |= 0x8000;
done:
    return;
}
