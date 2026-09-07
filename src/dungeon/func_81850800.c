#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define owner arg0

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

BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    s32 step_x;
    s32 step_y;
    s32 state;
    s16 state3;
    s32 count;
    s32 off_x;
    register s32 off_y ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 facing ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 facing_shift ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 dx ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 dy ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 abs_x ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 abs_y;
    register s32 magnitude ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 scale ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 mode ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 loop ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 tile_x;
    s32 tile_y;
    s32 color;
    s32 copy_value;
    s32 spawn_color;
    register s32 prod_x ASM_REG("$9");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 prod_y;
    s32 mode_x;
    register s32 mode_y ASM_REG("$9");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 mode16 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 step_value;
    u16 timer;
    u16 flags;
    register u8 base_y ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s16 hit;
    u8 *root;
    register u8 *other ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *work;
    u8 *obj;
    u8 *child;
    u8 *slot;
    u8 *node;
    u8 *spawn_cb;
    register u8 *particle_cb ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *anim ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *xbase;
    u8 *ybase;
    s32 pix_x;
    s32 oy;
    u8 ox;
    s32 pix_y;
    s32 tailv;
    static void *const keepalive[] = { &&state_0_after };
    root = FIELD(owner, u8 *, 0);
    xbase = (u8 *)&D_8006CCD8;
    magnitude = (u16)FIELD(root, u16, 0x2A);
    facing_shift = magnitude >> 8;
    other = FIELD(root, u8 *, -0x14);
    facing = facing_shift & 0xE;
    xbase = (u8 *)(facing + (s32)xbase);
    step_x = *(s16 *)xbase;
    ybase = (u8 *)&D_8006CCE8;
    facing = (s32)ybase + facing;
    timer = FIELD(owner, u16, 0x50) - 1;
    facing = *(s16 *)facing;
    step_y = facing;
    work = root - 0x20;
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
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
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
    child = FIELD(root, u8 *, 0x60);
    count = 0;
    if (child == 0) {
        s32 raw_x;
        register s32 raw_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 floor;
        register s32 x ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register u16 y ASM_REG("$16");   /* MATCH pin: retail delay-slot fill depends on it */

        off_y = 0;
        off_x = 0;
state_0_loop:
        floor = -0x400;
        ASM_KEEP(floor);   /* MATCH pin: retail schedule: same instructions, different order without it */
        raw_x = FIELD(other, u8, 0x24);
        raw_y = FIELD(other, u8, 0x25);
        raw_x = (raw_x + off_x) << 6;
        ASM_KEEP(raw_x);   /* MATCH pin: load-bearing for the whole function shape */
        dx = raw_x + 0x20;
        raw_y = (raw_y + off_y) << 6;
        ASM_KEEP(raw_y);   /* MATCH pin: load-bearing for the whole function shape */
        dy = raw_y + 0x20;
        x = (u16)dx;
        y = (u16)dy;
        hit = func_800BCB04(x, y, floor);
        if ((s16)func_800A4688(x, y, hit, FIELD(root, s16, 0x2A),
                               FIELD(root, void *, 0x60)) != 0) {
            goto state_0_tail;
        }
        count++;
        off_y += step_y;
        off_x += step_x;
        if (count < 2) {
            goto state_0_loop;
        }
state_0_tail:
        dx = step_x * count;
        dy = step_y * count;
        ASM_KEEP(dx);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_KEEP(dy);   /* MATCH pin: retail basic-block layout depends on it */
        func_800241F0();
        return;
    }

    node = FIELD(child, u8 *, -0x14);
    copy_value = FIELD(other, u8, 0x24);
    facing = FIELD(node, u8, 0x24);
    dy = FIELD(node, u8, 0x25);
    dx = facing - copy_value;
    base_y = FIELD(other, u8, 0x25);
    dy -= base_y;
    if ((FIELD(node, u16, 0x14) & 0x8000) &&
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
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
    ASM_KEEP_NV(magnitude);   /* MATCH pin: load-bearing for the whole function shape */
        goto state_0_one;
    }
    scale = 1;
    mode = 0;
    ASM_USE(scale);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_TAILSLOT_PIN(mode);   /* MATCH pin: retail delay-slot contents depend on it */
    func_8002426C();

state_0_zero:
    scale = zero;
    ASM_KEEP(scale);   /* MATCH pin: retail basic-block layout depends on it */
    mode = 2;
    ASM_KEEP(mode);   /* MATCH pin: retail basic-block layout depends on it */
    FIELD(owner, u16, 0x50) = 0;
    func_8002427C();

