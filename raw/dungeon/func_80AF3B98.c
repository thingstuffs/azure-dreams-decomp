#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct DungeonCopy3 {
    s32 x;
    s32 y;
    s32 z;
} DungeonCopy3;

typedef struct DungeonChild {
    s32 x;
    s32 y;
    s32 z;
} DungeonChild;

typedef struct DungeonTail {
    u8 pad0[0x0C];
    u32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 value1c;
    u16 value1e;
} DungeonTail;

typedef struct DungeonEffect {
    u8 pad0[8];
    DungeonChild *child;
    DungeonTail *tail;
    void *resource;
} DungeonEffect;

extern void *D_80170908[];

extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 *D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_80174BE4[];
extern u8 D_8017526C[];
extern u8 D_801759F8[];
extern s32 D_80175A00[];
extern s16 D_80175A18;
extern u8 D_80175A80[];
extern u8 D_80175A81;
extern void *D_80175A84;

extern void func_8003DB94();
extern s32 func_8003E4FC();
extern void func_8003F540();
extern void *func_8003FC64();
extern s32 func_80041588();
extern s32 func_800445E0();
extern s32 func_8004491C();
extern void func_80047738();
extern s32 func_800498A0();
extern s32 func_80069EF8();
extern s32 func_8009A028();
extern s32 func_8009A3D0();
extern s32 func_800A18E8();
extern void *func_800A504C();
extern s32 func_800A56E0();
extern s32 func_800ADC4C();
extern s32 func_800C77D0();
extern s32 func_80174F24();
extern void func_801756FC() __attribute__((noreturn));
extern void func_801758EC() __attribute__((noreturn));

void func_80175398(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
    };
    u8 *var_s0 = D_80083160;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 9U) {
        goto done;
    }
    (void)jt_keep;
    goto *D_80170908[state];

jt_c0:
    {
        register u32 next_state ASM_REG("$2");

        next_state = FIELD(arg0, u8, 0x9B) + 1;
        ASM_TAILSLOT_PIN(next_state);
    }
    func_801756FC();

jt_c1:
    func_80041588(D_801759F8, D_80175A80, 0);
    FIELD(arg0, s16, 0xAC) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg3, u16, 0x8A) = FIELD(arg3, u16, 0x2A);

jt_c2:
    {
        s32 direction;
        u16 angle;

        direction = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        angle = FIELD(arg3, u16, 0x2A);
        if (D_80175A80[0] == 0) {
            goto direction_not_ready;
        }
        if (direction == 2) {
            goto direction_ready;
        }
direction_not_ready:
        if (direction == 2) {
            goto done;
        }
        FIELD(arg3, u16, 0x2A) = angle + 0x200;
        func_801758EC();

direction_ready:
        func_80041588(D_801759F8, D_80175A80, 1);
        func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
        func_8003E4FC(0x15, func_800445E0(), 0);
        D_80175A81 = 0;
        func_8003E4FC(0xFF, D_8003E140, &D_80175A81);
        func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B)++;
    }

jt_c3:
    {
        u16 old_timer = FIELD(arg0, u16, 0x96);
        u16 timer = old_timer - 1;
        u8 *target;

        FIELD(arg0, u16, 0x96) = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 finished = D_80175A81;
            FIELD(arg0, u16, 0x96) = old_timer;
            if (finished == 0) {
                goto done;
            }
            FIELD(arg0, u8, 0x9B)++;
            func_800A56E0(0x300);
            func_801758EC();
        }

        target = D_800DCEEC[func_800498A0(arg3)];
        FIELD(var_s0, u8, 0xA8) +=
            (FIELD(target, u8, 0) - FIELD(var_s0, u8, 0xA8)) /
            FIELD(arg0, s16, 0x96);
        FIELD(var_s0, u8, 0xA9) +=
            (FIELD(target, u8, 1) - FIELD(var_s0, u8, 0xA9)) /
            FIELD(arg0, s16, 0x96);
        FIELD(var_s0, u8, 0xAA) +=
            (FIELD(target, u8, 2) - FIELD(var_s0, u8, 0xAA)) /
            FIELD(arg0, s16, 0x96);
        func_801758EC();
    }

jt_c4:
    var_s0 = func_8003FC64(0x12);
    if (var_s0 == NULL) {
        goto done;
    }
    {
        DungeonEffect *effect = (DungeonEffect *)var_s0;

        effect->resource = D_8017526C;
        func_8004491C(effect, D_80174BE4);
        FIELD(arg0, void *, 0xA8) = effect;
        effect->child->x = ((DungeonCopy3 *)arg1)->x;
        effect->child->y = ((DungeonCopy3 *)arg1)->y;
        D_80175A18 = -2;
        effect->child->z = ((DungeonCopy3 *)arg1)->z;
        var_s0 = (u8 *)effect->tail;
        ((DungeonTail *)var_s0)->value1e = 0x1000;
        ((DungeonTail *)var_s0)->value1c = 0x1000;
        ((DungeonTail *)var_s0)->color = 0x00808080;
    }
    {
        s16 selector = func_800498A0(arg3) - 1;

        if (selector < 0) {
            s32 random = func_80069EF8();

            ASM_KEEP(var_s0);
            selector = random % 3;
        }
        func_8003DB94(var_s0, D_8014A000 + D_80175A00[selector], 0);
    }
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_801758EC();

jt_c5:
    {
        u16 old_timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = old_timer + 1;
        if ((s16)old_timer < 30) {
            s16 i = 0;
            do {
                func_80174F24(arg0, arg1, arg2, arg3);
                i++;
            } while (i < 8);
        }
    }
    var_s0 = FIELD(arg0, u8 *, 0xA8);
    var_s0 = FIELD(var_s0, u8 *, 0xC);
    if (FIELD(var_s0, u16, 0x14) & 0xE000) {
        FIELD(arg0, u8, 0x9B)++;
    }

jt_c6:
    if (FIELD(arg0, u8, 0x9B) != 6) {
        goto done;
    }
    if (func_800ADC4C(arg1, D_80175A84, D_80175A18, D_800DCF5C) == 0) {
        goto done;
    }
    FIELD(arg0, u16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A18E8(FIELD(arg3, u8, 0x13), 3);
    func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
    func_8009A028(arg3);
    var_s0 = (u8 *)arg3 - 0x20;
    FIELD(var_s0, u32, 0x10) |= 0x80000000;
    func_801758EC();

jt_c7:
    {
        u8 *linked = func_800A504C(arg2, arg3);
        FIELD(arg3, u8 *, 0x60) = linked;
        if (linked == NULL) {
            goto done;
        }
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(FIELD(arg3, u8 *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x2A);
        {
            u8 *linked2 = FIELD(arg3, u8 *, 0x60);
            s32 direction;
            u8 *choices;

            var_s0 = FIELD(linked2, u8 *, -0x14);
            direction = ((D_80083228 + FIELD(linked2, s16, 0x2A) + 0x100) >> 9) & 7;
            choices = FIELD(var_s0, u8 *, 0x2C);
            func_80047738(var_s0, choices[direction], FIELD(var_s0, s8, 4));
        }
        FIELD(var_s0, u16, 0x14) &= 0xFFFE;
    }

jt_c8:
    {
        u16 timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            goto done;
        }
        {
            register u8 *counter;

            FIELD(FIELD(arg3, u8 *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x8A);
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            counter = D_80083460;
            FIELD(counter, u16, 0xA)--;
        }
    }
    FIELD(arg3, s8, 0x6D) = 0;

done:
    return;
}
