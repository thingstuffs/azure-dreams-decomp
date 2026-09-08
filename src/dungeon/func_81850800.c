#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800241F0(void) __attribute__((noreturn));
extern void func_8002426C(void) __attribute__((noreturn));
extern void func_8002427C(void) __attribute__((noreturn));
extern void func_800246DC(void) __attribute__((noreturn));
extern void func_80024754(void) __attribute__((noreturn));
extern void func_800247A8(void) __attribute__((noreturn));
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

BODY_STORAGE void BODY_NAME(void *owner, void *motion, void *sprite) BODY_ATTR;
/* Advance a directional effect, spawn its particles, and apply its target impact. */
BODY_STORAGE void BODY_NAME(void *owner, void *motion, void *sprite)
{
    s32 step_x;
    s32 step_y;
    s32 state;
    s16 effect_flags;
    s32 tiles_ahead;
    s32 off_x;
    register s32 off_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 facing ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 facing_shift ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 dx ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 dy ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 abs_x ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 abs_y;
    register s32 magnitude ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 scale ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 mode ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 particles_left ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 tile_x;
    s32 tile_y;
    s32 color;
    s32 copy_value;
    s32 spawn_color;
    register s32 tile_step_x ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 tile_step_y;
    s32 pixel_step_x;
    register s32 pixel_step_y ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 pixel_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 timer;
    u16 flags;
    register u8 base_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s16 ground_height;
    u8 *caster_data;
    register u8 *caster_sprite ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *work;
    u8 *obj;
    u8 *target;
    u8 *effect_data;
    u8 *position;
    u8 *spawn_cb;
    register u8 *particle_cb ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *particle_anim ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *step_x_table;
    u8 *step_y_table;
    s32 pix_x;
    s32 origin_y;
    u8 origin_x;
    s32 pix_y;
    s32 next_state;
    static void *const keepalive[] = { &&state_0_after };
    caster_data = FIELD(owner, u8 *, 0);
    step_x_table = (u8 *)&D_8006CCD8;
    magnitude = (u16)FIELD(caster_data, u16, 0x2A);
    facing_shift = magnitude >> 8;
    caster_sprite = FIELD(caster_data, u8 *, -0x14);
    facing = facing_shift & 0xE;
    step_x_table = (u8 *)(facing + (s32)step_x_table);
    step_x = *(s16 *)step_x_table;
    step_y_table = (u8 *)&D_8006CCE8;
    facing = (s32)step_y_table + facing;
    timer = FIELD(owner, u16, 0x50) - 1;
    facing = *(s16 *)facing;
    step_y = facing;
    work = caster_data - 0x20;
    state = FIELD(owner, s16, 0xA) ^ (step_x ^ step_x);
    FIELD(owner, u16, 0x50) = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_800247A8();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800247A8();
    return;

state_0:
    if ((FIELD(FIELD(owner, u8 *, 4), u16, 0) & 0x80) == 0) {
        goto done;
    }
    target = FIELD(caster_data, u8 *, 0x60);
    tiles_ahead = 0;
    if (target == 0) {
        s32 tile_pixel_x;
        register s32 tile_pixel_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 min_height;
        register s32 probe_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register u16 probe_y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

        off_y = 0;
        off_x = 0;
state_0_loop:
        min_height = -0x400;
        ASM_KEEP(min_height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tile_pixel_x = FIELD(caster_sprite, u8, 0x24);
        tile_pixel_y = FIELD(caster_sprite, u8, 0x25);
        tile_pixel_x = (tile_pixel_x + off_x) << 6;
        ASM_KEEP(tile_pixel_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        dx = tile_pixel_x + 0x20;
        tile_pixel_y = (tile_pixel_y + off_y) << 6;
        ASM_KEEP(tile_pixel_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        dy = tile_pixel_y + 0x20;
        probe_x = (u16)dx;
        probe_y = (u16)dy;
        ground_height = func_800BCB04(probe_x, probe_y, min_height);
        if ((s16)func_800A4688(probe_x, probe_y, ground_height, FIELD(caster_data, s16, 0x2A),
                               FIELD(caster_data, void *, 0x60)) != 0) {
            goto state_0_tail;
        }
        tiles_ahead++;
        off_y += step_y;
        off_x += step_x;
        if (tiles_ahead < 2) {
            goto state_0_loop;
        }
state_0_tail:
        dx = step_x * tiles_ahead;
        dy = step_y * tiles_ahead;
        ASM_KEEP(dx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(dy);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800241F0();
        return;
    }

    position = FIELD(target, u8 *, -0x14);
    copy_value = FIELD(caster_sprite, u8, 0x24);
    facing = FIELD(position, u8, 0x24);
    dy = FIELD(position, u8, 0x25);
    dx = facing - copy_value;
    base_y = FIELD(caster_sprite, u8, 0x25);
    dy -= base_y;
    if ((FIELD(position, u16, 0x14) & 0x8000) &&
        (FIELD(sprite, u16, 0x14) & 0x8000)) {
        FIELD(owner, s16, 0xA) = 2;
        FIELD(owner, u16, 0x50) = 0;
        func_800247A8();
        return;
    }
    abs_x = dx;
    if (dx < 0) {
        abs_x = -abs_x;
    }
    abs_y = dy;
    if (dy < 0) {
        abs_y = -abs_y;
    }
    if (abs_x < abs_y) {
        abs_x = abs_y;
    }
    magnitude = abs_x * 4;
    FIELD(owner, u16, 0x50) = magnitude;
    if (abs_x == 0) {
        goto state_0_zero;
    }
    if (abs_x == 1) {
        ASM_KEEP_NV(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        goto state_0_one;
    }
    scale = 1;
    mode = 0;
    ASM_USE(scale);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_TAILSLOT_PIN(mode);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_8002426C();

state_0_zero:
    scale = zero;
    ASM_KEEP(scale);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    mode = 2;
    ASM_KEEP(mode);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    FIELD(owner, u16, 0x50) = 0;
    func_8002427C();

state_0_one:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    scale = zero;
    mode = 3;
    state = mode;
    if (FIELD(caster_data, void *, 0x60) != 0) {
        state = zero + 1;
    }
    ASM_KEEP(base_y);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(mode);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    FIELD(owner, u16, 0x50) = state;
    func_8002427C();

state_0_after:
    FIELD(owner, u16, 0x50) -= 2;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    tile_step_x = step_x * scale;
    pixel_offset = mode << 4;
    pixel_step_x = step_x * pixel_offset;
    ASM_KEEP(pixel_step_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    tile_step_y = step_y * scale;
    ASM_KEEP_NV(tile_step_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    origin_x = FIELD(caster_sprite, u8, 0x24);
    ASM_USE_NV(scale);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    pix_x = (origin_x + tile_step_x) << 6;
    pixel_step_y = step_y * pixel_offset;
    pixel_offset = pixel_step_x + 0x20;
    pix_x += pixel_offset;
    FIELD((u8 *)motion, u16, 2) = pix_x;
    origin_y = FIELD(caster_sprite, u8, 0x25);
    FIELD((u8 *)motion, u16, 0xE) = step_x << 4;
    FIELD((u8 *)motion, u16, 0x12) = step_y << 4;
    pix_y = (origin_y + tile_step_y) << 6;
    pixel_offset = pixel_step_y + 0x20;
    pix_y += pixel_offset;
    FIELD((u8 *)motion, u16, 6) = pix_y;
    func_800A56E0(0x300);
    next_state = FIELD(owner, u16, 0xA) + 1;
    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    func_80024754();
    return;

state_1:
    ground_height = func_800BCB04(FIELD((u8 *)motion, u16, 2),
                        FIELD((u8 *)motion, u16, 6),
                        (s16)(FIELD(FIELD(work, u8 *, 8), u16, 0xA) -
                              0x30));
    FIELD((u8 *)motion, s16, 0xA) = ground_height;
    if (ground_height >= 0x200) {
        FIELD((u8 *)motion, u16, 0xA) =
            FIELD(FIELD(work, u8 *, 8), u16, 0xA);
    }
    spawn_cb = (u8 *)&D_80083498;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_after_first;
    }
    FIELD(obj, void *, 0x10) = D_800247DC;
    position = FIELD(obj, u8 *, 8);
    work = FIELD(obj, u8 *, 0xC);
    copy_value = FIELD((u8 *)motion, s32, 0);
    FIELD(position, s32, 0) = copy_value;
    position = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)motion, s32, 4);
    effect_data = obj + 0x20;
    FIELD(position, s32, 4) = copy_value;
    position = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)motion, s32, 8);
    spawn_color = 0xC00000;
    FIELD(position, s32, 8) = copy_value;
    FIELD(work, s16, 0x1E) = 0x1000;
    FIELD(work, s16, 0x1C) = 0x1000;
    FIELD(work, s16, 0x10) = 0x60;
    FIELD(work, u16, 0x14) |= 0xC;
    FIELD(work, void *, 0) = D_800DE9D0;
    copy_value = FIELD(D_800DE9D0, s32, 4);
    spawn_color |= 0x8080;
    FIELD(work, s8, 4) = 0;
    FIELD(work, s8, 5) = 0;
    FIELD(work, s32, 0xC) = spawn_color;
    FIELD(work, s32, 8) = copy_value;
    FIELD(obj, void *, 0x20) = owner;
    FIELD(effect_data, s16, 0x48) = func_80069EF8() & 3;
    FIELD(effect_data, s16, 0x4E) = (func_80069EF8() & 3) + 8;
    FIELD(effect_data, s16, 0x4A) = (func_80069EF8() & 7) + 0xC;
    FIELD(effect_data, s16, 0x4C) = 0;

state_1_after_first:
    if (FIELD(owner, s16, 0x50) > 0) {
        goto shared_motion;
    }
    if (FIELD(caster_data, void *, 0x60) == 0) {
        goto state_1_no_child;
    }
    FIELD(owner, u16, 0x50) = 4;
    FIELD(owner, u16, 0xA)++;
    tile_x = FIELD(caster_data, s8, 0x72);
    FIELD((u8 *)motion, u16, 2) = (tile_x << 6) + 0x20;
    tile_y = FIELD(caster_data, s8, 0x73);
    FIELD((u8 *)motion, s32, 0x10) = 0;
    FIELD((u8 *)motion, s32, 0xC) = 0;
    FIELD((u8 *)motion, u16, 6) = (tile_y << 6) + 0x20;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_loop_setup;
    }
    FIELD(obj, void *, 0x10) = D_800247DC;
    position = FIELD(obj, u8 *, 8);
    work = FIELD(obj, u8 *, 0xC);
    copy_value = FIELD((u8 *)motion, s32, 0);
    FIELD(position, s32, 0) = copy_value;
    position = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)motion, s32, 4);
    effect_data = obj + 0x20;
    FIELD(position, s32, 4) = copy_value;
    position = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)motion, s32, 8);
    spawn_color = 0x600000;
    FIELD(position, s32, 8) = copy_value;
    FIELD(work, s16, 0x1C) = 0x2000;
    FIELD(work, s16, 0x1E) = 0x2800;
    FIELD(work, s16, 0x10) = 0x20;
    FIELD(work, u16, 0x14) |= 0xC;
    FIELD(work, void *, 0) = D_800DE9D0;
    copy_value = FIELD(D_800DE9D0, s32, 4);
    spawn_color |= 0x6060;
    FIELD(work, s8, 4) = 0;
    FIELD(work, s8, 5) = 0;
    FIELD(work, s32, 0xC) = spawn_color;
    FIELD(work, s32, 8) = copy_value;
    FIELD(obj, void *, 0x20) = owner;
    timer = FIELD(owner, u16, 0x50);
    FIELD(effect_data, s16, 0x4E) = 8;
    FIELD(effect_data, s16, 0x4A) = 8;
    FIELD(effect_data, s16, 0x4C) = 0;
    FIELD(effect_data, u16, 0x48) = timer;