state_0_one:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    scale = zero;
    mode = 3;
    state = mode;
    if (FIELD(root, void *, 0x60) != 0) {
        state = zero + 1;
    }
    ASM_KEEP(base_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(mode);   /* MATCH pin: retail basic-block layout depends on it */
    FIELD(owner, u16, 0x50) = state;
    func_8002427C();

state_0_after:
    FIELD(owner, u16, 0x50) -= 2;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    prod_x = step_x * scale;
    mode16 = mode << 4;
    mode_x = step_x * mode16;
    ASM_KEEP(mode_x);   /* MATCH pin: retail basic-block layout depends on it */
    prod_y = step_y * scale;
    ASM_KEEP_NV(prod_y);   /* MATCH pin: retail register colouring depends on it */
    ox = FIELD(other, u8, 0x24);
    ASM_USE_NV(scale);   /* MATCH pin: retail delay-slot fill depends on it */
    pix_x = (ox + prod_x) << 6;
    mode_y = step_y * mode16;
    mode16 = mode_x + 0x20;
    pix_x += mode16;
    FIELD((u8 *)arg1, u16, 2) = pix_x;
    oy = FIELD(other, u8, 0x25);
    FIELD((u8 *)arg1, u16, 0xE) = step_x << 4;
    FIELD((u8 *)arg1, u16, 0x12) = step_y << 4;
    pix_y = (oy + prod_y) << 6;
    mode16 = mode_y + 0x20;
    pix_y += mode16;
    FIELD((u8 *)arg1, u16, 6) = pix_y;
    func_800A56E0(0x300);
    tailv = FIELD(owner, u16, 0xA) + 1;
    ASM_TAILSLOT_PIN(tailv);   /* MATCH pin: retail delay-slot fill depends on it */
    func_80024754();
    return;

state_1:
    hit = func_800BCB04(FIELD((u8 *)arg1, u16, 2),
                        FIELD((u8 *)arg1, u16, 6),
                        (s16)(FIELD(FIELD(work, u8 *, 8), u16, 0xA) -
                              0x30));
    FIELD((u8 *)arg1, s16, 0xA) = hit;
    if (hit >= 0x200) {
        FIELD((u8 *)arg1, u16, 0xA) =
            FIELD(FIELD(work, u8 *, 8), u16, 0xA);
    }
    spawn_cb = (u8 *)&D_80083498;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_after_first;
    }
    FIELD(obj, void *, 0x10) = D_800247DC;
    node = FIELD(obj, u8 *, 8);
    work = FIELD(obj, u8 *, 0xC);
    copy_value = FIELD((u8 *)arg1, s32, 0);
    FIELD(node, s32, 0) = copy_value;
    node = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)arg1, s32, 4);
    slot = obj + 0x20;
    FIELD(node, s32, 4) = copy_value;
    node = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)arg1, s32, 8);
    spawn_color = 0xC00000;
    FIELD(node, s32, 8) = copy_value;
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
    FIELD(slot, s16, 0x48) = func_80069EF8() & 3;
    FIELD(slot, s16, 0x4E) = (func_80069EF8() & 3) + 8;
    FIELD(slot, s16, 0x4A) = (func_80069EF8() & 7) + 0xC;
    FIELD(slot, s16, 0x4C) = 0;

state_1_after_first:
    if (FIELD(owner, s16, 0x50) > 0) {
        goto shared_motion;
    }
    if (FIELD(root, void *, 0x60) == 0) {
        goto state_1_no_child;
    }
    FIELD(owner, u16, 0x50) = 4;
    FIELD(owner, u16, 0xA)++;
    tile_x = FIELD(root, s8, 0x72);
    FIELD((u8 *)arg1, u16, 2) = (tile_x << 6) + 0x20;
    tile_y = FIELD(root, s8, 0x73);
    FIELD((u8 *)arg1, s32, 0x10) = 0;
    FIELD((u8 *)arg1, s32, 0xC) = 0;
    FIELD((u8 *)arg1, u16, 6) = (tile_y << 6) + 0x20;
    obj = func_8003FD64(0x112, spawn_cb);
    if (obj == 0) {
        goto state_1_loop_setup;
    }
    FIELD(obj, void *, 0x10) = D_800247DC;
    node = FIELD(obj, u8 *, 8);
    work = FIELD(obj, u8 *, 0xC);
    copy_value = FIELD((u8 *)arg1, s32, 0);
    FIELD(node, s32, 0) = copy_value;
    node = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)arg1, s32, 4);
    slot = obj + 0x20;
    FIELD(node, s32, 4) = copy_value;
    node = FIELD(obj, u8 *, 8);
    copy_value = FIELD((u8 *)arg1, s32, 8);
    spawn_color = 0x600000;
    FIELD(node, s32, 8) = copy_value;
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
    FIELD(slot, s16, 0x4E) = 8;
    FIELD(slot, s16, 0x4A) = 8;
    FIELD(slot, s16, 0x4C) = 0;
    FIELD(slot, u16, 0x48) = timer;

