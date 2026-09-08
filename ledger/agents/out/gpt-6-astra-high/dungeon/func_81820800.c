#include "common.h"
#include "m2c_compat.h"

extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");
void *func_8003FD64();
s32 func_8004491C();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
void *func_800A05A4();
s16 func_800A3820();
s32 func_800A4688();
M2C_UNK func_800A56E0();
s16 func_800BCB04();
extern M2C_UNK D_800245B4;
extern M2C_UNK D_80024A1C;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;

extern void func_80024020(void);
extern void func_80024148(void);
extern void func_8002439C(void);
extern void func_800244D4(void);
extern void func_80024518(void);
extern void func_8002453C(void);
__asm__(".set func_80024020, 0x80024020");
__asm__(".set func_80024148, 0x80024148");
__asm__(".set func_8002439C, 0x8002439c");
__asm__(".set func_800244D4, 0x800244d4");
__asm__(".set func_80024518, 0x80024518");
__asm__(".set func_8002453C, 0x8002453c");

/* Composite carve: retail places an 8-word bank (entry pointer, a zero word and
 * the 6-entry state jump table) immediately before this function's own code,
 * all under the func_80024000 symbol.  The bank is pinned to the function's own
 * named section so it lands ahead of the compiled body in the same output
 * section, byte-for-byte and gap-free (cf. the landed sister-floor module
 * func_81844800.c). */
#ifdef __mips__
static void (*const func_80024000_table[])(void)
    __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
        func_80024020,
        0,
        func_80024148,
        func_8002439C,
        func_8002439C,
        func_800244D4,
        func_80024518,
        func_8002453C,
    };
__asm__(".globl func_80024000\n"
        ".type func_80024000,@function\n"
        ".size func_80024000, 1460");
