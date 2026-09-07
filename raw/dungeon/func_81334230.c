#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern s16 func_800A0134();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_8016B954();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

void func_8016B230(u8 *in0, void *arg1, u8 *in2, u8 *in3) {
    register u8 *arg0 ASM_REG("$21") = in0;
    register u8 *arg2 ASM_REG("$20") = in2;
    register u8 *arg3 ASM_REG("$18") = in3;
    register s32 enabled ASM_REG("$22");
    register s32 i ASM_REG("$19");
    register s16 *delta;
    register u8 *x_table;
    u8 *state;
    u8 *loop_state;
    u32 flags;
    u32 attr;
    s32 ret;
    register s32 direction_index ASM_REG("$4");
    register s32 loop_test ASM_REG("$2");
    s32 step;
    s32 base_wide;
    s16 move_angle;
    u8 call_x;
    u8 call_y;
    void *found;
    u8 *object;

    state = (u8 *)&D_80083460;
    do { flags = FIELD(state, u16, 2); } while (0);
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    enabled = 0;

    if ((flags & 0x4000) || (FIELD(arg3, s8, 0x71) >= 0)) {
        if ((FIELD(arg3, u8, 0x12) >= 2) ||
            ((func_8016B954(arg0, arg1, arg2, arg3) << 16) == 0)) {
            func_800A9A0C(arg3);
            goto end;
        }
        if (FIELD(state, void *, 0xC) != arg3) {
            goto end;
        }
        FIELD(arg3, u16, 0x46) = 0xC008;
        goto end;
    }
    if (!(flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
    attr = FIELD(arg3, u32, 0x1C);
    if (attr & 0x410) {
        if (attr & 0x400) {
            found = func_800A02AC(arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
            if (found != NULL) {
                object = FIELD(found, u8 *, -0x14);
                FIELD(arg3, u16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    FIELD(object, u8, 0x24), FIELD(object, u8, 0x25), arg0 + 0x98);
                FIELD(arg3, u8, 0x71) &= 0x7F;
                goto end;
            }
            {
                register s32 object_status ASM_REG("$2");

                object_status = FIELD(arg3, s32, 0x14);
                if (object_status >= 0) {
                    FIELD(arg3, s32, 0x14) = object_status | 0x80000000;
                    ret = func_800A6D30();
                    FIELD(arg3, u16, 0x2A) += (ret & 7) << 9;
                }
            }
            goto init_loop;
        }
        found = func_800A04F0(arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                              FIELD(arg3, s16, 0x2A));
        i = 0;
        if (found == NULL) {
            goto setup_loop;
        }
        goto clear_history;
    }

    if (FIELD(arg0, u8, 0xAF)) {
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            i = 0;
            goto setup_loop;
        }
        if (attr & 0x20000) {
            s32 direction;
            s16 target_x;
            s32 target_y;
            s16 new_angle;
            register u8 *target ASM_REG("$5");

            target = (u8 *)&D_80082EA4 - 0x24;
            direction = (FIELD(arg3, u8, 0x45) +
                         ((s32)(FIELD(D_800814A8, u16, 0x2A) << 16) >> 25)) & 7;
            target_x = FIELD(target, u8, 0x24) +
                       ((u16 *)&D_8006CCD8)[direction];
            target_y = FIELD(target, u8, 0x25) +
                       ((u16 *)&D_8006CCE8)[direction];
            if ((FIELD(arg2, u8, 0x24) == (u16)target_x) &&
                (FIELD(arg2, u8, 0x25) == (u16)target_y)) {
                goto clear_history;
            }
            new_angle = func_800A0818(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                                      target_x, (s16)target_y, arg0 + 0x98);
            FIELD(arg3, u16, 0x2A) = new_angle;
            if ((func_8009A66C(new_angle, arg2, arg3, 0x20) << 16) <= 0) {
                u8 *retry_target = D_80082E80;

                FIELD(arg3, u16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    FIELD(retry_target, u8, 0x24), FIELD(retry_target, u8, 0x25),
                    arg0 + 0x98);
            }
            {
                u8 *check_target = D_80082E80;

                if ((func_8009FD7C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                                   FIELD(check_target, u8, 0x24),
                                   FIELD(check_target, u8, 0x25)) << 16) != 0) {
                    enabled = 1;
                }
            }
            i = 0;
            goto setup_loop;
        }
        goto use_target;
    }

    {
        register s32 kind ASM_REG("$4");

        kind = FIELD(arg2, s8, 0x26);
        ASM_KEEP(kind);
        if (kind >= 0) {
            u8 *kind_table = (u8 *)D_800E2970;

            if (FIELD(kind_table + kind * 0x14, u16, 0xC) & 2) {
                goto use_target;
            }
        }
    }
        i = 0;
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            goto setup_loop;
        }
        found = func_800A04F0(arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                              FIELD(arg3, s16, 0x2A));
        if ((found != NULL) && (FIELD(found, u32, 0x1C) & 0x2000) &&
            (func_800A0134(found, arg3) < 0x81) &&
            ((func_8009A540(((s32)(FIELD(arg3, u16, 0x2A) << 16) >> 25) & 0xFFFF,
                            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                            (s16)(FIELD(arg3, u16, 0x88) - 0x20)) << 16) != 0)) {
            goto clear_history;
        }
        if (FIELD(arg3, u32, 0x1C) & 0x20000) {
            u8 *target = D_80082E80;
            FIELD(arg3, u16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(target, u8, 0x24), FIELD(target, u8, 0x25), arg0 + 0x98);
            if ((func_8009FD7C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                               FIELD(target, u8, 0x24), FIELD(target, u8, 0x25)) << 16) != 0) {
                if (func_800A0134(D_800814A8, arg3) < 0x81) {
                    ret = func_8009A540(
                        ((s32)(FIELD(arg3, u16, 0x2A) << 16) >> 25) & 0xFFFF,
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        (s16)(FIELD(arg3, u16, 0x88) - 0x20));
                    i = 0;
                    if ((ret << 16) == 0) {
                        goto setup_loop;
                    }
                    goto clear_history;
                }
                i = 0;
                goto setup_loop;
            }
            goto init_loop;
        }

