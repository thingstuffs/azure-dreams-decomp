#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171434(void) __attribute__((noreturn));
extern void func_8017143C(void) __attribute__((noreturn));
extern void func_80171704(void) __attribute__((noreturn));
extern void func_801718B4(void) __attribute__((noreturn));
extern void func_801718EC(void) __attribute__((noreturn));
extern void func_80171910(void);
extern void func_80171B68(void *, void *, void *, void *);
extern s32 func_80172314(void *, void *, void *, void *);
extern void func_80172514(void *, void *, void *, void *);
extern s32 func_80172658(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

extern u8 D_80045340[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern void *D_800814A8[3];
extern u8 D_80082E80[];
extern s8 D_80082EA4[16];
extern s16 D_80083228[5];
extern u16 D_80083460[];
extern u16 D_80083462[5];
extern u8 D_80083498[];
extern u8 D_800DEA68[];
extern DungeonRecord D_800E2970[];
extern u8 D_80175174[];
extern u8 D_80175258[];
extern u8 D_80175260[];
extern u8 D_80175290[];
extern u8 D_80175298[];
extern u8 D_801752A0[];
extern void *D_80170808[];
extern void *D_80170820[];

void func_80170F6C(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    static void *const sw_keep[] = {
        &&sw_case123, &&sw_generic, &&sw_case89,
        &&sw_case567, &&sw_case12
    };
    static void *const sw1_keep[] = {
        &&sw1_case0, &&sw1_case1, &&sw1_case2,
        &&sw1_case3, &&sw1_case4
    };
    u16 initial_flags = D_80083462[0];
    s32 scratch;
    s8 result;
    register void *arg0 ASM_REG("$18") = in_arg0;
    register void *arg1 ASM_REG("$20") = in_arg1;
    register void *arg2 ASM_REG("$19") = in_arg2;
    register void *arg3 ASM_REG("$17") = in_arg3;

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171910();
        func_801718EC();
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        {
            register void *current ASM_REG("$3") =
                FIELD(arg2, void *, 0x2C);
            register u8 *page ASM_REG("$2") = (u8 *)0x80170000;
            register void *table ASM_REG("$5");
            ASM_KEEP(current);
            ASM_KEEP(page);
            table = page + 0x5298;
            ASM_TAILSLOT_PIN(table);
            func_801718B4();
        }
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80175298) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_801718EC();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175298) != 0) {
            return;
        }
    }

    if (!(D_80083462[0] & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801718EC();
        }

        {
            register u32 state ASM_REG("$16");
            u32 current_state = FIELD(arg0, u8, 0x9A);
            ASM_SCHED_BARRIER();
            state = 0xE;
            ASM_KEEP(state);
            if (current_state != state) {
                if (FIELD(arg2, void *, 0x2C) != D_80175258) {
                    FIELD(arg2, void *, 0x2C) = D_80175258;
                    func_80047784(arg2,
                        D_80175258[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                FIELD(arg0, u8, 0x9A) = state;
            }
        }

        if (FIELD(arg3, u32, 0x14) & 0x20000) {
            {
                s32 switch_index = FIELD(arg0, s16, 0xA8);
                if ((u32)switch_index >= 5) {
                    goto epilogue;
                }
                (void)sw1_keep;
                {
                    register void **switch_table ASM_REG("$2") = D_80170808;
                    ASM_KEEP(switch_table);
                    goto *switch_table[switch_index];
                }
            }
sw1_case0:
                if (FIELD(arg2, void *, 0x2C) != D_801752A0) {
                    D_80083460[5]++;
                    FIELD(arg0, u16, 0xAA) = FIELD(arg3, u16, 0x2A);
                    FIELD(arg3, s16, 0x2A) =
                        (FIELD(arg3, u16, 0x6A) + 0x800) & 0xFFF;
                    FIELD(arg2, u16, 0x14) &= 0x9FFF;
                    FIELD(arg0, u16, 0xA6) = 300;
                }
                {
                    register u32 tail_state ASM_REG("$2") =
                        FIELD(arg0, u16, 0xA8);
                    tail_state += 1;
                    ASM_TAILSLOT_PIN_TIED(tail_state);
                    func_8017143C();
                }

sw1_case1: {
                u16 timer = FIELD(arg0, u16, 0xA6) - 1;

                FIELD(arg0, u16, 0xA6) = timer;
                if (((s32)timer << 16) <= 0 ||
                    FIELD(arg3, s16, 0x64) != 0) {
                    D_80083460[5]--;
                    FIELD(arg1, s32, 0x10) = 0;
                    FIELD(arg1, s32, 0x0C) = 0;
                    func_800A2B04(arg1,
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
                    FIELD(arg3, u32, 0x14) &= ~0x20000;
                    FIELD(arg0, u16, 0xA8) = 0;
                    func_801718EC();
                }
                if (FIELD(arg3, u32, 0x14) & 0x1000000) {
                    FIELD(arg0, u16, 0xA8)++;
                    FIELD(arg2, void *, 0x2C) = D_801752A0;
                    func_80047784(arg2,
                        D_801752A0[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                    FIELD(arg0, u16, 0xA6) = 0;
                    func_801718EC();
                }
                goto epilogue;
            }

sw1_case2: {
                s32 scale;
                void *object;
                register void *part ASM_REG("$4");
                register void *payload ASM_REG("$3");
                register u32 color ASM_REG("$5");
                u32 payload_word;
                u32 texture_word;

                FIELD(arg1, s32, 0x0C) =
                    D_8006CCD8[((s32)(FIELD(arg3, u16, 0x6A) << 16)) >> 25] << 16;
                FIELD(arg1, s32, 0x10) =
                    D_8006CCE8[((s32)(FIELD(arg3, u16, 0x6A) << 16)) >> 25] << 16;
                scale = func_800644B8((s16)FIELD(arg0, u16, 0xA6) << 8);
                FIELD(arg1, s32, 0x0C) = FIELD(arg1, s32, 0x0C) +
                    (FIELD(arg1, s32, 0x0C) * scale >> 9);
                scale = func_800644B8((s16)FIELD(arg0, u16, 0xA6) << 8);
                FIELD(arg1, s32, 0x10) = FIELD(arg1, s32, 0x10) +
                    (FIELD(arg1, s32, 0x10) * scale >> 9);

                object = func_8003FD64(0x312, D_80083498);
                if (object != 0) {
                    func_8004491C(object, D_80045340);
                    payload = FIELD(object, void *, 8);
                    FIELD(object, void *, 0x10) = D_80175174;
                    part = FIELD(object, void *, 0x0C);
                    FIELD(payload, s32, 0) = FIELD(arg1, s32, 0);
                    payload = FIELD(object, void *, 8);
                    FIELD(payload, s32, 4) = FIELD(arg1, s32, 4);
                    payload = FIELD(object, void *, 8);
                    ASM_SCHED_BARRIER();
                    payload_word = FIELD(arg1, u32, 8);
                    ASM_KEEP(payload_word);
                    color = 0x00800000;
                    ASM_KEEP(color);
                    FIELD(payload, u32, 8) = payload_word;
                    FIELD(part, u16, 0x1E) = 0x1000;
                    FIELD(part, u16, 0x1C) = 0x1000;
                    FIELD(part, u16, 0x10) = 0;
                    FIELD(part, void *, 0) = D_800DEA68;
                    FIELD(part, u16, 0x14) |= 0xC;
                    ASM_SCHED_BARRIER();
                    texture_word = FIELD(D_800DEA68, u32, 4);
                    color |= 0x8080;
                    FIELD(part, u8, 4) = 0;
                    FIELD(part, u8, 5) = 0;
                    FIELD(part, u32, 0x0C) = color;
                    FIELD(part, u32, 8) = texture_word;
                    FIELD(object, u8, 0xBA) = 0;
                }

                {
                    u16 old_timer = FIELD(arg0, u16, 0xA6);
                    FIELD(arg0, u16, 0xA6) = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                    FIELD(arg2, u16, 0x14) &= 0xF7FF;
                    ASM_SCHED_BARRIER();
                    FIELD(arg1, s32, 0x10) = 0;
                    FIELD(arg1, s32, 0x0C) = 0;
                    {
                        register u32 tail_value ASM_REG("$2") =
                            FIELD(arg0, u16, 0xA8);
                        register u32 tail_code ASM_REG("$3") = 4;
                        ASM_KEEP(tail_value);
                        ASM_TAILSLOT_PIN_TIED(tail_code);
                        func_80171434();
                    }
                }
                }
                goto epilogue;
            }

sw1_case3: {
                u16 timer = FIELD(arg0, u16, 0xA6) - 1;

                FIELD(arg0, u16, 0xA6) = timer;
                if (((s32)timer << 16) <= 0) {
                    FIELD(arg2, u16, 0x14) &= 0xF7FF;
                    FIELD(arg1, s32, 0x10) = 0;
                    FIELD(arg1, s32, 0x0C) = 0;
                    FIELD(arg0, u16, 0xA6) = 3;
                    FIELD(arg0, u16, 0xA8)++;
                    func_801718EC();
                }
                goto epilogue;
            }

sw1_case4: {
                s32 x;
                s32 y;
                s32 coord;
                s32 delta;
                u16 timer;

                coord = FIELD(arg2, u8, 0x24) << 6;
                delta = FIELD(arg1, s16, 2) - 0x20;
                ASM_SCHED_BARRIER();
                x = coord - delta;
                FIELD(arg1, s32, 0x0C) = (s32)((u32)x << 15) >> 1;
                coord = FIELD(arg2, u8, 0x25) << 6;
                delta = FIELD(arg1, s16, 6) - 0x20;
                ASM_SCHED_BARRIER();
                y = coord - delta;
                FIELD(arg1, s32, 0x10) = (s32)((u32)y << 15) >> 1;
                timer = FIELD(arg0, u16, 0xA6) - 1;
                FIELD(arg0, u16, 0xA6) = timer;
                if (((s32)timer << 16) <= 0) {
                    D_80083460[5]--;
                    FIELD(arg1, s32, 0x10) = 0;
                    FIELD(arg1, s32, 0x0C) = 0;
                    func_800A2B04(arg1,
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
                    FIELD(arg3, u32, 0x14) &= ~0x20000;
                    FIELD(arg3, s16, 0x2A) = FIELD(arg0, u16, 0xAA);
                    FIELD(arg2, void *, 0x2C) = D_80175258;
                    func_80047784(arg2,
                        D_80175258[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                    FIELD(arg0, u16, 0xA8) = 0;
                    func_801718EC();
                }
                goto epilogue;
            }
        } else {
            FIELD(arg0, u16, 0x98) &= 0xFFF3;
            if (FIELD(arg3, s16, 0x64) == 0 ||
                func_800AA6B4(arg0, arg1, arg2, D_80175260) == 0) {
                if (FIELD(arg3, u32, 0x1C) & 0x80000) {
                    func_800AA888(arg0, arg1, arg2, arg3);
                    func_80174250(arg0, arg1, arg2, arg3);
                    func_801718EC();
                }
                if ((func_800A1C58(arg3) << 16) != 0) {
                    func_800AAB10(arg0, arg1, arg2, arg3);
                }
            } else {
                return;
            }
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, s8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto sw_case12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4[0]) {
            goto sw_generic;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if ((D_80083462[0] & 0x2000) &&
                ((func_8009A180(arg3,
                    (u8 *)FIELD(D_800814A8[0], void *, 0x58) + 0x20) << 16) != 0)) {
                return;
            }
            if ((func_80172658(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
                goto sw_generic;
            }
        }

        {
            u32 swi = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

            if (swi >= 12) {
                goto sw_generic;
            }
            (void)sw_keep;
            {
                register void **switch_table ASM_REG("$2") = D_80170820;
                ASM_KEEP(switch_table);
                goto *switch_table[swi];
            }
        }

sw_case89:
        if ((FIELD(arg3, u16, 0x46) & 0x3FFF) == 9) {
            register u32 case_flags ASM_REG("$2");

            ASM_SCHED_BARRIER();
            case_flags = FIELD(arg0, u16, 0x98);
            case_flags |= 0x8000;
            ASM_TAILSLOT_PIN_TIED(case_flags);
            func_80171704();
        }
        FIELD(arg0, u16, 0x98) &= 0x7FFF;
        ASM_SCHED_BARRIER();
        if ((func_80172314(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172514(arg0, arg1, arg2, arg3);
        func_801718EC();

sw_case567:
        {
            s16 next_position;
            register void *status_object ASM_REG("$3");
            u8 *map_base = D_80082E80;

            next_position = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(map_base, u8, 0x24), FIELD(map_base, u8, 0x25),
            &scratch);
            status_object = D_800814A8[0];
            FIELD(arg3, s16, 0x2A) = next_position;
            if (FIELD(status_object, u8, 0x9A) == 0x11) {
                goto sw_case123;
            }
        }
sw_case12:
        func_800A9A0C(arg3);
        func_801718EC();

sw_case123:
        func_800AAF00(arg0, arg1, arg2, D_80175290, func_80170F6C);
        func_801718EC();

sw_generic:
        func_80171B68(arg0, arg1, arg2, arg3);
        func_801718EC();
    }

    {
        register u32 final_flags ASM_REG("$5") =
            FIELD(arg3, u32, 0x1C);
        if (!(final_flags & 0x2000)) {
            if ((result < 0) || !(D_800E2970[result].flags & 2)) {
                register u32 final_mask ASM_REG("$2") =
                    final_flags & 0x430;
                ASM_KEEP(final_mask);
                if (!final_mask) {
                u8 *map_base = D_80082E80;

                if ((func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(map_base, u8, 0x24), FIELD(map_base, u8, 0x25)) << 16) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(map_base, u8, 0x24), FIELD(map_base, u8, 0x25),
                        &scratch);
                }
            }
        }
    }
    }

    if (!(D_80083462[0] & 0x2000) &&
        !(FIELD(arg2, u16, 0x14) & 0x40)) {
        register void *post_current ASM_REG("$3") =
            FIELD(arg2, void *, 0x2C);
        register u8 *post_page ASM_REG("$2") = (u8 *)0x80170000;
        register u8 *post_table ASM_REG("$5");
        ASM_KEEP(post_page);
        post_table = post_page + 0x5258;
        if (post_current != post_table) {
            u32 post_index;

            FIELD(arg2, void *, 0x2C) = post_table;
            post_index = ((D_80083228[0] +
                FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2,
                *(u8 *)((unsigned long)post_index +
                    (unsigned long)post_table),
                0);
        }
    }

epilogue:
    return;
}