state_1_loop_setup:
    loop = 0x3C;
    particle_cb = D_800247DC;
    ASM_KEEP_MEM_NV(loop, *(u8 *)D_800247DC);
    anim = D_800DEC28;
    ASM_KEEP_MEM_NV(loop, *(u8 *)D_800DEC28);
state_1_loop:
    obj = func_8003FD64(0x312, &D_80083498);
    if (obj == 0) {
        goto state_1_loop_next;
    }
    work = FIELD(obj, u8 *, 0xC);
    FIELD(obj, void *, 0x10) = particle_cb;
    FIELD(FIELD(obj, u8 *, 8), s16, 2) =
        FIELD((u8 *)arg1, u16, 2) + (func_80069EF8() & 0x3F) - 0x20;
    FIELD(FIELD(obj, u8 *, 8), s16, 6) =
        FIELD((u8 *)arg1, u16, 6) + (func_80069EF8() & 0x3F) - 0x20;
    FIELD(FIELD(obj, u8 *, 8), s16, 0xA) =
        FIELD((u8 *)arg1, u16, 0xA) - (func_80069EF8() & 0x1F);
    color = 0x800000;
    FIELD(work, s16, 0x1E) = 0x800;
    FIELD(work, s16, 0x1C) = 0x800;
    FIELD(work, s16, 0x10) = 0x60;
    FIELD(work, void *, 0) = anim;
    FIELD(work, u16, 0x14) |= 0xC;
    copy_value = FIELD(anim, s32, 4);
    color |= 0x8080;
    FIELD(work, s8, 4) = 0;
    FIELD(work, s8, 5) = 0;
    FIELD(work, s32, 0xC) = color;
    FIELD(work, s32, 8) = copy_value;
    FIELD(FIELD(obj, u8 *, 8), s32, 0xC) =
        step_x * (func_80069EF8() << 3);
    slot = obj + 0x20;
    FIELD(FIELD(obj, u8 *, 8), s32, 0x10) =
        step_y * (func_80069EF8() << 3);
    FIELD(FIELD(obj, u8 *, 8), s32, 0x14) =
        0xFFF7FFFF - func_80069EF8();
    FIELD(obj, void *, 0x20) = owner;
    FIELD(slot, s16, 0x48) = 2;
    FIELD(slot, s16, 0x4E) = (func_80069EF8() & 7) + 8;
    FIELD(slot, s16, 0x4A) = 0x10;
    FIELD(slot, s16, 0x4C) = 0;
state_1_loop_next:
    loop--;
    if (loop >= 0) {
        goto state_1_loop;
    }
    func_800246DC();
    return;

state_1_no_child:
    FIELD(owner, u16, 0x50) = 4;
    FIELD(owner, s16, 0xA) = 3;
shared_motion:
    FIELD((u8 *)arg1, s32, 0) += FIELD((u8 *)arg1, s32, 0xC);
    FIELD((u8 *)arg1, s32, 4) += FIELD((u8 *)arg1, s32, 0x10);
    func_800247A8();
    return;

state_2:
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(root, void *, 0x60) != 0) {
        func_8009CE1C(FIELD(root, void *, 0x60), 0x13,
                      FIELD(owner, u8, 9), 2,
                      FIELD(root, s16, 0x2A), root, state);
    }
    FIELD(owner, u16, 0x50) = 0x10;
    FIELD(owner, u16, 0xA)++;
    func_800247A8();
    return;

state_3:
    state3 = FIELD(owner, s16, 0x52);
    flags = FIELD(owner, u16, 0x52);
    if (state3 & 0x8000) {
        FIELD(owner, u16, 0x52) = flags & 0x7FFF;
        func_800247A8();
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
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
