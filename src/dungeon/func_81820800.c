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

typedef struct S_func_81820800_1 {
    void *unk_00;
    u16 *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    s16 unk_52;
} S_func_81820800_1;

typedef struct S_func_81820800_2 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            u16 unk_02;
        } unk_02;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            u16 unk_06;
        } unk_06;
    } unk_04;
    u8 pad_08[2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81820800_2;

typedef struct S_func_81820800_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
} S_func_81820800_3;

typedef struct S_func_81820800_4 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
} S_func_81820800_4;

typedef struct S_func_81820800_5 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_81820800_5;

typedef struct S_func_81820800_6 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_81820800_6;

typedef struct S_func_81820800_7 {
    u8 pad_00[4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x24];
    s16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    s16 unk_54;
    s16 unk_56;
} S_func_81820800_7;

typedef struct S_func_81820800_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_81820800_8;

typedef struct S_func_81820800_10 {
    s32 unk_00;
} S_func_81820800_10;

BODY_STORAGE void BODY_NAME(void *state, S_func_81820800_2 *motion, void *source_data) BODY_ATTR;
/* Moves an attack toward its target, spawns trailing effects, and applies the hit. */
BODY_STORAGE void BODY_NAME(void *state, S_func_81820800_2 *motion, void *source_data) {
    static void *const state_labels[] = { &&state_aim, &&state_move, &&state_trail, &&state_hit, &&state_wait, &&state_finish };
    S_func_81820800_1 *state_obj;
    S_func_81820800_4 *owner;
    S_func_81820800_5 *source;
    register S_func_81820800_3 *actor ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_func_81820800_3 *target;
    S_func_81820800_5 *target_data;
    S_func_81820800_7 *effect_data;
    S_func_81820800_6 *effect;
    S_func_81820800_5 *actor_data;
    s32 step_x;
    s32 step_y;
    register s32 offset_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 offset_y ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK distance_or_script;
    register s32 delta_x ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 delta_y ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s8 *x_steps ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 abs_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 effects_left;
    s32 velocity_x;
    s32 velocity_y;
    s32 phase;
    s16 target_flag;
    register M2C_UNK direction_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u16 header_raw;
    u16 duration;
    s32 coord_x;
    s32 coord_y;
    state_obj = state;
    source = source_data;
    x_steps = (s8 *) &D_8006CCD8;
    actor = state_obj->unk_00;
    owner = (void *) ((u8 *) actor - 0x20);
    header_raw = actor->unk_2A;
    delta_x = header_raw >> 8;
    direction_offset = delta_x & 0xE;
    ASM_KEEP_DEP_NV(direction_offset, header_raw);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    actor_data = ((S_func_81820800_4 *) ((u8 *) actor - 0x20))->unk_0C;
    step_x = *(s16 *)(direction_offset + x_steps);
    step_y = *(s16 *)(direction_offset + (s8 *)&D_8006CCE8);
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(state_obj);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (state_obj->unk_0A != 1) {
        goto dispatch;
    }
    motion->unk_00.unk_00 = (s32) (motion->unk_00.unk_00 + motion->unk_0C);
    motion->unk_04.unk_04 = (s32) (motion->unk_04.unk_04 + motion->unk_10);
    delta_x = func_800BCB04(motion->unk_00.unk_02.unk_02, motion->unk_04.unk_06.unk_06, (s16) (((S_func_81820800_8 *) owner->unk_08)->unk_0A - 0x30));
    if (delta_x >= 0x200) {
        goto dispatch;
    }
    motion->unk_0A = delta_x;
dispatch:
    phase = state_obj->unk_0A;
    state_obj->unk_50 = (u16) (state_obj->unk_50 - 1);
    if ((u32) phase >= 6U) {
        goto done;
    }
    (void)state_labels;
    goto *jtbl_80024008[(u32) phase];
state_aim:
    if (!(*state_obj->unk_04 & 0x80)) {
        goto done;
    }
    {
        S_func_81820800_5 *tile_data;
        s32 search_mode = func_800A3820(3) << 0x10;
        tile_data = actor_data;
        target = func_800A05A4(actor, tile_data->unk_24, tile_data->unk_25, (s16) actor->unk_2A, search_mode >> 0x10);
    }
    actor->unk_60 = target;
    if (target != NULL) {
        goto use_target;
    }
    distance_or_script = 0;
    offset_y = 0;
    offset_x = 0;
scan_tiles:
    {
        S_func_81820800_5 *tile_data = actor_data;
        register s32 tile_left ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        s32 tile_top;
        tile_left = (tile_data->unk_24 + offset_x) << 6;
        coord_x = tile_left + 0x20;
        tile_top = (tile_data->unk_25 + offset_y) << 6;
        coord_y = tile_top + 0x20;
        ASM_KEEP_NV(coord_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(coord_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    if ((func_800A4688((u16) coord_x, (u16) coord_y, func_800BCB04((u16) coord_x, (u16) coord_y, -0x400), (s16) actor->unk_2A, actor->unk_60) << 0x10) != 0) {
        goto set_endpoint;
    }
    distance_or_script += 1;
    offset_y += step_y;
    offset_x += step_x;
    if (distance_or_script < 2) {
        goto scan_tiles;
    }
set_endpoint:
    ASM_USE(coord_x);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_USE2(coord_x, coord_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        S_func_81820800_5 *tile_data = actor_data;
        actor->unk_72 = (u8) (tile_data->unk_24 + (step_x * distance_or_script));
        actor->unk_73 = (u8) (tile_data->unk_25 + (step_y * distance_or_script));
    }
    goto start_motion;
use_target:
    target_data = ((S_func_81820800_4 *) ((u8 *) target - 0x20))->unk_0C;
    actor->unk_72 = (u8) target_data->unk_24;
    actor->unk_73 = (u8) target_data->unk_25;
    if (!(target_data->unk_14 & 0x8000)) {
        goto start_motion;
    }
    if (source->unk_14 & 0x8000) {
        goto start_hit;
    }
start_motion:
    {
        S_func_81820800_5 *tile_data;
        s32 end_x;
        s32 end_y;
        s32 start_x;
        s32 start_y;
        tile_data = actor_data;
        end_x = (s8)actor->unk_72;
        end_y = (s8)actor->unk_73;
        start_x = tile_data->unk_24;
        start_y = tile_data->unk_25;
        delta_x = end_x - start_x;
        delta_y = end_y - start_y;
        ASM_KEEP(start_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(start_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(end_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(end_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
    state_obj->unk_50 = (u16) (distance_or_script * 0xC);
    motion->unk_00.unk_00 = (s32) (((actor_data->unk_24 << 6) + 0x20) << 0x10);
    motion->unk_04.unk_04 = (s32) (((actor_data->unk_25 << 6) + 0x20) << 0x10);
    motion->unk_0C = (s32) ((step_x << 0x16) / 12);
    motion->unk_10 = (s32) ((step_y << 0x16) / 12);
    func_800A56E0(0x300);
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;

state_move:
state_trail:
    motion->unk_14 = (s32) (motion->unk_14 + 0x100);
    target_flag = 0;
    if (actor->unk_60 != NULL) {
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
    effect->unk_10 = distance_or_script;
    func_8004491C(effect, &D_80024A1C);
    duration = state_obj->unk_50;
    effect_data = (S_func_81820800_7 *) ((u8 *) effect + 0x20);
    effect_data->unk_54 = target_flag;
    effect_data->unk_52 = duration;
    effect_data->unk_4C = (s16) (func_80069EF8() & 0xFFF);
    effect_data->unk_4E = (u16) motion->unk_14;
    effect_data->unk_04 = (s32) motion->unk_00.unk_00;
    effect_data->unk_08 = (s32) motion->unk_04.unk_04;
    effect_data->unk_0C = 0;
    velocity_x = motion->unk_0C;
    effect_data->unk_1C = velocity_x;
    effect_data->unk_10 = velocity_x;
    velocity_y = motion->unk_10;
    effect_data->unk_24 = 0xFFFD0000;
    effect_data->unk_18 = 0xFFFD0000;
    effect_data->unk_20 = velocity_y;
    effect_data->unk_14 = velocity_y;
    effect_data->unk_50 = (u16) motion->unk_0A;
    effect->unk_20 = state_obj;
    effect_data->unk_56 = (s16) ((u16) state_obj->unk_0A - 1);
effect_spawned:
    effects_left -= 1;
    if (effects_left >= 0) {
        goto next_effect;
    }
    if ((s16) state_obj->unk_50 > 0) {
        goto done;
    }
    state_obj->unk_50 = 5U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    if (actor->unk_60 != NULL) {
        goto done;
    }
start_hit:
    state_obj->unk_0A = 3;
    return;
state_hit:
    if (actor->unk_60 == NULL) {
        goto wait_hit;
    }
    func_8009CE1C(actor->unk_60, 0x10, state_obj->unk_09, 4, (s32) (s16) actor->unk_2A, actor, 2);
wait_hit:
    state_obj->unk_50 = 0x10U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
state_wait:
    if ((s16) state_obj->unk_50 > 0) {
        goto done;
    }
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
state_finish:
    if (!(state_obj->unk_52 & 0x8000)) {
        goto finish;
    }
    state_obj->unk_52 = (s16) ((u16) state_obj->unk_52 & 0x7FFF);
    return;
finish:
    D_8008346C = 0;
    *(u16 *)((u8 *)state_obj - 2) = (u16) (*(u16 *)((u8 *)state_obj - 2) | 0x8000);
    ((S_func_81820800_10 *) &D_800814A0)->unk_00 = (s32) (((S_func_81820800_10 *) &D_800814A0)->unk_00 | 0x8000);
done:
    return;
}
