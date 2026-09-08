#include "common.h"
#include "records/Rec_D_80016000.h"

typedef struct S_81844800_0_pre {
    u16 unk_00;
} S_81844800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */

typedef struct S_81844800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { u16 s; s16 u; } unk_52;   /* accessed as both */
} S_81844800_0;   /* arg0 in BODY_NAME */

typedef struct S_81844800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_1_pre;   /* the 0x14 bytes before root in BODY_NAME, addressed as root[-1] */

typedef struct S_81844800_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_81844800_1;   /* root in BODY_NAME */

typedef struct S_81844800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81844800_2;   /* object in BODY_NAME */

typedef struct S_81844800_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_81844800_3;   /* arg1_reg in BODY_NAME */

typedef struct S_81844800_4 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_81844800_4;   /* render in BODY_NAME */

typedef struct S_81844800_5 {
    u8 pad_00[0x4];
    u32 unk_04;
} S_81844800_5;   /* s8_page in BODY_NAME */

typedef struct S_81844800_6 {
    u8 pad_00[0x48];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_81844800_6;   /* part in BODY_NAME */

typedef struct S_81844800_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_81844800_7;   /* info in BODY_NAME */

typedef struct S_81844800_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_8_pre;   /* the 0x14 bytes before created in BODY_NAME, addressed as created[-1] */

typedef struct S_81844800_9 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81844800_9;   /* arg2_reg in BODY_NAME */

typedef struct S_81844800_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81844800_10;   /* base_before in BODY_NAME */

typedef struct S_81844800_11 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_11;   /* base_after in BODY_NAME */

typedef struct S_81844800_12 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x20];
    u16 unk_2A;
    u16 unk_2C;
} S_81844800_12;   /* initial_part in BODY_NAME */