state_1_loop_setup:
    particles_left = 0x3C;
    particle_cb = D_800247DC;
    ASM_KEEP_MEM_NV(particles_left, *(u8 *)D_800247DC);
    particle_anim = D_800DEC28;
    ASM_KEEP_MEM_NV(particles_left, *(u8 *)D_800DEC28);
state_1_loop:
    obj = func_8003FD64(0x312, &D_80083498);
    if (obj == 0) {
        goto state_1_loop_next;
    }
    work = FIELD(obj, u8 *, 0xC);
    FIELD(obj, void *, 0x10) = particle_cb;
    FIELD(FIELD(obj, u8 *, 8), s16, 2) =
        FIELD((u8 *)motion, u16, 2) + (func_80069EF8() & 0x3F) - 0x20;
    FIELD(FIELD(obj, u8 *, 8), s16, 6) =
        FIELD((u8 *)motion, u16, 6) + (func_80069EF8() & 0x3F) - 0x20;
    FIELD(FIELD(obj, u8 *, 8), s16, 0xA) =
        FIELD((u8 *)motion, u16, 0xA) - (func_80069EF8() & 0x1F);
    color = 0x800000;
    FIELD(work, s16, 0x1E) = 0x800;
    FIELD(work, s16, 0x1C) = 0x800;
    FIELD(work, s16, 0x10) = 0x60;
    FIELD(work, void *, 0) = particle_anim;
    FIELD(work, u16, 0x14) |= 0xC;
    copy_value = FIELD(particle_anim, s32, 4);
    color |= 0x8080;
    FIELD(work, s8, 4) = 0;
    FIELD(work, s8, 5) = 0;
    FIELD(work, s32, 0xC) = color;
    FIELD(work, s32, 8) = copy_value;
    FIELD(FIELD(obj, u8 *, 8), s32, 0xC) =
        step_x * (func_80069EF8() << 3);
    effect_data = obj + 0x20;
    FIELD(FIELD(obj, u8 *, 8), s32, 0x10) =
        step_y * (func_80069EF8() << 3);
    FIELD(FIELD(obj, u8 *, 8), s32, 0x14) =
        0xFFF7FFFF - func_80069EF8();
    FIELD(obj, void *, 0x20) = owner;
    FIELD(effect_data, s16, 0x48) = 2;
    FIELD(effect_data, s16, 0x4E) = (func_80069EF8() & 7) + 8;
    FIELD(effect_data, s16, 0x4A) = 0x10;
    FIELD(effect_data, s16, 0x4C) = 0;
