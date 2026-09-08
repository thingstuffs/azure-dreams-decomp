#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003AD08();
extern void func_8008D330();
extern void func_80098B38();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_80099734();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800A6D30();
extern s16 func_800AD6FC();
extern void func_800C4AFC();

extern s32 D_80082E80;
extern u16 D_80083460[];
extern s32 D_80083780;
extern s32 D_800893E0;
extern u8 D_800DDE84[];
extern s32 D_800E18A4;
extern s32 D_800E3D7C;


typedef struct S_800C4490_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800C4490_0_pre;   /* the 0x18 bytes before arg0 in func_800C4490, addressed as arg0[-1] */


/* Applies a capped random stat gain to the target and displays its effect message. */
s32 func_800C4490(void *target, s32 source, s16 effect_mode) {
    s16 stat_gap;
    s32 stat_gain;
    s32 effect_text;
    register s32 message_context ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 new_context;

    if (target == D_800E3D7C) {
        ((Rec_D_800E3D7C *)target)->unk_110 = source;
        func_8008D330(target, &D_80083780, &D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A63B8(target, source, effect_mode);
        if (func_800AD6FC(target,
                         (*(u16 *)(D_800DDE84 +
                                   ((Rec_D_800E3D7C *)target)->unk_10.at03_u8.v * 2) >> 6) & 3,
                         source) == 0) {
            func_800A5F38(target, source);
            return 1;
        }
    }

    stat_gain = (func_800A6D30() & 3) + 7;
    if (stat_gain >= 0x100) {
        stat_gain = 0xFF;
    }

    stat_gap = ((Rec_D_800E3D7C *)target)->unk_29 - ((Rec_D_800E3D7C *)target)->unk_28;
    if (stat_gap < stat_gain) {
        stat_gain = stat_gap;
    }
    ((Rec_D_800E3D7C *)target)->unk_64.as_s16 = stat_gain;

    if (((Rec_D_800E3D7C *)target)->unk_14.as_s32 & 0x4000) {
        new_context = func_800990FC();
        {
            register void *message_target ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 context_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            message_target = target;
            context_arg = new_context;
            message_context = context_arg;
            effect_text = func_80099734(message_target, context_arg);
        }
        func_80099290(func_80099194(
            &D_800893E0,
            func_8003AD08(((Rec_D_800E3D7C *)target)->unk_64.as_s16,
                          func_80099194(&D_800E18A4, effect_text))));
        func_800A5720(message_context);
    }

    func_800C4AFC(((S_800C4490_0_pre *)target)[-1].unk_00, 0x20E020, target);
    func_80098B38(source);
    D_80083460[5]--;
    return 1;
}
