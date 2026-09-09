#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80099F04();                         /* extern */
s32 func_8009C12C();    /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B341C();        /* extern */
M2C_UNK func_800B3D10();          /* extern */
M2C_UNK func_800B4194();             /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD030[];
extern u8 D_800DD068[];
extern u8 D_800DD070[];
extern u8 D_800DD078[];
extern u8 D_800DD080[];
extern u8 D_800DD088[];
extern u8 D_800DD090[];
extern u8 D_800DD098[];
extern u8 D_800DD0A0[];
extern u8 D_800DD0A8[];
extern u8 D_800DD0B0[];
extern s32 D_800DF244[];
extern s16 D_800DF248[];
extern void *D_800891C0[];


typedef struct S_800B348C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x2];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x23];
    u8 * unk_CC;
    u8 pad_D0[0x24];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
} S_800B348C_0;   /* arg0 in func_800B348C */




typedef struct S_800B348C_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800B348C_4_pre;   /* the 0x14 bytes before temp_a2 in func_800B348C, addressed as temp_a2[-1] */

typedef struct S_800B348C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B348C_4;   /* temp_a2 in func_800B348C */

typedef struct S_800B348C_5 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800B348C_5;   /* temp_a0 in func_800B348C */

typedef struct S_800B348C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B348C_6;   /* end_base in func_800B348C */

typedef struct S_800B348C_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B348C_7;   /* ((S_800B348C_4_pre *)temp_a2)[-1].unk_00 in func_800B348C */