state_1_loop_next:
    particles_left--;
    if (particles_left >= 0) {
        goto state_1_loop;
    }
    func_800246DC();
    return;

state_1_no_child:
    FIELD(owner, u16, 0x50) = 4;
    FIELD(owner, s16, 0xA) = 3;
shared_motion:
    FIELD((u8 *)motion, s32, 0) += FIELD((u8 *)motion, s32, 0xC);
    FIELD((u8 *)motion, s32, 4) += FIELD((u8 *)motion, s32, 0x10);
    func_800247A8();
    return;

state_2:
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(caster_data, void *, 0x60) != 0) {
        func_8009CE1C(FIELD(caster_data, void *, 0x60), 0x13,
                      FIELD(owner, u8, 9), 2,
                      FIELD(caster_data, s16, 0x2A), caster_data, state);
    }
    FIELD(owner, u16, 0x50) = 0x10;
    FIELD(owner, u16, 0xA)++;
    func_800247A8();
    return;

state_3:
    effect_flags = FIELD(owner, s16, 0x52);
    flags = FIELD(owner, u16, 0x52);
    if (effect_flags & 0x8000) {
        FIELD(owner, u16, 0x52) = flags & 0x7FFF;
        func_800247A8();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if ((s16)timer > 0) {
        goto done;
    }
    D_8008346C = 0;
    FIELD(owner, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

done:
    return;
}
