#include "common.h"

typedef struct S_FUNC_8197C800_BODY_0_pre {
    u16 unk_00;
} S_FUNC_8197C800_BODY_0_pre;   /* the 0x2 bytes before arg0 in FUNC_8197C800_BODY, addressed as arg0[-1] */

typedef struct S_FUNC_8197C800_BODY_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_FUNC_8197C800_BODY_0;   /* arg0 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_1 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x90];
    s32 unk_F4;
} S_FUNC_8197C800_BODY_1;   /* D_800814A8[0] in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_2;   /* arg1 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_FUNC_8197C800_BODY_3;   /* root in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_4 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_FUNC_8197C800_BODY_4;   /* segment in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_FUNC_8197C800_BODY_5;   /* obj in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_6;   /* src_position in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_7;   /* dst_position in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_8 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    void * unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_FUNC_8197C800_BODY_8;   /* node in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_9;   /* D_800DEDB0 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_10 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_FUNC_8197C800_BODY_10;   /* tail in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_11 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_FUNC_8197C800_BODY_11;   /* p in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_12 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_FUNC_8197C800_BODY_12;   /* page in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_13 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_13;   /* image0 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_FUNC_8197C800_BODY_14;   /* position in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_15 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_15;   /* template in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_16 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_FUNC_8197C800_BODY_16;   /* page2 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_17 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_17;   /* image in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_18 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_FUNC_8197C800_BODY_18;   /* base in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_19 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u32 unk_0C;
} S_FUNC_8197C800_BODY_19;   /* status in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_20;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_08 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_21 {
    u16 unk_00;
} S_FUNC_8197C800_BODY_21;   /* ((S_FUNC_8197C800_BODY_0 *)arg0)->unk_04 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_22 {
    u8 pad_00[0x8];
    void * unk_08;
} S_FUNC_8197C800_BODY_22;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_0C in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_23 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_FUNC_8197C800_BODY_23;   /* ((S_FUNC_8197C800_BODY_12 *)page)->unk_14A8 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_24 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_FUNC_8197C800_BODY_24;   /* ((S_FUNC_8197C800_BODY_16 *)page2)->unk_14A8 in FUNC_8197C800_BODY */

typedef struct S_FUNC_8197C800_BODY_25 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_FUNC_8197C800_BODY_25;   /* ((S_FUNC_8197C800_BODY_5 *)obj)->unk_08 in FUNC_8197C800_BODY */



/* The first seven words are the retail function bank.  The actual C body
 * starts at +0x1c; its dispatch table is the resident table at 0x80024008. */
#ifdef __mips__
static const u32 func_8197C800_bank[] __asm__("func_8197C800")
    __attribute__((section(".text.func_8197C800"), aligned(4))) = {
    0x8002401C, 0x00000000, 0x80024090, 0x800240EC,
    0x80024248, 0x80024284, 0x800245E0,
};
#define FUNC_8197C800_BODY func_8197C81C
#else
#define FUNC_8197C800_BODY func_8197C800
#endif

extern void *D_80024008[];
extern void *D_800814A8[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80083780[];
extern u32 D_800246C0[];
extern u8 D_80024BB8[];
extern u8 D_80024C68[];
extern u8 D_80082E80[];
extern u8 D_800DEDB0[];
extern u8 D_800DE9D0[];
extern u8 D_800DEC00[];
extern u8 D_80083460[];
extern s32 D_800814A0[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_80082E94[];

extern void *func_8003FD64(s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_80069EF8(void);
extern void func_8009CE1C(void *, s32, s32, s32, s16, void *, s32);

/* These are the original absolute shared-tail entry points used by this
 * copied overlay bank. */
extern void func_800245D0(void) __attribute__((noreturn));
extern void func_800245D8(void) __attribute__((noreturn));
extern void func_8002468C(void) __attribute__((noreturn));

void FUNC_8197C800_BODY(void *state_input, void *position_output)
    __attribute__((section(".text.func_8197C800")));

/* Updates a timed effect sequence, spawning sprites and signaling completion. */
void FUNC_8197C800_BODY(void *state_input, void *position_output)
{
    s16 offsets[3];
    s32 state;
    void *effect_state = state_input;
    void *out_position = position_output;
    void *actor_data;
    register void *actor ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    void *effect_script;
    void **state_table;
    u8 *state_entry;
    S_FUNC_8197C800_BODY_4 *dungeon;
    void *effect;
    S_FUNC_8197C800_BODY_8 *sprite;
    S_FUNC_8197C800_BODY_6 *src_position;
    S_FUNC_8197C800_BODY_7 *dst_position;
    S_FUNC_8197C800_BODY_19 *status;
    void *effect_data;
    s32 remaining;
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 effect_height ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 coord ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 random_value ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register s16 *offset_table ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u16 angle;
    u16 tail_state;
    register u16 tail_timer ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *actor_page ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *particle_page;
    u8 *particle_origin;
    register u8 *burst_origin ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    u16 timer;
    static void *const state_labels[] = {
        &&case_zero, &&case_one, &&case_two, &&case_three, &&case_four
    };

    timer = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.s;
    actor_data = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_00;
    state = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_0A.s;
    timer -= 1;
    ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.s = timer;
    actor = (u8 *)actor_data - 0x20;

    (void)state_labels;
    if ((u32)state < 5) {
        state_table = D_80024008;
        state_entry = (u8 *)(((u32)state << 2) + (u32)state_table);
        goto *((void *)*(void **)state_entry);
    }
    return;

case_zero:
    ((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_F4 = 0;
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_00 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)actor)->unk_08))->unk_00;
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_04 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)actor)->unk_08))->unk_04;
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_08 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)actor)->unk_08))->unk_08;
    ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_0A.u += 1;

