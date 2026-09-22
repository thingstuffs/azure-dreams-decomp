#include "common.h"

extern void func_800241F0(void) __attribute__((noreturn));
extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern void func_8009CE1C();
extern s16 func_800A4688();
extern void func_800A56E0(s32);
extern s16 func_800BCB04(s32, s32, s32);

extern u8 D_800247DC[];
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_8008346C;
extern s32 D_80083498;
extern u8 D_800DE9D0[];
extern u8 D_800DEC28[];

extern void func_80024004(void);

#ifdef __mips__
static void (*const func_81850800_table[])(void)
    __asm__("func_81850800")
    __attribute__((section(".text.func_81850800"), aligned(4))) = {
        func_80024004,
    };
__asm__(".globl func_81850800\n"
        ".type func_81850800,@function\n"
        ".size func_81850800, 2012");
#define BODY_NAME composite_body_81850800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81850800")))
#else
#define BODY_NAME func_81850800
#define BODY_STORAGE
#define BODY_ATTR
#endif

typedef struct S_81850800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 unk_0A_s16;
        u16 unk_0A_u16;
    } unk_0A;
    u8 pad_0C[0x44];
    union {
        s16 unk_50_s16;
        u16 unk_50_u16;
    } unk_50;
    union {
        s16 unk_52_s16;
        u16 unk_52_u16;
    } unk_52;
} S_81850800_0;

typedef struct S_81850800_1 {
    u8 pad_00[0x2A];
    union {
        s16 unk_2A_s16;
        u16 unk_2A_u16;
    } unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_81850800_1;

typedef struct S_81850800_2 {
    void * unk_00;
} S_81850800_2;

typedef struct S_81850800_3 {
    u16 unk_00;
} S_81850800_3;

typedef struct S_81850800_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_81850800_4;

typedef struct S_81850800_5 {
    union {
        s32 unk_00_s32;
        struct {
            u8 pad_00[0x2];
            s16 unk_02_s16;
        } unk_02_view_s16;
    } unk_00;
    union {
        s32 unk_04_s32;
        struct {
            u8 pad_04[0x2];
            s16 unk_06_s16;
        } unk_06_view_s16;
    } unk_04;
    union {
        s32 unk_08_s32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A_s16;
        } unk_0A_view_s16;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    union {
        s32 unk_14_s32;
        u16 unk_14_u16;
    } unk_14;
    u8 pad_18[0xC];
    u8 unk_24;
    u8 unk_25;
} S_81850800_5;

typedef struct S_81850800_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81850800_6;

typedef struct S_81850800_7 {
    union {
        s32 unk_00_s32;
        struct {
            u8 pad_00[0x2];
            u16 unk_02_u16;
        } unk_02_view_u16;
    } unk_00;
    union {
        s32 unk_04_s32;
        struct {
            u8 pad_04[0x2];
            u16 unk_06_u16;
        } unk_06_view_u16;
    } unk_04;
    union {
        s32 unk_08_s32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A_s16;
        } unk_0A_view_s16;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A_u16;
        } unk_0A_view_u16;
    } unk_08;
    union {
        s32 unk_0C_s32;
        struct {
            u8 pad_0C[0x2];
            u16 unk_0E_u16;
        } unk_0E_view_u16;
    } unk_0C;
    union {
        s32 unk_10_s32;
        struct {
            u8 pad_10[0x2];
            u16 unk_12_u16;
        } unk_12_view_u16;
    } unk_10;
} S_81850800_7;

typedef struct S_81850800_8 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    union {
        s32 unk_08_s32;
        void * unk_08_ptr;
    } unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81850800_8;

typedef struct S_81850800_9 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81850800_9;

typedef struct S_81850800_10 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81850800_10;

typedef struct S_81850800_11 {
    u8 pad_00[0x48];
    union {
        s16 unk_48_s16;
        u16 unk_48_u16;
    } unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
} S_81850800_11;