typedef struct S_81844800_14 {
    union { s32 * s; s32 u; } unk_00;   /* accessed as both */
    union { s32 * s; s32 u; } unk_04;   /* accessed as both */
    union { struct { s32 * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_81844800_14;   /* ((S_81844800_2 *)object)->unk_08 in BODY_NAME */

typedef struct S_81844800_15 {
    u16 unk_00;
} S_81844800_15;   /* ((S_81844800_0 *)arg0)->unk_04 in BODY_NAME */

typedef struct S_81844800_16 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_16;   /* ((S_81844800_10 *)base_before)->unk_0C in BODY_NAME */

typedef struct S_81844800_17 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81844800_17;   /* ((S_81844800_11 *)base_after)->unk_08 in BODY_NAME */



typedef struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
} Vec3;


extern u8 D_80083498[];
extern u8 D_800DEA68[];
extern u8 D_800DECF8[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];

extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void *func_8003DE58(void *, void *, Vec3 *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_8004491C(void *, void *);

extern void func_80024020(void);
extern void func_800241AC(void);
extern void func_800243D8(void);
extern void func_80024430(void);
extern void func_8002447C(void);
extern void func_80024684(void);
extern void func_800246B4(void);
__asm__(".set func_80024020, 0x80024020");
__asm__(".set func_800241AC, 0x800241ac");
__asm__(".set func_800243D8, 0x800243d8");
__asm__(".set func_80024430, 0x80024430");
__asm__(".set func_8002447C, 0x8002447c");
__asm__(".set func_80024684, 0x80024684");
__asm__(".set func_800246B4, 0x800246b4");

extern void func_80024C84(void);
extern void func_80024868(void);
extern void func_8002472C(void);
__asm__(".set func_80024C84, 0x80024c84");
__asm__(".set func_80024868, 0x80024868");
__asm__(".set func_8002472C, 0x8002472c");

extern void func_8002428C(void) __attribute__((noreturn));
extern void func_80024468(void) __attribute__((noreturn));
extern void func_800246A0(void) __attribute__((noreturn));
extern void func_800246A4(void) __attribute__((noreturn));
extern void func_800246F8(void) __attribute__((noreturn));
__asm__(".set func_8002428C, 0x8002428c");
__asm__(".set func_80024468, 0x80024468");
__asm__(".set func_800246A0, 0x800246a0");
__asm__(".set func_800246A4, 0x800246a4");
__asm__(".set func_800246F8, 0x800246f8");

/* Retail places an 8-entry (32-byte) callee jump table immediately before this
 * function's own code, all under the func_81844800 symbol (one 1836-byte
 * span). The table is pinned to the function's own named section (not the
 * generic ".text") so it lands ahead of the compiled body in the same output
 * section, byte-for-byte and gap-free -- a naked-asm label + a bare
 * section(".text") table (the original approach) leaves the table in the
 * literal ".text" section, which the land gate's `.text.func_81844800`-scoped
 * KEEP rule never sees, so the table silently zero-fills (bare-text-pin
 * class; cf. func_81892800.c, func_808CB000.c BODY_ATTR shape). BODY_ATTR is
 * applied directly to the compiled body (not left to ccproc.py's `.ent`-name
 * rename) so both halves land in the identical named section regardless of
 * toolchain quirks. */
#ifdef __mips__
static void (*const func_81844800_table[])(void)
    __asm__("func_81844800")
    __attribute__((section(".text.func_81844800"), aligned(4))) = {
        func_80024020,
        0,
        func_800241AC,
        func_800243D8,
        func_80024430,
        func_8002447C,
        func_80024684,
        func_800246B4,
    };
__asm__(".globl func_81844800\n"
        ".type func_81844800,@function\n"
        ".size func_81844800, 1836");
#define BODY_NAME composite_body_81844800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81844800")))
#else
#define BODY_NAME func_81844800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *effect_in, void *motion_in, void *source_render) BODY_ATTR;
/* Updates a staged effect, moves it toward its target, and emits particles. */
BODY_STORAGE void BODY_NAME(void *effect_in, void *motion_in, void *source_render) {
    static void *const state_labels[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4, &&case5
    };
    void *effect = effect_in;
    void *motion;
    register void *owner ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Vec3 delta;
    void * volatile owner_base;
    void *owner_sprite;
    void *spawned;
    void *particle_data;
    void *sprite;
    register s32 particles_left ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_81844800_5 *sprite_page;
    s16 state;

    owner = ((S_81844800_0 *)effect)->unk_00;
    {
        register void *owner_start ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        owner_start = (u8 *)owner - 0x20;
        owner_base = owner_start;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    state = ((S_81844800_0 *)effect)->unk_0A.s;
    owner_sprite = ((S_81844800_1_pre *)owner)[-1].unk_00;
    motion = motion_in;
    if (state == 0) {
        goto dispatch;
    }
    if (state < 5) {
        particles_left = 12;
        sprite_page = D_800DEA68;
        do {
            spawned = func_8003FD64(0x312, &D_80083498);
            if (spawned != 0) {
                particle_data = (u8 *)spawned + 0x20;
                sprite = ((S_81844800_2 *)spawned)->unk_0C;
                ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                {
                    register void *callback ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    callback = func_80024C84;
                    ((S_81844800_2 *)spawned)->unk_10 = callback;
                }
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_00.s =
                    ((S_81844800_3 *)motion)->unk_00.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 13);
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_04.s =
                    ((S_81844800_3 *)motion)->unk_04.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 13);
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_08.at00.v =
                    ((S_81844800_3 *)motion)->unk_08.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 10);

                {
                    u16 flags = ((S_81844800_4 *)sprite)->unk_14;
                    ((S_81844800_4 *)sprite)->unk_1E = 0x1000;
                    ((S_81844800_4 *)sprite)->unk_1C = 0x1000;
                    ((S_81844800_4 *)sprite)->unk_10 = 0x40;
                    ((S_81844800_4 *)sprite)->unk_00 = sprite_page;
                    ((S_81844800_4 *)sprite)->unk_14 = flags | 0xC;
                    {
                        u32 texture_page = sprite_page->unk_04;
                        ((S_81844800_4 *)sprite)->unk_04 = 0;
                        ((S_81844800_4 *)sprite)->unk_05 = 0;
                        ((S_81844800_4 *)sprite)->unk_0C = 0x00404040;
                        ((S_81844800_4 *)sprite)->unk_08 = texture_page;
                    }
                }
                ((S_81844800_2 *)spawned)->unk_20 = effect;
                ((S_81844800_6 *)particle_data)->unk_48 = func_80069EF8() & 3;
                ((S_81844800_6 *)particle_data)->unk_4A = 8;
                ((S_81844800_6 *)particle_data)->unk_4C = 0;
            }
            particles_left--;
        } while (particles_left >= 0);
    }

dispatch:
    {
        s32 state_index = ((S_81844800_0 *)effect)->unk_0A.s;
        if ((u32)state_index >= 6) {
            goto done;
        }
        (void)state_labels;
        goto *jtbl_80024008[state_index];
    }

case0:
    {
        void *target;
        if ((((S_81844800_15 *)(((S_81844800_0 *)effect)->unk_04))->unk_00 & 0x80) == 0) {
            goto done;
        }
        target = func_800A05A4(
            owner,
            ((S_81844800_7 *)owner_sprite)->unk_24,
            ((S_81844800_7 *)owner_sprite)->unk_25,
            ((S_81844800_1 *)owner)->unk_2A,
            (s16)func_800A3820(9));
        ((S_81844800_1 *)owner)->unk_60 = target;
        if (target == 0) {
            ((S_81844800_1 *)owner)->unk_72.s = ((S_81844800_7 *)owner_sprite)->unk_24;
            ((S_81844800_1 *)owner)->unk_73.s = ((S_81844800_7 *)owner_sprite)->unk_25;
            func_8002428C();
            return;
        }
        sprite = ((S_81844800_8_pre *)target)[-1].unk_00;
        if ((((S_81844800_4 *)sprite)->unk_14 & 0x8000) != 0) {
            register void *source_sprite ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            source_sprite = source_render;
            ASM_KEEP(source_sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if ((((S_81844800_9 *)source_sprite)->unk_14 & 0x8000) != 0) {
                func_8009CE1C(
                    ((S_81844800_1 *)owner)->unk_60,
                    10,
                    ((S_81844800_0 *)effect)->unk_09,
                    4,
                    ((S_81844800_1 *)owner)->unk_2A,
                    owner,
                    2);
                {
                    s32 next_state = 5;
                    ASM_TAILSLOT_PIN_TIED(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_80024468();
                    return;
                }
            }
        }
        ((S_81844800_1 *)owner)->unk_72.s = ((S_81844800_4 *)sprite)->unk_24;
        ((S_81844800_1 *)owner)->unk_73.s = ((S_81844800_4 *)sprite)->unk_25;
        {
            register void *owner_before ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            owner_before = owner_base;
            if (func_8003DE58(
                ((S_81844800_16 *)(((S_81844800_10 *)owner_before)->unk_0C))->unk_08,
                ((S_81844800_10 *)owner_before)->unk_0C, &delta, 0) == 0) {
                delta.z = 0;
                delta.y = 0;
                delta.x = 0;
            }
            {
                register void *owner_after ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                owner_after = owner_base;
                ((S_81844800_3 *)motion)->unk_00.at02.v = ((S_81844800_17 *)(((S_81844800_11 *)owner_after)->unk_08))->unk_02 + delta.x;
                ((S_81844800_3 *)motion)->unk_04.at02.v = ((S_81844800_17 *)(((S_81844800_11 *)owner_after)->unk_08))->unk_06 + delta.y;
                ((S_81844800_3 *)motion)->unk_08.at02.v = ((S_81844800_17 *)(((S_81844800_11 *)owner_after)->unk_08))->unk_0A + delta.z;
                ((S_81844800_0 *)effect)->unk_50.s = 8;
                {
                    register s32 target_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    target_x = ((S_81844800_1 *)owner)->unk_72.u;
                    ASM_KEEP(target_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    {
                        s16 start_x = ((S_81844800_3 *)motion)->unk_00.at02.v - 0x20;
                        ((S_81844800_3 *)motion)->unk_0C.at02.v = (target_x << 6) - start_x;
                    }
                }
                ((S_81844800_3 *)motion)->unk_0C.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                {
                    register s32 target_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    target_y = ((S_81844800_1 *)owner)->unk_73.u;
                    ASM_KEEP(target_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    {
                        s16 start_y = ((S_81844800_3 *)motion)->unk_04.at02.v - 0x20;
                        ((S_81844800_3 *)motion)->unk_10.at02.v = (target_y << 6) - start_y;
                    }
                }
                ((S_81844800_3 *)motion)->unk_10.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                ((S_81844800_3 *)motion)->unk_14.at02.v = func_800BCB04(
                    ((S_81844800_3 *)motion)->unk_00.at02.v,
                    ((S_81844800_3 *)motion)->unk_04.at02.v,
                    (s16)(((S_81844800_17 *)(((S_81844800_11 *)owner_after)->unk_08))->unk_0A - 48)) -
                    (((S_81844800_3 *)motion)->unk_08.at02.v + 176);
            }
            ((S_81844800_3 *)motion)->unk_14.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
            func_800A56E0(0x300);
            func_800246A0();
            return;
        }
    }

case1:
    ((S_81844800_3 *)motion)->unk_00.at00.v += ((S_81844800_3 *)motion)->unk_0C.at00.v;
    ((S_81844800_3 *)motion)->unk_04.at00.v += ((S_81844800_3 *)motion)->unk_10.at00.v;
    ((S_81844800_3 *)motion)->unk_08.at00.v += ((S_81844800_3 *)motion)->unk_14.at00.v;
    state = ((S_81844800_0 *)effect)->unk_50.s - 1;
    ((S_81844800_0 *)effect)->unk_50.s = state;
    if ((state << 16) > 0) {
        goto done;
    }
    {
        register u16 timer_reset ASM_REG("$3") = 12;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = ((S_81844800_0 *)effect)->unk_0A.u;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_81844800_0 *)effect)->unk_50.s = timer_reset;
        func_800246A4();
        return;
    }

case2:
    {
        register u16 target_timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            goto done;
        }
        if (((S_81844800_1 *)owner)->unk_60 != 0) {
            target_timer = 10;
            goto case2_nonzero;
        }
        ((S_81844800_0 *)effect)->unk_50.s = 8;
        ((S_81844800_0 *)effect)->unk_0A.u = 5;
        func_800246F8();
        return;

case2_nonzero:
        state = ((S_81844800_0 *)effect)->unk_0A.u;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_81844800_0 *)effect)->unk_50.s = target_timer;
        func_800246A4();
        return;
    }

case3:
    if ((((S_81844800_0 *)effect)->unk_52.s & 0x7FFF) == 0) {
        spawned = func_8003FD64(0x201, &D_80083498);
        if (spawned != 0) {
            S_81844800_12 *burst_data = (u8 *)spawned + 0x20;
            ((S_81844800_2 *)spawned)->unk_10 = func_8002472C;
            func_8004491C(spawned, func_80024868);
            burst_data->unk_2A = 8;
            ((S_81844800_2 *)spawned)->unk_20 = effect;
            burst_data->unk_04 = ((S_81844800_3 *)motion)->unk_00.at02.v;
            burst_data->unk_06 = ((S_81844800_3 *)motion)->unk_04.at02.v;
            burst_data->unk_08 = ((S_81844800_3 *)motion)->unk_08.at02.v;
            ((S_81844800_0 *)effect)->unk_52.s++;
            burst_data->unk_2C = 0;
        }
    }
    if (((S_81844800_0 *)effect)->unk_50.u == 7 &&
        ((S_81844800_1 *)owner)->unk_60 != 0) {
        func_8009CE1C(
            ((S_81844800_1 *)owner)->unk_60,
            10,
            ((S_81844800_0 *)effect)->unk_09,
            4,
            ((S_81844800_1 *)owner)->unk_2A,
            owner,
            2);
    }
    particles_left = 20;
    do {
        spawned = func_8003FD64(0x312, &D_80083498);
        if (spawned != 0) {
            particle_data = (u8 *)spawned + 0x20;
            ASM_KEEP(particle_data);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            sprite = ((S_81844800_2 *)spawned)->unk_0C;
            ((S_81844800_2 *)spawned)->unk_10 = func_80024C84;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_00.u = ((S_81844800_3 *)motion)->unk_00.at00.v;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_04.u = ((S_81844800_3 *)motion)->unk_04.at00.v;
            state = (func_80069EF8() & 0x3F) - 176;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_08.at02.v = ((S_81844800_3 *)motion)->unk_08.at02.v - state;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_0E = (func_80069EF8() & 0xF) - 8;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_12 = (func_80069EF8() & 0xF) - 8;
            ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_16 = -(func_80069EF8() & 7);
            {
                u16 flags = ((S_81844800_4 *)sprite)->unk_14;
                ((S_81844800_4 *)sprite)->unk_1E = 0x1000;
                ((S_81844800_4 *)sprite)->unk_1C = 0x1000;
                ((S_81844800_4 *)sprite)->unk_10 = 0x60;
                ((S_81844800_4 *)sprite)->unk_00 = D_800DECF8;
                ((S_81844800_4 *)sprite)->unk_14 = flags | 0xC;
                {
                    u32 texture_page = ((Rec_D_80016000 *)D_800DECF8)->unk_04.at00_u32.v;
                    ((S_81844800_4 *)sprite)->unk_04 = 0;
                    ((S_81844800_4 *)sprite)->unk_05 = 0;
                    ((S_81844800_4 *)sprite)->unk_0C = 0x00404040;
                    ((S_81844800_4 *)sprite)->unk_08 = texture_page;
                }
            }
            ((S_81844800_2 *)spawned)->unk_20 = effect;
            ((S_81844800_6 *)particle_data)->unk_48 = func_80069EF8() & 3;
            ((S_81844800_6 *)particle_data)->unk_4A = 16;
            ((S_81844800_6 *)particle_data)->unk_4C = 0;
        }
        particles_left--;
    } while (particles_left >= 0);
    state = ((S_81844800_0 *)effect)->unk_50.s - 1;
    ((S_81844800_0 *)effect)->unk_50.s = state;
    if ((state << 16) > 0) {
        goto done;
    }
    {
        register u16 timer_reset ASM_REG("$3") = 8;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = ((S_81844800_0 *)effect)->unk_0A.u;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_81844800_0 *)effect)->unk_50.s = timer_reset;
        func_800246A4();
        return;
    }

case4:
    state = ((S_81844800_0 *)effect)->unk_50.s - 1;
    ((S_81844800_0 *)effect)->unk_50.s = state;
    if ((state << 16) > 0) {
        goto done;
    }
    ((S_81844800_0 *)effect)->unk_0A.u++;
    func_800246F8();
    return;

case5:
    {
        u16 effect_count;
        if ((((S_81844800_0 *)effect)->unk_52.u & 0x8000) != 0) {
            effect_count = ((S_81844800_0 *)effect)->unk_52.s & 0x7FFF;
            ((S_81844800_0 *)effect)->unk_52.s = effect_count;
            func_800246F8();
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        D_8008346C[0] = 0;
        ((S_81844800_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

done:
    return;
}