use_target:
    func_800A0E6C(arg2, FIELD(arg0, s8, 0x9C), arg3, arg0 + 0x98);
init_loop:
    i = 0;
setup_loop:
    x_table = (u8 *)&D_8006CCD8;
    delta = &D_8006CD00;
    ASM_KEEP(i);
    ASM_KEEP(x_table);
    ASM_KEEP(delta);
    ASM_KEEP(enabled);

loop:
    base_wide = (s32)FIELD(arg3, s16, 0x2A);
    if (FIELD(arg0, u16, 0x98) & 2) {
        {
            s32 delta_wide = (s32)*delta;

            move_angle = (s16)(base_wide - delta_wide);
        }
    } else {
        {
            s32 delta_wide = (s32)*delta;

            move_angle = (s16)(base_wide + delta_wide);
        }
    }
    ASM_KEEP(base_wide);
    if ((func_8009A66C(move_angle, arg2, arg3, 0x20) << 16) > 0) {
        if (i >= 3) {
            register s32 enabled_test ASM_REG("$2") = enabled;

            ASM_KEEP(enabled_test);
            if (enabled_test) {
                goto clear_history;
            }
        }
        FIELD(arg3, u16, 0x2A) = move_angle;
        FIELD(arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x74) =
            FIELD(arg2, u8, 0x24);
        FIELD(arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x7C) =
            FIELD(arg2, u8, 0x25);
        FIELD(arg3, u8, 0x71)++;
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                      (FIELD(arg3, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        direction_index = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
        FIELD(arg2, u8, 0x24) +=
            *((u8 *)((u32)direction_index + (u32)x_table));
        FIELD(arg2, u8, 0x25) += *((u8 *)&D_8006CCE8 + direction_index);
        call_x = FIELD(arg2, u8, 0x24);
        call_y = *(volatile u8 *)((u8 *)arg2 + 0x25);
        step = 0x3000;
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            step = 0x300;
        }
        func_8009A21C(call_x, call_y, step);
        goto after_loop;
    }

    if (i == 0) {
        if ((FIELD(&D_80082EA4, u16, 0) != FIELD(arg2, u16, 0x24)) &&
            ((s16)func_8009A180(arg3, FIELD(D_800814A8, s32, 0x58) + 0x20) != 0)) {
            goto end;
        }
    }
    i++;
    delta++;
    if (i < 8) {
        goto loop;
    }

after_loop:
    loop_test = i < 8;
    ASM_KEEP(loop_test);
    if (!loop_test) {
        FIELD(arg3, u8, 0x71) &= 0x7F;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A9A0C(arg3);
        goto end;
    }
    loop_state = (u8 *)&D_80083460;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    FIELD(arg0, u8, 0x9C) = FIELD(arg2, u8, 0x26);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(loop_state, u16, 8)++;
    if (FIELD(arg3, s8, 0x6D) != 0) {
        goto update_height;
    }

clear_history:
    FIELD(arg3, u8, 0x71) &= 0x7F;
    goto end;

update_height:
    i = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
                      (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                      (s16)(FIELD(arg3, u16, 0x88) - 0x20));
    if (i < 0x200) {
        FIELD(arg3, u16, 0x88) = i;
    }
    goto end;

end:
    ASM_KEEP(arg0);
    return;
}
