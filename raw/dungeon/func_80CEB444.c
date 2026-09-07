#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801724BC[];
extern u8 D_80175E3C[];
extern u8 D_80175E44[];
extern u8 D_80175E4C[];

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

void func_80174C44(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 initial_state;
    s32 kind;
    s16 timer;
    u16 count;
    s32 origin;
    s32 value;
    void *global;

    initial_state = FIELD(arg0, u8, 0x9B);
    if (initial_state == 1) {
        goto state_1;
    }
    if (initial_state < 2) {
        if (initial_state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (initial_state == 2) {
        goto state_2;
    }
    if (initial_state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(arg3);
    FIELD(arg0, s16, 0x96) = 6;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto state_0_active;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    kind = FIELD(arg3, u8, 0x48);
    if (kind == 14) {
        goto kind_14;
    }
    if (kind < 15) {
        goto kind_less_15;
    }
    if (kind != 15) {
        goto done;
    }
    goto kind_15_from_state_0;

state_0_active:
    if ((FIELD(arg2, u16, 0x14) & 0x8000) == 0) {
        goto done;
    }
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B) = 3;
    goto done;

state_1:
    timer = (u16)FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = timer;
    if (timer <= 0) {
        goto state_1_nonpositive;
    }

    FIELD(arg1, s32, 0x0C) =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
    FIELD(arg1, s32, 0x10) =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
    goto done;

state_1_nonpositive:
    if (timer != 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x0C) =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
    FIELD(arg1, s32, 0x10) =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
    FIELD(arg0, s16, 0x96) = 12;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    goto done;

state_2:
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto state_2_active;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    kind = FIELD(arg3, u8, 0x48);
    if (kind == 14) {
        goto kind_14;
    }
    if (kind >= 15) {
        goto kind_at_least_15;
    }

kind_less_15:
    if (kind == 13) {
        goto kind_13;
    }
    goto done;

kind_at_least_15:
    if (kind == 15) {
        goto kind_15;
    }
    goto done;

kind_13:
    func_800AAA54(arg0, arg1, arg2, D_80175E3C);
    goto done;

kind_14:
    func_800AAA54(arg0, arg1, arg2, D_80175E44);
    goto done;

kind_15:
    func_800AAA54(arg0, arg1, arg2, D_80175E4C);
    goto done;

kind_15_from_state_0:
    func_800AAA54(arg0, arg1, arg2, D_80175E4C);
    goto done;

state_2_active:
    timer = FIELD(arg0, s16, 0x96);
    if (timer != 0) {
        value = FIELD(arg2, u8, 0x24);
        origin = FIELD(arg1, s16, 2);
        value <<= 6;
        origin -= 0x20;
        value -= origin;
        value = (value << 16) / timer;
        origin = FIELD(arg1, s16, 6);
        FIELD(arg1, s32, 0x0C) = value;
        origin -= 0x20;
        value = (FIELD(arg2, u8, 0x25) << 6) - origin;
        value = (value << 16) / FIELD(arg0, s16, 0x96);
        FIELD(arg1, s32, 0x10) = value;
    }

    count = FIELD(arg0, u16, 0x96);
    FIELD(arg0, s16, 0x96) = count - 1;
    if ((s32)(count << 16) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    goto done;

state_3:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    global = &D_80083460;
    if (FIELD(global, s32, 0x10) == (s32)arg3 - 0x20) {
        FIELD(global, s32, 0x10) &= 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = D_801724BC;

done:
    return;
}
