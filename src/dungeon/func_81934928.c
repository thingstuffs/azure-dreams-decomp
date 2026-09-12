#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81934928_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    union { u16 s; s16 u; } unk_12;   /* accessed as both */
    u16 unk_14;
} S_81934928_0;   /* self in func_81934928 */

typedef struct S_81934928_1 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    u8 pad_04[0x2];
    volatile u16 unk_06;
    u8 pad_08[0x2];
    volatile u16 unk_0A;
} S_81934928_1;   /* copy_page in func_81934928 */

typedef struct S_81934928_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934928_2;   /* created in func_81934928 */

typedef struct S_81934928_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_81934928_3;   /* part in func_81934928 */

typedef struct S_81934928_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81934928_4;   /* found in func_81934928 */

typedef struct S_81934928_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81934928_5;   /* owner in func_81934928 */

typedef struct S_81934928_6 {
    u16 unk_00;
} S_81934928_6;   /* ((S_81934928_0 *)self)->unk_04 in func_81934928 */



typedef struct {
    s32 word[6];
} Copy24;

extern void func_80024004(void *);
extern void func_80024344(void) __attribute__((noreturn));
extern void func_80024434(void) __attribute__((noreturn));
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void *func_800A3F28(s32, s32, void *, void *);
extern void func_800A56E0(s32);

extern s32 D_8002445C[];
extern s32 D_80024740[];
extern s32 D_800814A0;
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern s32 D_8008346C;
extern s32 D_80083498[];
extern Copy24 D_80083780;

/* Spawns a timed particle effect, processes its midpoint target, and marks completion. */
void func_81934928(void *effect, void *output)
{
    register void *self ASM_REG("$18") = effect;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *output_data ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register void *owner ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *search_origin;
    void *target;
    void *saved_origin;
    register void *tail_origin ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    void *particle;
    s32 rand_quotient;
    s16 state;
    s32 spawn_index;
    s32 origin_component;
    s32 random_value;
    s32 value;
    s16 countdown;

    state = ((S_81934928_0 *)self)->unk_0A.s;
    owner = ((S_81934928_0 *)self)->unk_00;
    output_data = output;
    if (state != 1) {
        if (state < 2) {
            if (state != 0) {
                func_80024434();
            }
        } else {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (state == 0xFF) {
                goto state_ff;
            }
            func_80024434();
        }
        ASM_KEEP(output_data);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if ((((S_81934928_6 *)(((S_81934928_0 *)self)->unk_04))->unk_00 & 0x80) == 0) {
            goto done;
        }
        {
            u8 *copy_page;
            register Copy24 *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            s32 copy_word_0;
            s32 copy_word_1;
            s32 copy_word_2;
#ifdef NON_MATCHING
            copy_page = (u8 *)&D_80083780 - 0x3780;
#else
            copy_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            copy_src = (Copy24 *)(copy_page + 0x3780);
            ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            copy_word_0 = copy_src->word[0];
            copy_word_1 = copy_src->word[1];
            copy_word_2 = copy_src->word[2];
            ((s32 *)output_data)[0] = copy_word_0;
            ((s32 *)output_data)[1] = copy_word_1;
            ((s32 *)output_data)[2] = copy_word_2;
            copy_word_0 = copy_src->word[3];
            copy_word_1 = copy_src->word[4];
            copy_word_2 = copy_src->word[5];
            ((s32 *)output_data)[3] = copy_word_0;
            ((s32 *)output_data)[4] = copy_word_1;
            ((s32 *)output_data)[5] = copy_word_2;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            copy_page += 0x3780;
            ((S_81934928_0 *)self)->unk_10.s = ((S_81934928_1 *)copy_page)->unk_02;
            ((S_81934928_0 *)self)->unk_12.s = ((S_81934928_1 *)copy_page)->unk_06;
            value = ((S_81934928_1 *)copy_page)->unk_0A;
        }
        ((S_81934928_0 *)self)->unk_0C.s = 0x3C;
        ((S_81934928_0 *)self)->unk_0A.u++;
        ((S_81934928_0 *)self)->unk_14 = value;
        func_800A56E0(0x300);
    }

main_state:
    spawn_index = 0x3C - ((S_81934928_0 *)self)->unk_0C.u;
    if (spawn_index >= 8) {
        spawn_index = 8;
    }
    if (spawn_index >= 0) {
        do {
            particle = func_8003FD64(0x202, D_80083498);
            if (particle != NULL) {
                ((S_81934928_2 *)particle)->unk_10 = D_8002445C;
                func_8004491C(particle, D_80024740);
                search_origin = (u8 *)particle + 0x20;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_10.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0C = value;
                ((S_81934928_3 *)search_origin)->unk_1E = value;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_12.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0E = value;
                ((S_81934928_3 *)search_origin)->unk_22 = value;

                value = ((S_81934928_0 *)self)->unk_14 - 0x100;
                ((S_81934928_3 *)search_origin)->unk_10 = value;
                ((S_81934928_3 *)search_origin)->unk_26 = value;
                ((S_81934928_2 *)particle)->unk_20 = self;
            }
            spawn_index--;
        } while (spawn_index >= 0);
    }

    if (((S_81934928_0 *)self)->unk_0C.u == 0x1E) {
        search_origin = D_800814A8;
        if (search_origin != NULL) {
            u8 *search_page;
            register u8 *lookup_table ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 lookup_key_a;
            s32 lookup_key_b;
            void *lookup_origin;
            void *lookup_context;
            saved_origin = search_origin;
            ASM_KEEP_NV(saved_origin);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            search_page = D_80082E80 - 0x2E80;
#else
            search_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(search_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            lookup_table = search_page + 0x2E80;
            ASM_KEEP(search_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            lookup_origin = saved_origin;
            lookup_key_a = lookup_table[0x24];
            lookup_key_b = lookup_table[0x25];
            lookup_context = search_origin;
            target = func_800A3F28(lookup_key_a, lookup_key_b, lookup_origin, lookup_context);
            if (target != NULL) {
                if ((((S_81934928_4 *)target)->unk_1C & 0x2000) == 0) {
                    func_8009CE1C(target, 0x20, ((S_81934928_0 *)self)->unk_09, 0xA,
                                  ((S_81934928_5 *)owner)->unk_2A, owner, 2);
                }
                func_80024004(target);
                tail_origin = saved_origin;
                ASM_TAILSLOT_PIN(tail_origin);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                func_80024344();
            }
        }
    }

    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        goto done;
    }
    ((S_81934928_0 *)self)->unk_0C.s = 8;
    ((S_81934928_0 *)self)->unk_0A.u = 0xFF;
    func_80024434();

state_ff:
    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        goto done;
    }
    {
        u16 effect_flags;
        value = ((S_81934928_0 *)self)->unk_0E.s;
        effect_flags = ((S_81934928_0 *)self)->unk_0E.u;
        if ((value & 0x8000) != 0) {
            value = effect_flags & 0x7FFF;
            ((S_81934928_0 *)self)->unk_0E.u = value;
            func_80024434();
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)self + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