BODY_STORAGE void BODY_NAME(S_81850800_0 *owner, S_81850800_7 *motion, S_81850800_6 *sprite) BODY_ATTR;
/* Advance a directional effect, spawn its particles, and apply its target impact. */
BODY_STORAGE void BODY_NAME(S_81850800_0 *owner, S_81850800_7 *motion, S_81850800_6 *sprite)
{
    s32 step_x;
    s32 step_y;
    s32 state;
    s16 effect_flags;
    s32 tiles_ahead;
    s32 off_x;
    s32 off_y;
    register s32 facing_shift ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 dx ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 magnitude ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tile_x;
    s32 tile_y;
    s32 color;
    s32 copy_value;
    s32 spawn_color;
    u32 tile_step_x;
    s32 tile_step_y;
    s32 pixel_step_x;
    s32 pixel_offset;
    u16 timer;
    u16 flags;
    u32 base_y;
    s16 ground_height;
    S_81850800_1 *caster_data;
    S_81850800_4 *caster_sprite;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_81850800_8 *work;
    S_81850800_9 *obj;
    S_81850800_1 *target;
    union { S_81850800_11 * pointer; s32 value; } effect_data;
    S_81850800_5 *position;
    u8 *spawn_cb;
    register u8 *particle_cb ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register S_81850800_10 *particle_anim ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *step_x_table;
    u8 *step_y_table;
    s32 pix_x;
    s32 origin_y;
    u8 origin_x;
    s32 pix_y;
    s32 next_state;
    static void *const keepalive[] = { &&state_0_after };
    caster_data = owner->unk_00;
    step_x_table = (u8 *)&D_8006CCD8;
    magnitude = (u16)caster_data->unk_2A.unk_2A_u16;
    facing_shift = magnitude >> 8;
    caster_sprite = ((S_81850800_2 *)((u8 *)caster_data - 0x14))->unk_00;
    base_y = facing_shift & 0xE;
    step_x_table = (u8 *)(base_y + (s32)step_x_table);
    step_x = *(s16 *)step_x_table;
    step_y_table = (u8 *)&D_8006CCE8;
    base_y = (s32)step_y_table + base_y;
    timer = owner->unk_50.unk_50_u16 - 1;
    base_y = *(s16 *)base_y;
    step_y = base_y;
    work = (S_81850800_8 *)((u8 *)caster_data - 0x20);
    state = owner->unk_0A.unk_0A_s16 ^ (step_x ^ step_x);
    owner->unk_50.unk_50_u16 = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    if ((((S_81850800_3 *)owner->unk_04)->unk_00 & 0x80) == 0) {
        goto done;
    }
    target = caster_data->unk_60;
    tiles_ahead = 0;
    if (target == 0) {
        s32 tile_pixel_x;
        s32 min_height;
        s32 probe_y;

        off_y = 0;
        off_x = 0;
        do {
            min_height = -0x400;
            ASM_KEEP(min_height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            tile_pixel_x = caster_sprite->unk_24;
            magnitude = caster_sprite->unk_25;
            tile_pixel_x = (tile_pixel_x + off_x) << 6;
            ASM_KEEP(tile_pixel_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            dx = tile_pixel_x + 0x20;
            magnitude = (magnitude + off_y) << 6;
            ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            facing_shift = magnitude + 0x20;
            obj = (S_81850800_9 *)((u16)dx);
            probe_y = (u16)facing_shift;
            ground_height = func_800BCB04((s32)obj, probe_y, min_height);
            if ((s16)func_800A4688((s32)obj, probe_y, ground_height, caster_data->unk_2A.unk_2A_s16,
                                   caster_data->unk_60) != 0) {
                goto state_0_tail;
            }
            tiles_ahead++;
            off_y += step_y;
            off_x += step_x;
            if (tiles_ahead >= 2) {
                break;
            }
        } while (1);
state_0_tail:
        dx = step_x * tiles_ahead;
        facing_shift = step_y * tiles_ahead;
        ASM_KEEP(dx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(facing_shift);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800241F0();
        return;
    }

    position = ((S_81850800_2 *)((u8 *)target - 0x14))->unk_00;
    copy_value = caster_sprite->unk_24;
    base_y = position->unk_24;
    facing_shift = position->unk_25;
    dx = base_y - copy_value;
    base_y = caster_sprite->unk_25;
    facing_shift -= base_y;
    if ((position->unk_14.unk_14_u16 & 0x8000) &&
        (sprite->unk_14 & 0x8000)) {
        owner->unk_0A.unk_0A_s16 = 2;
        owner->unk_50.unk_50_u16 = 0;
        return;
    }
    effect_data.value = dx;
    if (dx < 0) {
        effect_data.value = -effect_data.value;
    }
    pixel_offset = facing_shift;
    if (facing_shift < 0) {
        pixel_offset = -pixel_offset;
    }
    if (effect_data.value < pixel_offset) {
        effect_data.value = pixel_offset;
    }
    magnitude = effect_data.value * 4;
    owner->unk_50.unk_50_u16 = magnitude;
    if (effect_data.value == 0) {
        goto state_0_zero;
    }
    if (effect_data.value == 1) {
        ASM_KEEP_NV(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        goto state_0_one;
    }
    dx = 1;
    facing_shift = 0;
    goto state_0_after;

state_0_zero:
    dx = 0;
    facing_shift = 2;
    owner->unk_50.unk_50_u16 = 0;
    goto state_0_common;

state_0_one:
    dx = 0;
    facing_shift = 3;
    state = facing_shift;
    if (caster_data->unk_60 != 0) {
        state = 1;
    }
    owner->unk_50.unk_50_u16 = state;
    goto state_0_common;

state_0_after:
    owner->unk_50.unk_50_u16 -= 2;
state_0_common:
    tile_step_x = step_x * dx;
    pixel_offset = facing_shift << 4;
    pixel_step_x = step_x * pixel_offset;
    tile_step_y = step_y * dx;
    origin_x = caster_sprite->unk_24;
    pix_x = (origin_x + tile_step_x) << 6;
    tile_step_x = step_y * pixel_offset;
    pixel_offset = pixel_step_x + 0x20;
    pix_x += pixel_offset;
    motion->unk_00.unk_02_view_u16.unk_02_u16 = pix_x;
    origin_y = caster_sprite->unk_25;
    motion->unk_0C.unk_0E_view_u16.unk_0E_u16 = step_x << 4;
    motion->unk_10.unk_12_view_u16.unk_12_u16 = step_y << 4;
    pix_y = (origin_y + tile_step_y) << 6;
    pixel_offset = tile_step_x + 0x20;
    pix_y += pixel_offset;
    motion->unk_04.unk_06_view_u16.unk_06_u16 = pix_y;
    func_800A56E0(0x300);
    owner->unk_0A.unk_0A_u16++;
    goto done;

state_1:
    ground_height = func_800BCB04(motion->unk_00.unk_02_view_u16.unk_02_u16,
                        motion->unk_04.unk_06_view_u16.unk_06_u16,
                        (s16)(((S_81850800_7 *)work->unk_08.unk_08_ptr)->unk_08.unk_0A_view_u16.unk_0A_u16 -
                              0x30));
    motion->unk_08.unk_0A_view_s16.unk_0A_s16 = ground_height;
    if (ground_height >= 0x200) {
        motion->unk_08.unk_0A_view_u16.unk_0A_u16 =
            ((S_81850800_7 *)work->unk_08.unk_08_ptr)->unk_08.unk_0A_view_u16.unk_0A_u16;
    }
    spawn_cb = (u8 *)&D_80083498;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_after_first;
    }
    obj->unk_10 = D_800247DC;
    position = obj->unk_08;
    work = obj->unk_0C;
    copy_value = motion->unk_00.unk_00_s32;
    position->unk_00.unk_00_s32 = copy_value;
    position = obj->unk_08;
    copy_value = motion->unk_04.unk_04_s32;
    effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
    position->unk_04.unk_04_s32 = copy_value;
    position = obj->unk_08;
    copy_value = motion->unk_08.unk_08_s32;
    spawn_color = 0xC00000;
    position->unk_08.unk_08_s32 = copy_value;
    work->unk_1E = 0x1000;
    work->unk_1C = 0x1000;
    work->unk_10 = 0x60;
    work->unk_14 |= 0xC;
    work->unk_00 = D_800DE9D0;
    copy_value = ((S_81850800_10 *)D_800DE9D0)->unk_04;
    spawn_color |= 0x8080;
    work->unk_04 = 0;
    work->unk_05 = 0;
    work->unk_0C = spawn_color;
    work->unk_08.unk_08_s32 = copy_value;
    obj->unk_20 = owner;
    effect_data.pointer->unk_48.unk_48_s16 = func_80069EF8() & 3;
    effect_data.pointer->unk_4E = (func_80069EF8() & 3) + 8;
    effect_data.pointer->unk_4A = (func_80069EF8() & 7) + 0xC;
    effect_data.pointer->unk_4C = 0;

state_1_after_first:
    if (owner->unk_50.unk_50_s16 > 0) {
        goto shared_motion;
    }
    if (caster_data->unk_60 == 0) {
        goto state_1_no_child;
    }
    owner->unk_50.unk_50_u16 = 4;
    owner->unk_0A.unk_0A_u16++;
    tile_x = caster_data->unk_72;
    motion->unk_00.unk_02_view_u16.unk_02_u16 = (tile_x << 6) + 0x20;
    tile_y = caster_data->unk_73;
    motion->unk_10.unk_10_s32 = 0;
    motion->unk_0C.unk_0C_s32 = 0;
    motion->unk_04.unk_06_view_u16.unk_06_u16 = (tile_y << 6) + 0x20;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_loop_setup;
    }
    obj->unk_10 = D_800247DC;
    position = obj->unk_08;
    work = obj->unk_0C;
    copy_value = motion->unk_00.unk_00_s32;
    position->unk_00.unk_00_s32 = copy_value;
    position = obj->unk_08;
    copy_value = motion->unk_04.unk_04_s32;
    effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
    position->unk_04.unk_04_s32 = copy_value;
    position = obj->unk_08;
    copy_value = motion->unk_08.unk_08_s32;
    spawn_color = 0x600000;
    position->unk_08.unk_08_s32 = copy_value;
    work->unk_1C = 0x2000;
    work->unk_1E = 0x2800;
    work->unk_10 = 0x20;
    work->unk_14 |= 0xC;
    work->unk_00 = D_800DE9D0;
    copy_value = ((S_81850800_10 *)D_800DE9D0)->unk_04;
    spawn_color |= 0x6060;
    work->unk_04 = 0;
    work->unk_05 = 0;
    work->unk_0C = spawn_color;
    work->unk_08.unk_08_s32 = copy_value;
    obj->unk_20 = owner;
    timer = owner->unk_50.unk_50_u16;
    effect_data.pointer->unk_4E = 8;
    effect_data.pointer->unk_4A = 8;
    effect_data.pointer->unk_4C = 0;
    effect_data.pointer->unk_48.unk_48_u16 = timer;

state_1_loop_setup:
    dx = 0x3C;
    particle_cb = D_800247DC;
    ASM_KEEP_MEM_NV(dx, *(u8 *)D_800247DC);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    particle_anim = (S_81850800_10 *)D_800DEC28;
    ASM_KEEP_MEM_NV(dx, *(u8 *)D_800DEC28);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
do {
    obj = func_8003FD64(0x312, &D_80083498);
    if (obj == 0) {
        goto state_1_loop_next;
    }
    work = obj->unk_0C;
    obj->unk_10 = particle_cb;
    ((S_81850800_5 *)obj->unk_08)->unk_00.unk_02_view_s16.unk_02_s16 =
        motion->unk_00.unk_02_view_u16.unk_02_u16 + (func_80069EF8() & 0x3F) - 0x20;
    ((S_81850800_5 *)obj->unk_08)->unk_04.unk_06_view_s16.unk_06_s16 =
        motion->unk_04.unk_06_view_u16.unk_06_u16 + (func_80069EF8() & 0x3F) - 0x20;
    ((S_81850800_5 *)obj->unk_08)->unk_08.unk_0A_view_s16.unk_0A_s16 =
        motion->unk_08.unk_0A_view_u16.unk_0A_u16 - (func_80069EF8() & 0x1F);
    color = 0x800000;
    work->unk_1E = 0x800;
    work->unk_1C = 0x800;
    work->unk_10 = 0x60;
    work->unk_00 = particle_anim;
    work->unk_14 |= 0xC;
    copy_value = particle_anim->unk_04;
    color |= 0x8080;
    work->unk_04 = 0;
    work->unk_05 = 0;
    work->unk_0C = color;
    work->unk_08.unk_08_s32 = copy_value;
    ((S_81850800_5 *)obj->unk_08)->unk_0C =
        step_x * (func_80069EF8() << 3);
    effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
    ((S_81850800_5 *)obj->unk_08)->unk_10 =
        step_y * (func_80069EF8() << 3);
    ((S_81850800_5 *)obj->unk_08)->unk_14.unk_14_s32 =
        0xFFF7FFFF - func_80069EF8();
    obj->unk_20 = owner;
    effect_data.pointer->unk_48.unk_48_s16 = 2;
    effect_data.pointer->unk_4E = (func_80069EF8() & 7) + 8;
    effect_data.pointer->unk_4A = 0x10;
    effect_data.pointer->unk_4C = 0;
state_1_loop_next:
    dx--;
    } while (dx >= 0);
    goto shared_motion;

state_1_no_child:
    owner->unk_50.unk_50_u16 = 4;
    owner->unk_0A.unk_0A_s16 = 3;
shared_motion:
    motion->unk_00.unk_00_s32 += motion->unk_0C.unk_0C_s32;
    motion->unk_04.unk_04_s32 += motion->unk_10.unk_10_s32;
    return;

state_2:
    if ((s16)timer > 0) {
        goto done;
    }
    if (caster_data->unk_60 != 0) {
        func_8009CE1C(caster_data->unk_60, 0x13,
                      owner->unk_09, 2,
                      caster_data->unk_2A.unk_2A_s16, caster_data, state);
    }
    owner->unk_50.unk_50_u16 = 0x10;
    owner->unk_0A.unk_0A_u16++;
    goto done;

state_3:
    effect_flags = owner->unk_52.unk_52_s16;
    flags = owner->unk_52.unk_52_u16;
    if (effect_flags & 0x8000) {
        owner->unk_52.unk_52_u16 = flags & 0x7FFF;
        return;
    }
    if ((s16)timer > 0) {
        goto done;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)owner - 2)) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

done:
    return;
}
