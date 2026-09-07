#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct Copy48 {
    u32 words[12];
} Copy48;

typedef struct ItemInfo {
    u8 pad00[0x12];
    u8 type;
    u8 pad13;
} ItemInfo;

extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_801708B8(void *, void *, void *);

extern s32 D_80045340;
extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D58D8[];
extern s8 D_800DCECC[];
extern u8 D_800E23E0[];
extern u8 D_800E2410[];
extern void *D_80170868[];
extern u8 D_80171A80[];

void func_80173A60(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&L_kind1, &&L_kind2, &&L_kind3, &&L_kind4,
        &&L_kind5, &&L_kind6, &&L_kind7
    };
    register s32 special ASM_REG("$17");
    u8 *selector;

    special = 0;
    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            u32 dispatch;

            dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
            if (dispatch >= 7) {
                goto L_kind4;
            }
            (void)kind_keep;
            goto *D_80170868[dispatch];

L_kind7:
            special = 1;
            goto L_kind3;
L_kind6:
            special = 1;
            goto L_kind2;
L_kind5:
            special = 1;
            goto L_kind1;
        }

        switch (FIELD(arg3, u16, 0x46) & 0x3FFF) {
        case 3:
L_kind3:
            selector = (u8 *)arg3 + 0xE;
            break;
        case 2:
L_kind2:
            selector = (u8 *)arg3 + 0xB;
            break;
        case 1:
L_kind1:
            selector = (u8 *)arg3 + 8;
            break;
        default:
L_kind4:
            selector = 0;
            break;
        }

        if (*selector != 0) {
            register s32 special_test ASM_REG("$2");
            void *active;

            FIELD(arg0, u16, 0x98) &= 0xFF7F;
            ASM_KEEP(special);
            special_test = special;
            ASM_KEEP(special_test);
            if (special_test != 0) {
                active = D_800814A8;
                FIELD(arg3, void *, 0x60) = active;
                goto L_copy_linked;
            } else if (D_8006DE24[*selector].type == 2) {
                active = FIELD(arg3, void *, 0x60);
                if (active != 0) {
                    register u8 *linked ASM_REG("$3");

L_copy_linked:
                    linked = FIELD(active, u8 *, -0x14);
                    ASM_KEEP(linked);
                    FIELD(arg3, u8, 0x72) = linked[0x24];
                    FIELD(arg3, u8, 0x73) = linked[0x25];
                }
            } else {
                s32 x;
                s32 y;

                active = func_800A05A4(arg3,
                                       FIELD(arg2, u8, 0x24),
                                       FIELD(arg2, u8, 0x25),
                                       FIELD(arg3, s16, 0x2A), 0x10);
                FIELD(arg3, void * volatile, 0x60) = active;
                ASM_USE(active);
                x = FIELD(arg3, s8, 0x72);
                y = FIELD(arg3, s8, 0x73);
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                FIELD(arg3, u8, 0x72) = x;
                FIELD(arg3, u8, 0x73) = y;
            }

            if (func_800A94A0(arg3, selector, special,
                              (u16 *)((u8 *)arg0 + 0x98)) == 0) {
                return;
            }
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B)++;
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6)--;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg0, void *, 0x8C) = D_80171A80;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            FIELD(arg2, u16, 0x14) |= 0x0800;
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, u8, 0x9B)++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        {
            u16 timer;

            timer = FIELD(arg0, u16, 0x96) + 1;
            FIELD(arg0, u16, 0x96) = timer;
            if ((s16)timer == 3) {
                u8 *object;

                object = func_8003FD64(0x112, D_80083498);
                if (object != 0) {
                    u8 *state;
                    u8 *copy;
                    u8 *direction;
                    u8 *target;
                    register u8 *animation ASM_REG("$5");
                    u8 *animation_entry;
                    s8 *offsets;
                    register s32 index ASM_REG("$2");

                    state = object + 0x20;
                    FIELD(state, u16, 0x96) = 0x10;
                    FIELD(object, void *, 0x10) = D_800D58D8;
                    FIELD(state, void *, 0xAC) = arg1;
                    FIELD(state, u16, 0x94) = FIELD(arg3, u16, 0x2A);
                    copy = FIELD(object, u8 *, 0x0C);
                    *(Copy48 *)copy = *(Copy48 *)arg2;
                    FIELD(copy, u16, 0x1E) = 0x1000;
                    FIELD(copy, u16, 0x1C) = 0x1000;
                    FIELD(copy, u8, 0x0E) = 0x80;
                    FIELD(copy, u8, 0x0D) = 0x80;
                    FIELD(copy, u8, 0x0C) = 0x80;
                    func_8004491C(object, &D_80045340);

                    animation = D_800E2410;
                    ASM_KEEP(animation);
                    FIELD(copy, void *, 0x2C) = animation;
                    direction = D_80083160;
                    index = ((FIELD(direction, s16, 0xC8) +
                              FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
                    animation_entry = (u8 *)((u32)index + (u32)animation);
                    func_80047784(copy, *animation_entry, 0);
                    FIELD(copy, u16, 0x14) &= 0xFFF3;

                    index = ((FIELD(direction, s16, 0xC8) +
                              FIELD(arg0, s16, 0x2A) + 0x100) >> 9) & 7;
                    ASM_KEEP(index);
                    offsets = D_800DCECC;
                    FIELD(copy, s16, 6) = -(offsets[index] * 4);
                    FIELD(state, u16, 0x94) =
                        (FIELD(arg0, u16, 0x2A) >> 9) & 7;
                    FIELD(state, u16, 0x2A) = FIELD(arg0, u16, 0x2A);

                    target = FIELD(object, u8 *, 8);
                    FIELD(target, u16, 2) = FIELD(arg1, u16, 2);
                    FIELD(target, u16, 6) = FIELD(arg1, u16, 6);
                    FIELD(target, u16, 0xA) = FIELD(arg1, u16, 0xA);
                }
            }

            if (FIELD(arg0, s16, 0x96) == 0x10) {
                u8 *animation;
                s32 index;

                animation = D_800E23E0;
                FIELD(arg2, void *, 0x2C) = animation;
                index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
                func_80047784(arg2, animation[index], 3);
                if (FIELD(arg0, u8, 0xB0) == 0) {
                    func_801708B8(arg0, arg1, arg2);
                }
            }

            if (FIELD(arg0, s16, 0x96) == 0x13 ||
                (FIELD(arg2, u16, 0x14) & 0xE000)) {
                FIELD(arg0, u16, 0x98) |= 0x80;
                func_800A56E0(0x81B);
            }

            if (FIELD(arg0, s16, 0x96) < 0x19 &&
                !(FIELD(arg2, u16, 0x14) & 0xE000)) {
                return;
            }
            FIELD(arg0, u8, 0x9B)++;
            return;
        }

    case 3:
        {
            u8 *global;

            global = D_80083460;
            if (FIELD(global, volatile s32, 0x0C) != 0) {
                return;
            }
            FIELD(arg0, u16, 0x96) = 0;
            if (FIELD(global, volatile s32, 0x0C) != 0) {
                return;
            }
            FIELD(global, u16, 0x0A)--;
            FIELD(arg0, void *, 0x8C) = D_80171A80;
            func_800A4ACC(arg3);
            FIELD(arg3, u8, 0x73) = 0;
            FIELD(arg3, u8, 0x72) = 0;
            FIELD(arg3, u8, 0x6D)--;
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
            func_800A56E0(0xB4);
            return;
        }
    }
}

/* MECHANISM: The four long-lived arguments and scoped temporaries reproduce the 0x40 frame
   and s4/s7/s6/s2 plus s1/s5/s3/s0 save contract; the shared linked-copy label restores both CFG edges.
   ASM_USE orders the returned-pointer store before signed-byte loads, while a v0-pinned index and
   named integer address sum reproduce the two table-lookup register roles and final addu polarity. */