#define BODY_NAME composite_body_81820800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *state, void *motion, void *source_data) BODY_ATTR;
/* Moves an attack toward its target, spawns trailing effects, and applies the hit. */
BODY_STORAGE void BODY_NAME(void *state, void *motion, void *source_data) {
    static void *const state_labels[] = { &&state_aim, &&state_move, &&state_trail, &&state_hit, &&state_wait, &&state_finish };
    void *state_obj;
    void *owner;
    register void *source ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *actor ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *target;
    void *target_data;
    void *effect_data;
    void *effect;
    void *actor_data;
    s32 step_x;
    s32 step_y;
    register s32 offset_x ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 offset_y ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    M2C_UNK distance_or_script;
    register s32 delta_x ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 delta_y ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s8 *x_steps ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 abs_y ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 effects_left;
    s32 velocity_x;
    s32 velocity_y;
    s32 phase;
    s16 target_flag;
    register M2C_UNK direction_offset ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u16 header_raw;
    u16 duration;
    s32 coord_x;
    s32 coord_y;
    state_obj = state;
    source = source_data;
    x_steps = (s8 *) &D_8006CCD8;
    actor = M2C_FIELD(state_obj, void **, 0);
    owner = (void *) ((u8 *) actor - 0x20);
    header_raw = M2C_FIELD(actor, u16 *, 0x2A);
    delta_x = header_raw >> 8;
    direction_offset = delta_x & 0xE;
    ASM_KEEP_DEP_NV(direction_offset, header_raw);   /* MATCH pin: keeps a statement from moving across a call/branch */
    actor_data = M2C_FIELD(actor, void **, -0x14);
    step_x = *(s16 *)(direction_offset + x_steps);
    step_y = *(s16 *)(direction_offset + (s8 *)&D_8006CCE8);
    ASM_KEEP_NV(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(state_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (M2C_FIELD(state_obj, s16 *, 0xA) != 1) {
        goto dispatch;
    }
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    delta_x = func_800BCB04(M2C_FIELD(motion, u16 *, 2), M2C_FIELD(motion, u16 *, 6), (s16) (M2C_FIELD(M2C_FIELD(owner, void **, 8), u16 *, 0xA) - 0x30));
    if (delta_x >= 0x200) {
        goto dispatch;
    }
    M2C_FIELD(motion, s16 *, 0xA) = delta_x;
dispatch:
    phase = M2C_FIELD(state_obj, s16 *, 0xA);
    M2C_FIELD(state_obj, u16 *, 0x50) = (u16) (M2C_FIELD(state_obj, u16 *, 0x50) - 1);
    if ((u32) phase >= 6U) {
        goto done;
    }
    (void)state_labels;
    goto *jtbl_80024008[(u32) phase];
state_aim:
    if (!(*M2C_FIELD(state_obj, u16 **, 4) & 0x80)) {
        goto done;
    }
    {
        void *tile_data;
        s32 search_mode = func_800A3820(3) << 0x10;
        tile_data = actor_data;
        target = func_800A05A4(actor, M2C_FIELD(tile_data, u8 *, 0x24), M2C_FIELD(tile_data, u8 *, 0x25), (s16) M2C_FIELD(actor, u16 *, 0x2A), search_mode >> 0x10);
    }
    M2C_FIELD(actor, void **, 0x60) = target;
    if (target != NULL) {
        goto use_target;
    }
    distance_or_script = 0;
    offset_y = 0;
    offset_x = 0;
scan_tiles:
    {
        void *tile_data = actor_data;
        register s32 tile_left ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */
        s32 tile_top;
        tile_left = (M2C_FIELD(tile_data, u8 *, 0x24) + offset_x) << 6;
        coord_x = tile_left + 0x20;
        tile_top = (M2C_FIELD(tile_data, u8 *, 0x25) + offset_y) << 6;
        coord_y = tile_top + 0x20;
        ASM_KEEP_NV(coord_x);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP_NV(coord_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    if ((func_800A4688((u16) coord_x, (u16) coord_y, func_800BCB04((u16) coord_x, (u16) coord_y, -0x400), (s16) M2C_FIELD(actor, u16 *, 0x2A), M2C_FIELD(actor, void **, 0x60)) << 0x10) != 0) {
        goto set_endpoint;
    }
    distance_or_script += 1;
    offset_y += step_y;
    offset_x += step_x;
    if (distance_or_script < 2) {
        goto scan_tiles;
    }
set_endpoint:
    ASM_USE(coord_x);   /* MATCH pin: retail register colouring depends on it */
    ASM_USE2(coord_x, coord_y);   /* MATCH pin: load-bearing for the whole function shape */
    {
        void *tile_data = actor_data;
        M2C_FIELD(actor, u8 *, 0x72) = (u8) (M2C_FIELD(tile_data, u8 *, 0x24) + (step_x * distance_or_script));
        M2C_FIELD(actor, u8 *, 0x73) = (u8) (M2C_FIELD(tile_data, u8 *, 0x25) + (step_y * distance_or_script));
    }
    goto start_motion;
use_target:
    target_data = M2C_FIELD(target, void **, -0x14);
    M2C_FIELD(actor, u8 *, 0x72) = (u8) M2C_FIELD(target_data, u8 *, 0x24);
    M2C_FIELD(actor, u8 *, 0x73) = (u8) M2C_FIELD(target_data, u8 *, 0x25);
    if (!(M2C_FIELD(target_data, u16 *, 0x14) & 0x8000)) {
        goto start_motion;
    }
    if (M2C_FIELD(source, u16 *, 0x14) & 0x8000) {
        goto start_hit;
    }
start_motion:
    {
        void *tile_data;
        s32 end_x;
        s32 end_y;
        s32 start_x;
        s32 start_y;
        tile_data = actor_data;
        end_x = (s8)M2C_FIELD(actor, u8 *, 0x72);
        end_y = (s8)M2C_FIELD(actor, u8 *, 0x73);
        start_x = M2C_FIELD(tile_data, u8 *, 0x24);
        start_y = M2C_FIELD(tile_data, u8 *, 0x25);
        delta_x = end_x - start_x;
        delta_y = end_y - start_y;
        ASM_KEEP(start_y);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(start_x);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(end_y);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(end_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    }
    distance_or_script = delta_x;
    if (delta_x >= 0) {
        goto abs_delta_y;
    }
    distance_or_script = 0 - distance_or_script;
abs_delta_y:
    abs_y = delta_y;
    if (delta_y >= 0) {
        goto max_distance;
    }
    abs_y = 0 - abs_y;
max_distance:
    if (distance_or_script >= abs_y) {
        goto set_motion;
    }
    distance_or_script = abs_y;
set_motion:
    M2C_FIELD(state_obj, u16 *, 0x50) = (u16) (distance_or_script * 0xC);
    M2C_FIELD(motion, s32 *, 0) = (s32) (((M2C_FIELD(actor_data, u8 *, 0x24) << 6) + 0x20) << 0x10);
    M2C_FIELD(motion, s32 *, 4) = (s32) (((M2C_FIELD(actor_data, u8 *, 0x25) << 6) + 0x20) << 0x10);
    M2C_FIELD(motion, s32 *, 0xC) = (s32) ((step_x << 0x16) / 12);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) ((step_y << 0x16) / 12);
    func_800A56E0(0x300);
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;

state_move:
state_trail:
    M2C_FIELD(motion, s32 *, 0x14) = (s32) (M2C_FIELD(motion, s32 *, 0x14) + 0x100);
    target_flag = 0;
    if (M2C_FIELD(actor, void **, 0x60) != NULL) {
        goto spawn_effects;
    }
    target_flag = -1;
spawn_effects:
    effects_left = 2;
    distance_or_script = (s32)&D_800245B4;
next_effect:
    effect = func_8003FD64(0x201, &D_80083498);
    if (effect == NULL) {
        goto effect_spawned;
    }
    M2C_FIELD(effect, s32 *, 0x10) = distance_or_script;
    func_8004491C(effect, &D_80024A1C);
    duration = M2C_FIELD(state_obj, u16 *, 0x50);
    effect_data = effect + 0x20;
    M2C_FIELD(effect_data, s16 *, 0x54) = target_flag;
    M2C_FIELD(effect_data, u16 *, 0x52) = duration;
    M2C_FIELD(effect_data, s16 *, 0x4C) = (s16) (func_80069EF8() & 0xFFF);
    M2C_FIELD(effect_data, u16 *, 0x4E) = (u16) M2C_FIELD(motion, s32 *, 0x14);
    M2C_FIELD(effect_data, s32 *, 4) = (s32) M2C_FIELD(motion, s32 *, 0);
    M2C_FIELD(effect_data, s32 *, 8) = (s32) M2C_FIELD(motion, s32 *, 4);
    M2C_FIELD(effect_data, s32 *, 0xC) = 0;
    velocity_x = M2C_FIELD(motion, s32 *, 0xC);
    M2C_FIELD(effect_data, s32 *, 0x1C) = velocity_x;
    M2C_FIELD(effect_data, s32 *, 0x10) = velocity_x;
    velocity_y = M2C_FIELD(motion, s32 *, 0x10);
    M2C_FIELD(effect_data, s32 *, 0x24) = 0xFFFD0000;
    M2C_FIELD(effect_data, s32 *, 0x18) = 0xFFFD0000;
    M2C_FIELD(effect_data, s32 *, 0x20) = velocity_y;
    M2C_FIELD(effect_data, s32 *, 0x14) = velocity_y;
    M2C_FIELD(effect_data, u16 *, 0x50) = (u16) M2C_FIELD(motion, s16 *, 0xA);
    M2C_FIELD(effect, void **, 0x20) = state_obj;
    M2C_FIELD(effect_data, s16 *, 0x56) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) - 1);
effect_spawned:
    effects_left -= 1;
    if (effects_left >= 0) {
        goto next_effect;
    }
    if ((s16) M2C_FIELD(state_obj, u16 *, 0x50) > 0) {
        goto done;
    }
    M2C_FIELD(state_obj, u16 *, 0x50) = 5U;
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    if (M2C_FIELD(actor, void **, 0x60) != NULL) {
        goto done;
    }
start_hit:
    M2C_FIELD(state_obj, s16 *, 0xA) = 3;
    return;
state_hit:
    if (M2C_FIELD(actor, void **, 0x60) == NULL) {
        goto wait_hit;
    }
    func_8009CE1C(M2C_FIELD(actor, void **, 0x60), 0x10, M2C_FIELD(state_obj, u8 *, 9), 4, (s32) (s16) M2C_FIELD(actor, u16 *, 0x2A), actor, 2);
wait_hit:
    M2C_FIELD(state_obj, u16 *, 0x50) = 0x10U;
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;
state_wait:
    if ((s16) M2C_FIELD(state_obj, u16 *, 0x50) > 0) {
        goto done;
    }
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;
state_finish:
    if (!(M2C_FIELD(state_obj, s16 *, 0x52) & 0x8000)) {
        goto finish;
    }
    M2C_FIELD(state_obj, s16 *, 0x52) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0x52) & 0x7FFF);
    return;
finish:
    D_8008346C = 0;
    M2C_FIELD(state_obj, u16 *, -2) = (u16) (M2C_FIELD(state_obj, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
done:
    return;
}
