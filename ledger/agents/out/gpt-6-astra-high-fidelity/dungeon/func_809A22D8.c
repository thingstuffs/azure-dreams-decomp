#include "common.h"

#define FIELD_U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define FIELD_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FIELD_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FIELD_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FIELD_PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_80083460[];
extern s32 D_801710EC[];
extern u8 D_80175E90[];

void func_80173AD8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 initial_state;
    s32 state;
    s32 first_value;
    s32 second_value;
    s32 first_adjusted;
    s32 second_adjusted;
    s32 byte_value;
    register s32 delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 *global;
    s16 motion_count;
    s32 state_2_count;
    s16 next_count;

    initial_state = FIELD_U8(arg0, 0x9B);
    if (initial_state == 1) {
        goto state_1;
    }
    if (initial_state < 2) {
        if (initial_state == 0) {
            goto state_0;
        }
        return;
    }
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (initial_state == 2) {
        goto state_2;
    }
    return;

state_0:
    func_800AD4D0(arg3);
    FIELD_U8(arg0, 0x9B) = FIELD_U8(arg0, 0x9B) + 1;
    if (FIELD_U8(arg3, 0x28) == 0) {
        goto reset_motion;
    }
    if (FIELD_U16(arg2, 0x14) & 0x8000) {
        FIELD_S16(arg0, 0x96) = 0;
        FIELD_U8(arg0, 0x9B) = 2;
        return;
    }
    FIELD_S32(arg1, 0xC) =
        (-*(s16 *)((u8 *)D_8006CCD8 + ((FIELD_U16(arg3, 0x6A) >> 8) & 0xE))) << 15;
    FIELD_S32(arg1, 0x10) =
        (-*(s16 *)((u8 *)D_8006CCE8 + ((FIELD_U16(arg3, 0x6A) >> 8) & 0xE))) << 15;
    motion_count = -1;
    if (FIELD_S32(arg3, 0x1C) & 0x228) {
        motion_count = 8;
    }
    FIELD_S16(arg0, 0x96) = motion_count;

state_1:
    first_value = FIELD_S32(arg1, 0xC);
    first_adjusted = first_value;
    if (first_value < 0) {
        first_adjusted = first_value + 3;
    }
    second_value = FIELD_S32(arg1, 0x10);
    FIELD_S32(arg1, 0xC) = first_value - (first_adjusted >> 2);
    second_adjusted = second_value;
    if (second_value < 0) {
        second_adjusted = second_value + 3;
    }
    FIELD_S32(arg1, 0x10) = second_value - (second_adjusted >> 2);
    if (FIELD_S16(arg0, 0x96) > 0) {
        next_count = FIELD_U16(arg0, 0x96) - 1;
        FIELD_S16(arg0, 0x96) = next_count;
    } else if (FIELD_U16(arg2, 0x14) & 0x6000) {
        FIELD_S16(arg0, 0x96) = 0;
    }
    if (FIELD_S16(arg0, 0x96) != 0) {
        return;
    }
    if (FIELD_U8(arg3, 0x28) != 0) {
        goto advance_state;
    }

reset_motion:
    FIELD_S32(arg1, 0x14) = 0;
    FIELD_S32(arg1, 0x10) = 0;
    FIELD_S32(arg1, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, D_80175E90);
    return;

advance_state:
    state = FIELD_U8(arg0, 0x9B);
    motion_count = 8;
    FIELD_S16(arg0, 0x96) = motion_count;
    FIELD_U8(arg0, 0x9B) = state + 1;
    return;

state_2:
    state_2_count = FIELD_S16(arg0, 0x96);
    if (state_2_count != 0) {
        do {
            byte_value = FIELD_U8(arg2, 0x24);
        } while (0);
        delta = FIELD_S16(arg1, 2);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        FIELD_S32(arg1, 0xC) = (((byte_value << 6) - (delta -= 0x20)) << 15) /
                               state_2_count;
        delta = FIELD_S16(arg1, 6) - 0x20;
        byte_value = FIELD_U8(arg2, 0x25);
        FIELD_S32(arg1, 0x10) = (((byte_value << 6) - delta) << 15) /
                                FIELD_S16(arg0, 0x96);
    }
    next_count = (u16)FIELD_S16(arg0, 0x96) - 1;
    FIELD_S16(arg0, 0x96) = next_count;
    if ((next_count << 16) > 0) {
        return;
    }
    FIELD_S32(arg1, 0x14) = 0;
    FIELD_S32(arg1, 0x10) = 0;
    FIELD_S32(arg1, 0xC) = 0;
    func_800A2B04(arg1, FIELD_U8(arg2, 0x24), FIELD_U8(arg2, 0x25));
    global = D_80083460;
    if (global[4] == (s32)((u8 *)arg3 - 0x20)) {
        global[4] &= 0x7FFFFFFF;
    }
    FIELD_PTR(arg0, 0x8C) = D_801710EC;
}
