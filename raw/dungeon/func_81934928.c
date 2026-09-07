#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register void *self ASM_REG("$18") = arg0;
    register void *dst ASM_REG("$7");
    register void *owner ASM_REG("$20");
    register void *search ASM_REG("$16");
    register void *found ASM_REG("$16");
    register void *search_copy ASM_REG("$19");
    register void *tail_a2 ASM_REG("$6");
    register void *created ASM_REG("$17");
    register s32 arithmetic ASM_REG("$2");
    s16 state;
    s32 count;
    s32 base;
    s32 random;
    s32 value;
    s16 countdown;
    void *part;

    state = FIELD(self, s16, 0xA);
    owner = FIELD(self, void *, 0);
    dst = arg1;
    if (state != 1) {
        if (state < 2) {
            if (state != 0) {
                func_80024434();
            }
        } else {
            ASM_SCHED_BARRIER();
            if (state == 0xFF) {
                goto state_ff;
            }
            func_80024434();
        }
        ASM_KEEP(dst);
        if ((FIELD(FIELD(self, void *, 4), u16, 0) & 0x80) == 0) {
            goto done;
        }
        {
            register u8 *copy_page ASM_REG("$3");
            register Copy24 *copy_src ASM_REG("$6");
            register s32 copy0 ASM_REG("$2");
            register s32 copy1 ASM_REG("$4");
            register s32 copy2 ASM_REG("$5");
#ifdef NON_MATCHING
            copy_page = (u8 *)&D_80083780 - 0x3780;
#else
            copy_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(copy_page);
            copy_src = (Copy24 *)(copy_page + 0x3780);
            ASM_KEEP(copy_page);
            ASM_KEEP(copy_src);
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
            ASM_SCHED_BARRIER();
            copy_page += 0x3780;
            FIELD(self, u16, 0x10) = FIELD(copy_page, volatile u16, 2);
            FIELD(self, u16, 0x12) = FIELD(copy_page, volatile u16, 6);
            value = FIELD(copy_page, volatile u16, 0xA);
        }
        FIELD(self, u16, 0xC) = 0x3C;
        FIELD(self, u16, 0xA)++;
        FIELD(self, u16, 0x14) = value;
        func_800A56E0(0x300);
    }

main_state:
    count = 0x3C - FIELD(self, s16, 0xC);
    if (count >= 8) {
        count = 8;
    }
    if (count >= 0) {
        do {
            created = func_8003FD64(0x202, D_80083498);
            if (created != NULL) {
                FIELD(created, void *, 0x10) = D_8002445C;
                func_8004491C(created, D_80024740);
                part = (u8 *)created + 0x20;

                arithmetic = rand();
                random = arithmetic;
                base = FIELD(self, s16, 0x10);
                arithmetic >>= 9;
                if (random < 0) {
                    arithmetic = (random + 0x1FF) >> 9;
                }
                value = base + (random - (arithmetic << 9)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                FIELD(part, s16, 0xC) = value;
                FIELD(part, s16, 0x1E) = value;

                arithmetic = rand();
                random = arithmetic;
                base = FIELD(self, s16, 0x12);
                arithmetic >>= 9;
                if (random < 0) {
                    arithmetic = (random + 0x1FF) >> 9;
                }
                value = base + (random - (arithmetic << 9)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                FIELD(part, s16, 0xE) = value;
                FIELD(part, s16, 0x22) = value;

                value = FIELD(self, u16, 0x14) - 0x100;
                FIELD(part, s16, 0x10) = value;
                FIELD(part, s16, 0x26) = value;
                FIELD(created, void *, 0x20) = self;
            }
            count--;
        } while (count >= 0);
    }

    if (FIELD(self, s16, 0xC) == 0x1E) {
        search = D_800814A8;
        if (search != NULL) {
            register u8 *search_page ASM_REG("$2");
            register u8 *pinned_table ASM_REG("$17");
            register s32 call0 ASM_REG("$4");
            register s32 call1 ASM_REG("$5");
            register void *call2 ASM_REG("$6");
            register void *call3 ASM_REG("$7");
            search_copy = search;
            ASM_KEEP_NV(search);
            ASM_KEEP_NV(search_copy);
            ASM_SCHED_BARRIER();
#ifdef NON_MATCHING
            search_page = D_80082E80 - 0x2E80;
#else
            search_page = (u8 *)0x80080000;
#endif
            ASM_KEEP(search_page);
            pinned_table = search_page + 0x2E80;
            ASM_KEEP(search_page);
            ASM_KEEP(pinned_table);
            call2 = search_copy;
            ASM_KEEP(call2);
            call0 = pinned_table[0x24];
            call1 = pinned_table[0x25];
            ASM_SCHED_BARRIER();
            call3 = search;
            found = func_800A3F28(call0, call1, call2, call3);
            if (found != NULL) {
                if ((FIELD(found, s32, 0x1C) & 0x2000) == 0) {
                    func_8009CE1C(found, 0x20, FIELD(self, u8, 9), 0xA,
                                  FIELD(owner, s16, 0x2A), owner, 2);
                }
                func_80024004(found);
                tail_a2 = search_copy;
                ASM_TAILSLOT_PIN(tail_a2);
                func_80024344();
            }
        }
    }

    countdown = FIELD(self, u16, 0xC) - 1;
    FIELD(self, u16, 0xC) = countdown;
    if (countdown > 0) {
        goto done;
    }
    FIELD(self, u16, 0xC) = 8;
    FIELD(self, u16, 0xA) = 0xFF;
    func_80024434();

state_ff:
    countdown = FIELD(self, u16, 0xC) - 1;
    FIELD(self, u16, 0xC) = countdown;
    if (countdown > 0) {
        goto done;
    }
    {
        register u16 clear_value ASM_REG("$3");
        value = FIELD(self, s16, 0xE);
        clear_value = FIELD(self, u16, 0xE);
        if ((value & 0x8000) != 0) {
            value = clear_value & 0x7FFF;
            FIELD(self, u16, 0xE) = value;
            func_80024434();
        }
        ASM_SCHED_BARRIER();
    }
    D_8008346C = 0;
    FIELD(self, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