/* Advances the attack and mixing sequence, resetting element flags at its start and finish. */
void func_800B348C(void *action_state, void *motion, void *animation, void *actor) {
    void *held_arg1;
    register void *held_arg2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *windup_animations;
    u8 *attack_animations;
    u8 *mix_animations;
    M2C_UNK sound_id;
    s32 vertical_velocity;
    s32 unused_result;
    s32 launch_direction_offset;
    s32 resume_direction_offset;
    u16 attack_delay;
    u16 mix_delay;
    u16 return_delay;
    u8 jt_index;
    u8 action_phase;

    static void *const jt_keep[] = {
        &&jt_0, &&jt_1, &&jt_2, &&jt_3,
        &&jt_4, &&jt_5, &&jt_6, &&jt_7,
        &&jt_8, &&jt_9, &&jt_10, &&jt_default,
        &&jt_default, &&jt_default, &&jt_default, &&jt_15
    };

    held_arg1 = motion;
    held_arg2 = animation;
#define motion held_arg1
#define animation held_arg2
    jt_index = ((S_800B348C_0 *)action_state)->unk_9B;
    (void)jt_keep;
    if (jt_index >= 16) {
        goto jt_default;
    }
    goto *D_800891C0[jt_index];
    switch (((S_800B348C_0 *)action_state)->unk_9B) {
    case 0:
jt_0:
        ((Rec_D_800E3D7C *)actor)->unk_14.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_14.as_s32 & ~7);
        ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
        D_800DF248[0] = 0;
        return;
    case 1:
jt_1:
        if (((S_800B348C_0 *)action_state)->unk_A6 != 0) {
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD030;
            func_80048A44(animation, D_800DD030[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = NULL;
            if ((u16) ((S_800B348C_0 *)action_state)->unk_A6 >= 2U) {
                return;
            }
        } else {
            ((S_800B348C_0 *)action_state)->unk_F4 = 0;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        }
block_7:
        ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xDFFF);
        ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
    case 2:
jt_2:
        if (((S_800B348C_0 *)action_state)->unk_A6 == 0) {
            func_800C77D0(actor - 0x20, motion, 8, 0x300);
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD068;
            func_80048A44(animation, D_800DD068[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            action_phase = ((S_800B348C_0 *)action_state)->unk_9B;
            ((S_800B348C_0 *)action_state)->unk_CC = NULL;
            goto bump_state_9b;
        }
        break;
    case 3:
jt_3:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            launch_direction_offset = ((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + launch_direction_offset) << 0x11);
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + launch_direction_offset) << 0x11);
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFEBC000;
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD070;
            func_80048A44(animation, D_800DD070[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            {
                u8 *next_animations;

                if (((Rec_D_800E3D7C *)actor)->unk_4C.as_s32 != 0) {
                    next_animations = D_800DD078;
                } else {
                    next_animations = D_800DD0A8;
                }
                ((S_800B348C_0 *)action_state)->unk_CC = next_animations;
            }
            ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            return;
        }
        break;
    case 4:
jt_4:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            windup_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = windup_animations;
            func_80048A44(animation, *(windup_animations + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0, 1);
            {
                u8 *next_v1;

                if (((Rec_D_800E3D7C *)actor)->unk_4C.as_s32 != 0) {
                    next_v1 = D_800DD080;
                } else {
                    next_v1 = D_800DD0B0;
                }
                action_phase = ((S_800B348C_0 *)action_state)->unk_9B;
                ((S_800B348C_0 *)action_state)->unk_CC = next_v1;
            }
            goto bump_state_9b;
        }
        break;
    case 5:
jt_5:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            if (((S_800B348C_0 *)action_state)->unk_A8 != 0) {
                D_800DF248[0] = 1;
                goto load_state_9b;
            }
            ((S_800B348C_0 *)action_state)->unk_96.u = 4U;
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 0xA);
            return;
        }
        break;
    case 15:
jt_15:
        attack_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = attack_delay;
        if (((attack_delay << 0x10) <= 0) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            sound_id = 0x606;
            if (((Rec_D_800E3D7C *)actor)->unk_4C.as_s32 != 0) {
                sound_id = 0x605;
            }
            func_800A56E0(sound_id);
            attack_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = attack_animations;
            func_80048A44(animation, *(attack_animations + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = D_800DD088;
            ((S_800B348C_0 *)action_state)->unk_96.u = 2U;
            ((S_800B348C_0 *)action_state)->unk_9B = 7U;
            return;
        }
        break;
    case 6:
jt_6:
        ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v | 0x800);
        ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 | 8);
        vertical_velocity = ((Rec_D_800E3D7C *)motion)->unk_14.as_s32;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        mix_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = mix_delay;
        D_800DF244[0] = vertical_velocity;
        if ((s16)mix_delay < 0) {
            resume_direction_offset = ((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + resume_direction_offset) << 0x11);
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + resume_direction_offset) << 0x11);
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = vertical_velocity;
            ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xF7FF);
            ((S_800B348C_0 *)action_state)->unk_96.u = 4U;
            ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            func_800B341C(action_state - 0x20, ((S_800B348C_0 *)action_state)->unk_F4, 0x40);
            mix_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = mix_animations;
            func_80048A44(animation, *(mix_animations + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = D_800DD088;
            func_800B3D10(((S_800B348C_0 *)action_state)->unk_A8, ((Rec_D_800E3D7C *)actor)->unk_60.as_pv, actor);
            return;
        }
        break;
    case 7:
jt_7:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
            ((S_800B348C_0 *)action_state)->unk_96.u = 0U;
        } else {
            ((S_800B348C_0 *)action_state)->unk_96.u = (u16) (((S_800B348C_0 *)action_state)->unk_96.u - 1);
        }
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (((S_800B348C_0 *)action_state)->unk_96.s == 0) {
            if (((S_800B348C_0 *)action_state)->unk_102 == 0) {
                register s32 temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */

                temp_a2 = func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
                if (temp_a2 != 0) {
                    func_800B4194(((S_800B348C_0 *)action_state)->unk_A8, temp_a2, actor);
                    ((S_800B348C_0 *)action_state)->unk_A8 = 0U;
                    goto check_mix_delay;
                } else {
                    register void *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */

                    temp_a2 = ((Rec_D_800E3D7C *)actor)->unk_60.as_pv;
                    if (temp_a2 != NULL) {
                        ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = NULL;
                        ((S_800B348C_4 *)temp_a2)->unk_1C = (s32) (((S_800B348C_4 *)temp_a2)->unk_1C & 0xEFFFFFFF);
                        ((S_800B348C_7 *)(((S_800B348C_4_pre *)temp_a2)[-1].unk_00))->unk_0C = 0x808080;
                        goto check_mix_delay;
                    }
                }
            } else {
                void *attached_object;

                attached_object = ((Rec_D_800E3D7C *)actor)->unk_60.as_pv;
                if (attached_object != NULL) {
                    ((S_800B348C_5 *)attached_object)->unk_14 = (s32) (((S_800B348C_5 *)attached_object)->unk_14 | 0x01000000);
                }
            }
        }
