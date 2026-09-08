#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80171F9C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171F9C_0;   /* held_arg2 in func_80171F9C */





extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern u8 D_80175E50[];
extern u8 D_80175E70[];
extern u8 D_80175EA8[];

s32 func_80171F9C(Rec_func_800A9E70_arg0 *arg0, s32 arg1, void *arg2, void *arg3) {
    register s32 held_arg1 ASM_REG("$22") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 neg;
    s32 mode;
    u16 old_value;
    register u16 flags_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 status;
    u16 remaining;

    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    status = *(volatile u8 *)((u8 *)arg3 + 0x71);
    {
        S_80171F9C_0 *held_arg2 = arg2;
        register s32 obj ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 *flags ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        *(volatile u8 *)((u8 *)arg3 + 0x71) = status & 0x7F;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        flags = (u16 *)(page + 0x3460);
        ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        mode = 0;
        if (flags[1] & 0x2000) {
            return -1;
        }

        obj = func_800A04F0(arg3, held_arg2->unk_24, held_arg2->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);
        if ((func_800A2CB8(arg3, obj) << 16) == 0) {
            return 0;
        }
        if (flags[1] & 0x2000) {
            return -1;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) && (flags[1] & 8)) {
            return -1;
        }

        neg = 0 - func_800A0134(obj, arg3);
        if ((u32)((neg - 0x20) & 0xFFFF) < 0x21U) {
            mode = 1;
            goto check_ready;
        }
        if ((u32)((neg + 0x10) & 0xFFFF) < 0x31U) {
            mode = 2;
            goto check_ready;
        }
        if ((u32)((neg + 0x40) & 0xFFFF) >= 0x31U) {
            return mode;
        }
        mode = 3;

check_ready:
        if ((func_800A2B5C(arg3) << 16) != 0) {
            return -1;
        }
        func_800C7930((u8 *)arg3 - 0x20, held_arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 16) != 0) {
            return -1;
        }

        {
            register s32 m ASM_REG("$3") = mode;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            arg0->unk_9B.as_s8 = 0;
            if (m == 1) {
                arg0->unk_8C = 0;
                held_arg2->unk_2C = D_80175E50;
                flags_value = arg0->unk_98;
                arg0->unk_9A.as_s8 = 0x11;
                goto set_flag;
            }
            if (m == 2) {
                arg0->unk_8C = 0;
                held_arg2->unk_2C = D_80175E70;
                flags_value = arg0->unk_98;
                arg0->unk_9A.as_s8 = 0x17;
set_flag:
                arg0->unk_98 = flags_value | 8;
                ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
                ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
                goto common;
            }

            arg0->unk_8C = 0;
            held_arg2->unk_2C = D_80175EA8;
            arg0->unk_9A.as_s8 = 0x18;
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xFFFBFFFF;

common:
            {
                u8 *phase_page;
                phase_page = (u8 *)0x80080000;
                func_80047784(held_arg2, held_arg2->unk_2C[((*(s16 *)(phase_page + 0x3228) + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            }
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
            func_8009C93C(arg3, held_arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
            remaining = arg0->unk_90.at02_u16.v;
            old_value = arg0->unk_A0.at02_u16.v;
            arg0->unk_A0.at02_u16.v = 0;
            arg0->unk_9E.as_s16 = 0;
            arg0->unk_90.at02_u16.v = remaining - old_value;
            return mode;
        }
    }
}