case_one:
    if (!(((S_FUNC_8197C800_BODY_21 *)(((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_04))->unk_00 & 0x80)) {
        return;
    }

    dungeon = D_800814A8[0];
    ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.s = 10;
    dungeon->unk_A6 -= 1;
    dungeon->unk_A8 = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_08;
    effect = func_8003FD64(0x312, D_80083498);
    if (effect == 0) {
        goto case_one_tail;
    }
    if (func_8003DE58(((S_FUNC_8197C800_BODY_22 *)(((S_FUNC_8197C800_BODY_3 *)actor)->unk_0C))->unk_08,
                      ((S_FUNC_8197C800_BODY_3 *)actor)->unk_0C, offsets, 0) == 0) {
        offsets[2] = 0;
        offsets[1] = 0;
        offsets[0] = 0;
    }
    effect_data = (u8 *)effect + 0x20;
    ((S_FUNC_8197C800_BODY_5 *)effect)->unk_10 = D_800246C0;
    func_8004491C(effect, D_80045340);
    random_value = 0x00800000u;
    sprite = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_0C;
    coord = offsets[0];
    src_position = ((S_FUNC_8197C800_BODY_3 *)actor)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
    result = src_position->unk_00 + (coord << 16);
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_00 = result;
    dst_position->unk_00 = result;
    coord = offsets[1];
    src_position = ((S_FUNC_8197C800_BODY_3 *)actor)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
    result = src_position->unk_04 + (coord << 16);
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_04 = result;
    dst_position->unk_04 = result;
    coord = offsets[2];
    src_position = ((S_FUNC_8197C800_BODY_3 *)actor)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
    result = src_position->unk_08 + (coord << 16);
    ((S_FUNC_8197C800_BODY_2 *)out_position)->unk_08 = result;
    dst_position->unk_08 = result;
    sprite->unk_1E = 0x800;
    sprite->unk_1C = 0x800;
    sprite->unk_10 = 0x20;
    sprite->unk_00 = D_800DEDB0;
    sprite->unk_14 |= 0xC;
    sprite->unk_08 = ((S_FUNC_8197C800_BODY_9 *)D_800DEDB0)->unk_04;
    random_value |= 0x8080u;
    sprite->unk_04 = 0;
    sprite->unk_05 = 0;
    sprite->unk_0C = (void *)random_value;
    ((S_FUNC_8197C800_BODY_5 *)effect)->unk_20 = effect_state;
    ((S_FUNC_8197C800_BODY_10 *)effect_data)->unk_4C = 0;
    goto case_one_tail;

case_one_tail:
    tail_state = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_0A.u + 1;
    ASM_TAILSLOT_PIN(tail_state);   /* MATCH pin: retail delay-slot fill depends on it */
    func_800245D8();

case_two:
    if (((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.u > 0) {
        return;
    }
    result = func_80053EF0(4);
    if (result != 2) {
        func_800A56E0(0x300);
    } else {
        func_800A56E0(0x4300);
    }
    tail_state = ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_0A.u;
    ASM_KEEP(tail_state);   /* MATCH pin: retail basic-block layout depends on it */
    tail_timer = 16;
    ASM_TAILSLOT_PIN(tail_timer);   /* MATCH pin: retail delay-slot contents depend on it */
    func_800245D0();

case_three:
    if (((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.u >= 3) {
        goto two_finish;
    }
    remaining = 1;
    actor_page = (u8 *)0x80080000;
    {
        S_FUNC_8197C800_BODY_11 *view_position;
        view_position = D_80083780;
        result = func_800BCB04(view_position->unk_02, view_position->unk_06,
                          (s16)(view_position->unk_0A - 0x80));
        effect_height = (s16)((result << 16) >> 16);
    }
    ASM_KEEP(actor_page);   /* MATCH pin: retail immediate-load split depends on it */
    effect_script = D_80024BB8;
    result = (s32)0x80080000;
    ASM_KEEP(result);   /* MATCH pin: keeps a constant in a register as retail does */
    burst_origin = (u8 *)result + 0x2E80;
    do {
        effect = func_8003FD64(0x312, D_80083498);
        if (effect != 0) {
            ((S_FUNC_8197C800_BODY_5 *)effect)->unk_10 = effect_script;
            func_8004491C(effect, D_80045340);
            sprite = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_0C;
            effect_data = (u8 *)effect + 0x20;
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_23 *)(((S_FUNC_8197C800_BODY_12 *)actor_page)->unk_14A8))->unk_2A;
            coord = (s16)angle >> 9;
            offset_table = D_8006CCD8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_13 *)burst_origin)->unk_24 + offset_table[coord];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
                ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 31;
                }
                jitter = random_value - ((rounded_random >> 5) << 5) + 16;
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
            }
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_23 *)(((S_FUNC_8197C800_BODY_12 *)actor_page)->unk_14A8))->unk_2A;
            coord = (s16)angle >> 9;
            offset_table = D_8006CCE8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_13 *)burst_origin)->unk_25 + offset_table[coord];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
                ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 31;
                }
                jitter = random_value - ((rounded_random >> 5) << 5) + 16;
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_06 = result;
            }
            {
                u32 color;
                void *sprite_template;
                void *position;
                color = 0x00600000u;
                ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
                position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                sprite_template = (void *)0x800E0000;
                ASM_KEEP(sprite_template);   /* MATCH pin: retail delay-slot fill depends on it */
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_0A = effect_height;
                sprite->unk_1C = 0x1800;
                sprite->unk_1E = 0x2000;
                sprite->unk_10 = 0x60;
                {
                    u16 flags;
                    flags = sprite->unk_14;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                    sprite_template = (u8 *)sprite_template - 0x1630;
                    sprite->unk_00 = sprite_template;
                    flags |= 0xC;
                    sprite->unk_14 = flags;
                    sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->unk_0C = (void *)(color | 0x6060u);
                ((S_FUNC_8197C800_BODY_5 *)effect)->unk_20 = effect_state;
                ((S_FUNC_8197C800_BODY_10 *)effect_data)->unk_4C = 0;
            }
        }
        remaining -= 1;
    } while (remaining >= 0);

    remaining = 9;
    effect_script = D_80024C68;
    particle_origin = D_80082E80;
    particle_page = (u8 *)0x80080000;
    do {
        effect = func_8003FD64(0x312, D_80083498);
        if (effect != 0) {
            ((S_FUNC_8197C800_BODY_5 *)effect)->unk_10 = effect_script;
            func_8004491C(effect, D_80045340);
            sprite = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_0C;
            effect_data = (u8 *)effect + 0x20;
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_24 *)(((S_FUNC_8197C800_BODY_16 *)particle_page)->unk_14A8))->unk_2A;
            coord = (s16)angle >> 9;
            offset_table = D_8006CCD8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_17 *)particle_origin)->unk_24 + offset_table[coord];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
                ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 63;
                }
                jitter = random_value - ((rounded_random >> 6) << 6);
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
            }
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_24 *)(((S_FUNC_8197C800_BODY_16 *)particle_page)->unk_14A8))->unk_2A;
            coord = (s16)angle >> 9;
            offset_table = D_8006CCE8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_17 *)particle_origin)->unk_25 + offset_table[coord];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)effect)->unk_08;
                ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 63;
                }
                jitter = random_value - ((rounded_random >> 6) << 6);
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_06 = result;
            }
            result = func_80069EF8();
            ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)effect)->unk_08))->unk_0A = effect_height - (result & 0x1F);
            result = func_80069EF8();
            {
                u32 color;
                register s32 size ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                void *sprite_template;
                color = 0x00100000u;
                ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
                ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)effect)->unk_08))->unk_14 =
                    (s32)0xFFE60000 - (result << 2);
                sprite->unk_1E = 0x800;
                sprite->unk_1C = 0x800;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                size = 0x20;
                sprite_template = (void *)0x800E0000;
                ASM_KEEP(sprite_template);   /* MATCH pin: retail delay-slot fill depends on it */
                sprite->unk_10 = size;
                {
                    u16 flags;
                    flags = sprite->unk_14;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                    sprite_template = (u8 *)sprite_template - 0x1400;
                    sprite->unk_00 = sprite_template;
                    flags |= 0xC;
                    sprite->unk_14 = flags;
                    sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->unk_0C = (void *)(color | 0x1010u);
                ((S_FUNC_8197C800_BODY_5 *)effect)->unk_20 = effect_state;
                ((S_FUNC_8197C800_BODY_10 *)effect_data)->unk_4C = 0;
            }
        }
        remaining -= 1;
    } while (remaining >= 0);

two_finish:
    if (((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.u > 0) {
        return;
    }
    ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.s = 32;
    ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_0A.u += 1;
    func_8002468C();

case_four:
    if (!(D_80082E94[0] & 0x8000) && ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_50.u >= 0) {
        return;
    }
    if (((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_52.s & 0x8000) {
        ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_52.u &= 0x7FFF;
    } else {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
        func_8009CE1C(((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_60, 8,
                      ((S_FUNC_8197C800_BODY_0 *)effect_state)->unk_09, 10,
                      ((S_FUNC_8197C800_BODY_18 *)actor_data)->unk_2A, actor_data, 2);
        status = D_80083460;
        status->unk_0C = 0;
        status->unk_0A -= 1;
        ((S_FUNC_8197C800_BODY_0_pre *)effect_state)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_8197C800\n"
    ".type func_8197C800,@function\n"
    ".size func_8197C800,1728\n");
#endif
