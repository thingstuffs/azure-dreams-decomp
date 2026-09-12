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

void FUNC_8197C800_BODY(void *input, void *output)
    __attribute__((section(".text.func_8197C800")));

/* Updates a timed effect, spawns particles, and completes its owner's action. */
void FUNC_8197C800_BODY(void *input, void *output)
{
    s16 offsets[3];
    s32 state;
    void *effect = input;
    void *effect_position = output;
    void *owner_data;
    register void *owner ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *particle_script;
    void **state_table;
    u8 *state_entry;
    S_FUNC_8197C800_BODY_4 *scene;
    void *particle;
    S_FUNC_8197C800_BODY_8 *sprite;
    S_FUNC_8197C800_BODY_6 *src_position;
    S_FUNC_8197C800_BODY_7 *dst_position;
    S_FUNC_8197C800_BODY_19 *status;
    void *particle_data;
    s32 remaining;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 height ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 offset_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 random_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 *direction_offsets ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 angle;
    u16 tail_state;
    register u16 tail_timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *scene_page ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *debris_scene_page;
    u8 *debris_origin;
    register u8 *burst_origin ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 timer;
    s32 scaled_coord;
    static void *const state_labels[] = {
        &&case_zero, &&case_one, &&case_two, &&case_three, &&case_four
    };

    timer = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.s;
    owner_data = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_00;
    state = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_0A.s;
    timer -= 1;
    ((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.s = timer;
    owner = (u8 *)owner_data - 0x20;

    (void)state_labels;
    if ((u32)state < 5) {
        state_table = D_80024008;
        state_entry = (u8 *)(((u32)state << 2) + (u32)state_table);
        goto *((void *)*(void **)state_entry);
    }
    return;

case_zero:
    ((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_F4 = 0;
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_00 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_00;
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_04 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_04;
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_08 = ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_08;
    ((S_FUNC_8197C800_BODY_0 *)effect)->unk_0A.u += 1;

case_one:
    if (!(((S_FUNC_8197C800_BODY_21 *)(((S_FUNC_8197C800_BODY_0 *)effect)->unk_04))->unk_00 & 0x80)) {
        return;
    }

    scene = D_800814A8[0];
    ((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.s = 10;
    scene->unk_A6 -= 1;
    scene->unk_A8 = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_08;
    particle = func_8003FD64(0x312, D_80083498);
    if (particle == 0) {
        goto case_one_tail;
    }
    if (func_8003DE58(((S_FUNC_8197C800_BODY_22 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C))->unk_08,
                      ((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C, offsets, 0) == 0) {
        offsets[2] = 0;
        offsets[1] = 0;
        offsets[0] = 0;
    }
    particle_data = (u8 *)particle + 0x20;
    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = D_800246C0;
    func_8004491C(particle, D_80045340);
    random_value = 0x00800000u;
    sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
    offset_index = offsets[0];
    src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
    result = src_position->unk_00 + (offset_index << 16);
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_00 = result;
    dst_position->unk_00 = result;
    offset_index = offsets[1];
    src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
    result = src_position->unk_04 + (offset_index << 16);
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_04 = result;
    dst_position->unk_04 = result;
    offset_index = offsets[2];
    src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
    dst_position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
    result = src_position->unk_08 + (offset_index << 16);
    ((S_FUNC_8197C800_BODY_2 *)effect_position)->unk_08 = result;
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
    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = effect;
    ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
    goto case_one_tail;

case_one_tail:
    tail_state = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_0A.u + 1;
    ASM_TAILSLOT_PIN(tail_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    func_800245D8();

case_two:
    if (((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.u > 0) {
        return;
    }
    result = func_80053EF0(4);
    if (result != 2) {
        func_800A56E0(0x300);
    } else {
        func_800A56E0(0x4300);
    }
    tail_state = ((S_FUNC_8197C800_BODY_0 *)effect)->unk_0A.u;
    ASM_KEEP(tail_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    tail_timer = 16;
    ASM_TAILSLOT_PIN(tail_timer);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_800245D0();

case_three:
    if (((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.u >= 3) {
        goto two_finish;
    }
    remaining = 1;
    scene_page = (u8 *)0x80080000;
    {
        S_FUNC_8197C800_BODY_11 *reference_position;
        reference_position = D_80083780;
        result = func_800BCB04(reference_position->unk_02, reference_position->unk_06,
                          (s16)(reference_position->unk_0A - 0x80));
        height = (s16)((result << 16) >> 16);
    }
    ASM_KEEP(scene_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    particle_script = D_80024BB8;
    result = (s32)0x80080000;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    burst_origin = (u8 *)result + 0x2E80;
    do {
        particle = func_8003FD64(0x312, D_80083498);
        if (particle != 0) {
            ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = particle_script;
            func_8004491C(particle, D_80045340);
            sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
            particle_data = (u8 *)particle + 0x20;
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_23 *)(((S_FUNC_8197C800_BODY_12 *)scene_page)->unk_14A8))->unk_2A;
            offset_index = (s16)angle >> 9;
            direction_offsets = D_8006CCD8;
            {
                s32 grid_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_13 *)burst_origin)->unk_24 + direction_offsets[offset_index];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 31;
                }
                jitter = random_value - ((rounded_random >> 5) << 5) + 16;
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
            }
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_23 *)(((S_FUNC_8197C800_BODY_12 *)scene_page)->unk_14A8))->unk_2A;
            offset_index = (s16)angle >> 9;
            direction_offsets = D_8006CCE8;
            {
                s32 grid_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_13 *)burst_origin)->unk_25 + direction_offsets[offset_index];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
                ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                sprite_template = (void *)0x800E0000;
                ASM_KEEP(sprite_template);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_0A = height;
                sprite->unk_1C = 0x1800;
                sprite->unk_1E = 0x2000;
                sprite->unk_10 = 0x60;
                {
                    u16 flags;
                    flags = sprite->unk_14;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    sprite_template = (u8 *)sprite_template - 0x1630;
                    sprite->unk_00 = sprite_template;
                    flags |= 0xC;
                    sprite->unk_14 = flags;
                    sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->unk_0C = (void *)(color | 0x6060u);
                ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = effect;
                ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
            }
        }
        remaining -= 1;
    } while (remaining >= 0);

    remaining = 9;
    particle_script = D_80024C68;
    debris_origin = D_80082E80;
    debris_scene_page = (u8 *)0x80080000;
    do {
        particle = func_8003FD64(0x312, D_80083498);
        if (particle != 0) {
            ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = particle_script;
            func_8004491C(particle, D_80045340);
            sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
            particle_data = (u8 *)particle + 0x20;
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_24 *)(((S_FUNC_8197C800_BODY_16 *)debris_scene_page)->unk_14A8))->unk_2A;
            offset_index = (s16)angle >> 9;
            direction_offsets = D_8006CCD8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_17 *)debris_origin)->unk_24 + direction_offsets[offset_index];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 63;
                }
                jitter = random_value - ((rounded_random >> 6) << 6);
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
            }
            random_value = func_80069EF8();
            angle = ((S_FUNC_8197C800_BODY_24 *)(((S_FUNC_8197C800_BODY_16 *)debris_scene_page)->unk_14A8))->unk_2A;
            offset_index = (s16)angle >> 9;
            direction_offsets = D_8006CCE8;
            {
                s32 grid_coord;
                s32 scaled_coord;
                s32 rounded_random;
                s32 jitter;
                void *position;
                grid_coord = ((S_FUNC_8197C800_BODY_17 *)debris_origin)->unk_25 + direction_offsets[offset_index];
                rounded_random = random_value;
                position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                scaled_coord = grid_coord << 6;
                if (random_value < 0) {
                    rounded_random = random_value + 63;
                }
                jitter = random_value - ((rounded_random >> 6) << 6);
                result = scaled_coord + jitter;
                ((S_FUNC_8197C800_BODY_14 *)position)->unk_06 = result;
            }
            result = func_80069EF8();
            ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)particle)->unk_08))->unk_0A = height - (result & 0x1F);
            result = func_80069EF8();
            {
                u32 color;
                register s32 sprite_size ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                void *sprite_template;
                color = 0x00100000u;
                ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)particle)->unk_08))->unk_14 =
                    (s32)0xFFE60000 - (result << 2);
                sprite->unk_1E = 0x800;
                sprite->unk_1C = 0x800;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                sprite_size = 0x20;
                sprite_template = (void *)0x800E0000;
                ASM_KEEP(sprite_template);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                sprite->unk_10 = sprite_size;
                {
                    u16 flags;
                    flags = sprite->unk_14;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    sprite_template = (u8 *)sprite_template - 0x1400;
                    sprite->unk_00 = sprite_template;
                    flags |= 0xC;
                    sprite->unk_14 = flags;
                    sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->unk_0C = (void *)(color | 0x1010u);
                ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = effect;
                ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
            }
        }
        remaining -= 1;
    } while (remaining >= 0);

two_finish:
    if (((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.u > 0) {
        return;
    }
    ((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.s = 32;
    ((S_FUNC_8197C800_BODY_0 *)effect)->unk_0A.u += 1;
    func_8002468C();

case_four:
    if (!(D_80082E94[0] & 0x8000) && ((S_FUNC_8197C800_BODY_0 *)effect)->unk_50.u >= 0) {
        return;
    }
    if (((S_FUNC_8197C800_BODY_0 *)effect)->unk_52.s & 0x8000) {
        ((S_FUNC_8197C800_BODY_0 *)effect)->unk_52.u &= 0x7FFF;
        func_8002468C();
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    func_8009CE1C(((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_60, 8,
                  ((S_FUNC_8197C800_BODY_0 *)effect)->unk_09, 10,
                  ((S_FUNC_8197C800_BODY_18 *)owner_data)->unk_2A, owner_data, 2);
    status = D_80083460;
    status->unk_0C = 0;
    status->unk_0A -= 1;
    ((S_FUNC_8197C800_BODY_0_pre *)effect)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

#ifdef __mips__
__asm__(
    ".globl func_8197C800\n"
    ".type func_8197C800,@function\n"
    ".size func_8197C800,1728\n");
#endif
