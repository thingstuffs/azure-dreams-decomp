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

void func_81934928(void *arg0, void *arg1)
{
    register void *self ASM_REG("$18") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register void *owner ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *search ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *found;
    void *search_copy;
    register void *tail_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    void *created;
    register s32 arithmetic ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 state;
    s32 count;
    s32 base;
    s32 random;
    s32 value;
    s16 countdown;
    void *part;

    state = ((S_81934928_0 *)self)->unk_0A.s;
    owner = ((S_81934928_0 *)self)->unk_00;
    dst = arg1;
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
        ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if ((((S_81934928_6 *)(((S_81934928_0 *)self)->unk_04))->unk_00 & 0x80) == 0) {
            goto done;
        }
        {
            u8 *copy_page;
            register Copy24 *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            s32 copy0;
            s32 copy1;
            s32 copy2;
#ifdef NON_MATCHING
            copy_page = (u8 *)&D_80083780 - 0x3780;
#else
            copy_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            copy_src = (Copy24 *)(copy_page + 0x3780);
            ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            copy0 = copy_src->word[0];
            copy1 = copy_src->word[1];
            copy2 = copy_src->word[2];
            ((s32 *)dst)[0] = copy0;
            ((s32 *)dst)[1] = copy1;
            ((s32 *)dst)[2] = copy2;
            copy0 = copy_src->word[3];
            copy1 = copy_src->word[4];
            copy2 = copy_src->word[5];
            ((s32 *)dst)[3] = copy0;
            ((s32 *)dst)[4] = copy1;
            ((s32 *)dst)[5] = copy2;
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
    count = 0x3C - ((S_81934928_0 *)self)->unk_0C.u;
    if (count >= 8) {
        count = 8;
    }
    if (count >= 0) {
        do {
            created = func_8003FD64(0x202, D_80083498);
            if (created != NULL) {
                ((S_81934928_2 *)created)->unk_10 = D_8002445C;
                func_8004491C(created, D_80024740);
                part = (u8 *)created + 0x20;

                arithmetic = rand();
                random = arithmetic;
                base = ((S_81934928_0 *)self)->unk_10.u;
                arithmetic >>= 9;
                if (random < 0) {
                    arithmetic = (random + 0x1FF) >> 9;
                }
                value = base + (random - (arithmetic << 9)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)part)->unk_0C = value;
                ((S_81934928_3 *)part)->unk_1E = value;

                arithmetic = rand();
                random = arithmetic;
                base = ((S_81934928_0 *)self)->unk_12.u;
                arithmetic >>= 9;
                if (random < 0) {
                    arithmetic = (random + 0x1FF) >> 9;
                }
                value = base + (random - (arithmetic << 9)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)part)->unk_0E = value;
                ((S_81934928_3 *)part)->unk_22 = value;

                value = ((S_81934928_0 *)self)->unk_14 - 0x100;
                ((S_81934928_3 *)part)->unk_10 = value;
                ((S_81934928_3 *)part)->unk_26 = value;
                ((S_81934928_2 *)created)->unk_20 = self;
            }
            count--;
        } while (count >= 0);
    }

    if (((S_81934928_0 *)self)->unk_0C.u == 0x1E) {
        search = D_800814A8;
        if (search != NULL) {
            u8 *search_page;
            register u8 *pinned_table ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 call0;
            s32 call1;
            void *call2;
            void *call3;
            search_copy = search;
            ASM_KEEP_NV(search_copy);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            search_page = D_80082E80 - 0x2E80;
#else
            search_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(search_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            pinned_table = search_page + 0x2E80;
            ASM_KEEP(search_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            call2 = search_copy;
            call0 = pinned_table[0x24];
            call1 = pinned_table[0x25];
            call3 = search;
            found = func_800A3F28(call0, call1, call2, call3);
            if (found != NULL) {
                if ((((S_81934928_4 *)found)->unk_1C & 0x2000) == 0) {
                    func_8009CE1C(found, 0x20, ((S_81934928_0 *)self)->unk_09, 0xA,
                                  ((S_81934928_5 *)owner)->unk_2A, owner, 2);
                }
                func_80024004(found);
                tail_a2 = search_copy;
                ASM_TAILSLOT_PIN(tail_a2);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
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
        u16 clear_value;
        value = ((S_81934928_0 *)self)->unk_0E.s;
        clear_value = ((S_81934928_0 *)self)->unk_0E.u;
        if ((value & 0x8000) != 0) {
            value = clear_value & 0x7FFF;
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