check_mix_delay:
        if (((s16) ((S_800B348C_0 *)action_state)->unk_96.u <= 0) && (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000)) {
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD088;
            func_80048A44(animation, D_800DD088[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = D_800DD090;
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
        }
        /* fallthrough */
    case 8:
jt_8:
        if (((S_800B348C_0 *)action_state)->unk_A2 & 0x10) {
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
            if (((S_800B348C_0 *)action_state)->unk_A8 != 0) {
                ((S_800B348C_0 *)action_state)->unk_A8 = 0U;
            }
            if ((s16) ((S_800B348C_0 *)action_state)->unk_96.u <= 0) {
                (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD090;
                func_80048A44(animation, D_800DD090[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
                ((S_800B348C_0 *)action_state)->unk_CC = D_800DD098;
                ((S_800B348C_0 *)action_state)->unk_9B = 9U;
                return;
            }
        }
        break;
    case 9: {
        s32 delta_x;
        s32 delta_y;

jt_9:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD098;
            func_80048A44(animation, D_800DD098[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)action_state)->unk_96.u = 2U;
            delta_x = ((Rec_D_80082E80 *)animation)->unk_24 << 6;
            delta_y = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
            delta_y -= 0x20;
            delta_x -= delta_y;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) ((delta_x << 0x10) / (s16) ((S_800B348C_0 *)action_state)->unk_96.u);
            delta_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) ((s32) (((((Rec_D_80082E80 *)animation)->unk_25 << 6) - delta_y) << 0x10) / (s16) ((S_800B348C_0 *)action_state)->unk_96.u);
load_state_9b:
            action_phase = ((S_800B348C_0 *)action_state)->unk_9B;
bump_state_9b:
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (action_phase + 1);
            return;
        }
        break;
    }
    case 10: {
        u32 end_page;
        s32 *end_base;
        s32 end_mask;
        s32 end_timer_state;
        s32 end_flags;

jt_10:
        return_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = return_delay;
        if (((return_delay << 0x10) <= 0) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
            {
                register void *case10_arg2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                case10_arg2 = animation;
                (*(u8 **)((u8 *)case10_arg2 + 0x2C)) = D_800DD0A0;
                func_80048A44(case10_arg2, D_800DD0A0[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            }
            func_80099F04(((Rec_D_800E3D7C *)actor)->unk_5C);
            end_page = 0x80080000;
            ASM_KEEP(end_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            end_base = (s32 *)(end_page + 0x3460);
            end_mask = -8;
            ((S_800B348C_6 *)end_base)->unk_02 = (u16) (((S_800B348C_6 *)end_base)->unk_02 | 0x412);
            end_timer_state = 0x800E0000;
            ASM_KEEP(end_timer_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            ((S_800B348C_0 *)action_state)->unk_8C = &D_8008ACDC;
            end_flags = ((Rec_D_800E3D7C *)actor)->unk_14.as_s32;
            end_timer_state = *(s16 *)((u8 *)end_timer_state - 0xDB8);
            end_flags &= end_mask;
            ((Rec_D_800E3D7C *)actor)->unk_14.as_s32 = end_flags;
            if (end_timer_state == 0) {
                ((S_800B348C_6 *)end_base)->unk_0C = 0;
            }
            ((S_800B348C_0 *)action_state)->unk_96.u = 0U;
        }
        break;
    }
    default:
jt_default:
        break;
    }
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
}
#undef motion
#undef animation
