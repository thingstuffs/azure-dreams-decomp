#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80033B78(s32);
extern s32 func_80033BC0(s32);
extern s32 func_800352FC(void);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80053DA8(s32);
extern s32 rand(void);
extern void func_80093CEC(void *);
extern void func_80093D48(void *, void *, void *);
extern s16 func_800C2AE8(void *);

extern u16 D_800135C2;
extern u8 D_80023934[];
extern u8 D_80023994[];
extern u8 D_80023B14[];
extern u8 D_80023F6C[];
extern u8 D_80023FF8[];
extern u8 D_80024070[];
extern s16 D_80026F24[];
extern s16 D_80026F26;
extern s32 D_80026F2C[];
extern s32 D_80026F34;
extern s16 D_800272C8;
extern s16 D_800272CA;
extern u8 D_80045340[];
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_80082E80[];
extern u16 D_80082E94;
extern u8 D_80083498[];
extern u8 D_800834B8[];
typedef struct {
    u8 raw[0x18];
} MotionState;
typedef struct {
    u8 pad[0x34B8];
    u8 state[0x20];
} TownPage;
extern MotionState D_80083780;
extern s32 D_8008378C;
extern s32 D_80097D2C[3];
extern M2C_UNK D_800D0120;
extern M2C_UNK D_800D0128;
extern M2C_UNK D_800D0138;
extern M2C_UNK D_800F9B40;

void func_80022F60(void *arg0) {
    register u8 *arg ASM_REG("$21") = arg0;
    u8 *secondary = NULL;
    u8 *main_state = D_800834B8;
    s32 state;
    u16 timer;
    register s32 two ASM_REG("$20");
    register void *obj ASM_REG("$17");
    register u8 *sprite ASM_REG("$16");

    ASM_KEEP(arg);
    ASM_KEEP(secondary);

    state = FIELD(arg, s16, 0);
    timer = FIELD(arg, u16, 2) - 1;
    FIELD(arg, u16, 2) = timer;
    switch (state) {
    case 0:
        if (func_80033BC0(0x524) != 0) {
            u8 *motion;
            s32 angle;

            angle = FIELD(main_state, s16, 0x10);
            angle = (angle + 0x1000) & 0xFE00;
            FIELD(main_state, u16, 0x10) = angle;
            func_80053DA8(0xB1);
            func_80033B78(0x524);
            FIELD(arg, u16, 2) = 4;
            FIELD(arg, u16, 6) = 0;
            FIELD(arg, u16, 0)++;
            motion = (u8 *)&D_80083780;
            FIELD(motion, s32, 0x10) = 0;
            FIELD(motion, s32, 0xC) = 0;
            FIELD(motion, s32, 0x14) = 0xFFE00000;
            *(void **)D_800834B8 = D_80097D2C;
            FIELD(main_state, void *, 4) = D_80023934;
            FIELD(arg, u16, 8) = 0;
        }
        break;

    case 1:
        FIELD(main_state, u16, 0x10) =
            (FIELD(main_state, u16, 0x10) + 0x200) & 0xFFF;
        if (FIELD(arg, s16, 2) <= 0) {
            u8 *motion = (u8 *)&D_80083780;
            s32 value;

            FIELD(arg, u16, 2) = 8;
            FIELD(motion, s32, 0xC) =
                (0x03800000 - FIELD(motion, s32, 0)) / FIELD(arg, s16, 2);
            value = (0x03800000 - FIELD(motion, s32, 4)) /
                FIELD(arg, s16, 2);
            FIELD(motion, s32, 0x14) = 0xFFF40000;
            FIELD(motion, s32, 0x10) = value;
            FIELD(arg, u16, 0)++;
        }
        break;

    case 2:
        {
            register u16 angle ASM_REG("$3");
            register s32 raw ASM_REG("$2");

            raw = FIELD(main_state, u16, 0x10) + 0x200;
            angle = raw & 0xFFF;
            FIELD(main_state, u16, 0x10) = angle;
            if (FIELD(arg, s16, 2) <= 0) {
                u8 *motion = (u8 *)&D_80083780;

                FIELD(motion, s32, 0x10) = 0;
                FIELD(motion, s32, 0xC) = 0;
                if (angle == 0) {
                    FIELD(arg, u16, 0)++;
                }
            }
        }
        break;

    case 3:
        {
            u8 *motion = (u8 *)&D_80083780;
            u8 *loop_asset;
            register s32 *table_base ASM_REG("$2");
            register s32 one ASM_REG("$4");
            s32 flag_one;
            register u8 *alloc_page ASM_REG("$5");

            FIELD(main_state, u16, 0x10) =
                (FIELD(main_state, u16, 0x10) + 0x200) & 0xFFF;
            if (FIELD(motion, s16, 0xA) >= func_800C2AE8(motion)) {
                s32 cur_angle = FIELD(main_state, s16, 0x10);

                FIELD(motion, s32, 0x10) = 0;
                FIELD(motion, s32, 0xC) = 0;
                if ((cur_angle == 0) && (func_800352FC() == 0)) {
                    func_80053DA8(0x200);
                    one = 1;
                    alloc_page = main_state - 0x20;
                    flag_one = D_800272C8;
                    FIELD(main_state, void *, 4) = D_80023934;
                    flag_one = 1;
                    D_800272C8 = flag_one;
                    FIELD(motion, s32, 4) = 0x03800000;
                    FIELD(motion, s32, 0x10) = 0;
                    D_800272CA = 0;
                    *(s32 *)&D_80083780 = D_80026F26 << 16;

                    obj = func_8003FD64(one, alloc_page);
                    if (obj != NULL) {
                        FIELD(obj, void *, 0x10) = D_80023F6C;
                        func_8004491C(obj, &D_80053A88);
                        secondary = (u8 *)obj + 0x20;
                        FIELD(secondary, s16, 0xC) = 0xC8;
                        FIELD(secondary, s16, 0xE) = 0xA0;
                        FIELD(secondary, s16, 0x10) = 0x60;
                        FIELD(secondary, s16, 0x12) = 0x1C;
                        FIELD(secondary, s16, 0x14) = 2;
                        FIELD(secondary, s16, 0x16) = 1;
                        FIELD(secondary, s32, 8) = 0x404040;
                        FIELD(secondary, void *, 4) = arg;
                    }

                    secondary = (u8 *)1;
                    loop_asset = D_80023FF8;
                    ASM_KEEP(loop_asset);
                    table_base = D_80026F2C;
                    ASM_KEEP(table_base);
                    two = (s32)(table_base + 1);
                    main_state = (u8 *)0xB0;
                    do {
                        obj = func_8003FD64(1, D_80083498);
                        if (obj != NULL) {

                            sprite = (u8 *)obj + 0x20;

                            FIELD(obj, void *, 0x10) = loop_asset;
                            func_8004491C(obj, D_80053858);
                            FIELD(sprite, s16, 0x14) = 0xCC;
                            FIELD(sprite, s16, 0x18) = 3;
                            FIELD(sprite, s16, 0x16) = (s32)main_state;
                            FIELD(sprite, s16, 0x1A) = 0x7C80;
                            FIELD(sprite, s32, 0x10) = 0x808080;
                            FIELD(sprite, void *, 0xC) = arg;
                            FIELD(sprite, void *, 8) =
                                (s32)secondary ? (void *)(arg + 8)
                                               : (void *)0x800135C2;
                            FIELD(sprite, s32, 4) = *(s32 *)two;
                        }
                        two -= 4;
                        secondary = (u8 *)((s32)secondary - 1);
                        main_state -= 0xC;
                    } while ((s32)secondary >= 0);

                    obj = func_8003FC64(0x136);
                    if (obj != NULL) {
                        register u8 *image ASM_REG("$4");
                        register s32 *position ASM_REG("$5");

                        sprite = (u8 *)obj + 0x20;

                        FIELD(obj, void *, 0x10) = D_80023B14;
                        func_8004491C(obj, D_80045340);
                        image = FIELD(obj, u8 *, 0xC);
                        FIELD(image, s16, 0x1E) = 0x1000;
                        FIELD(image, s16, 0x1C) = 0x1000;
                        FIELD(image, void *, 8) = &D_800F9B40;
                        FIELD(image, s8, 4) = 0;
                        FIELD(image, s8, 5) = 0;
                        FIELD(image, s32, 0xC) = 0x808080;
                        position = FIELD(obj, s32 *, 8);
                        position[0] = 0x03800000;
                        position[1] = 0x03C00000;
                        position[2] = 0;
                        FIELD(obj, void *, 0x20) = arg;
                        FIELD(sprite, s16, 0x50) = 0x20;
                        FIELD(sprite, s16, 0x52) = 4;
                    }
                    func_80093CEC(&D_800D0120);
                    FIELD(arg, u16, 0)++;
                }
            }
        }
        break;

    case 4:
        if (D_80082E94 & 0x6000) {
            func_80093CEC(&D_800D0128);
            FIELD(arg, u16, 0)++;
        }
        break;

    case 5:
        {
            u16 angle;

            angle = (FIELD(main_state, u16, 0x10) + 0xE00) & 0xFFF;
            FIELD(main_state, u16, 0x10) = angle;
            if (angle == 0xC00) {
                func_80093CEC(&D_800D0138);
                FIELD(arg, u16, 0)++;
            }
        }
        break;

    case 6:
        if (D_80082E94 & 0x6000) {
            FIELD(arg, u16, 2) = 1;
            func_80093CEC(&D_800D0120);
            FIELD(main_state, void *, 4) = D_80023994;
            FIELD(arg, u16, 0) = 0x20;
        }
        break;

    case 0x20:
        {
            secondary = (u8 *)(state - (*(s16 *)0x800135C2 / 10));
            if ((s32)secondary <= 0) {
                secondary = (u8 *)1;
            }
            if (((s16)timer % (s32)secondary) == 0) {
                obj = func_8003FC64(0x136);

                if (obj != NULL) {
                    register u8 *image ASM_REG("$4");
                    register s32 *position ASM_REG("$5");
                    s32 random;

                    sprite = (u8 *)obj + 0x20;
                    FIELD(obj, void *, 0x10) = D_80023B14;
                    func_8004491C(obj, D_80045340);
                    image = FIELD(obj, u8 *, 0xC);
                    FIELD(image, s16, 0x1E) = 0x1000;
                    FIELD(image, s16, 0x1C) = 0x1000;
                    FIELD(image, void *, 8) = &D_800F9B40;
                    FIELD(image, s8, 4) = 0;
                    FIELD(image, s8, 5) = 0;
                    FIELD(image, s32, 0xC) = 0x808080;
                    random = rand();
                    FIELD(sprite, s16, 0x54) = random % 3;
                    FIELD(sprite, s16, 0x52) = (rand() & 0x1F) + 0x20;
                    position = FIELD(obj, s32 *, 8);
                    position[0] = 0x02A00000;
                    position[1] = 0x03800000;
                    position[2] = 0xFFC00000;
                    position[3] =
                        (((D_80026F24[FIELD(sprite, s16, 0x54)] +
                           FIELD(sprite, s16, 0x54) * 8) << 16) - position[0]) /
                        FIELD(sprite, s16, 0x52);
                    position[5] = 0xFFF40000;
                    position[4] = 0x180000 / FIELD(sprite, s16, 0x52);
                    FIELD(obj, void *, 0x20) = arg;
                }
            }
            if (FIELD(arg, u16, 6) & 1) {
                FIELD(main_state, void *, 4) = D_80023934;
                func_80093CEC(&D_800D0138);
                D_800272CA = 0;
                D_800272C8 = 1;
                D_8008378C = 0;
                FIELD(arg, u16, 2) = 0x40;
                FIELD(arg, u16, 0)++;
            }
        }
        break;

    case 0x21:
        {
            s32 current;

            two = 0x03800000;
            current = FIELD(&D_80083780, s32, 0);
            FIELD(&D_80083780, s32, 0) =
                current + ((two - current) >> 1);
            if (FIELD(arg, s16, 2) <= 0) {
                obj = func_8003FC64(0x136);

                if (obj != NULL) {
                    register u8 *image ASM_REG("$4");
                    register s32 *position ASM_REG("$5");

                    sprite = (u8 *)obj + 0x20;
                    FIELD(obj, void *, 0x10) = D_80023B14;
                    func_8004491C(obj, D_80045340);
                    image = FIELD(obj, u8 *, 0xC);
                    FIELD(image, s16, 0x1E) = 0x1000;
                    FIELD(image, s16, 0x1C) = 0x1000;
                    FIELD(image, void *, 8) = &D_800F9B40;
                    FIELD(image, s8, 4) = 0;
                    FIELD(image, s8, 5) = 0;
                    FIELD(image, s32, 0xC) = 0x808080;
                    FIELD(sprite, s16, 0x54) = 1;
                    FIELD(sprite, s16, 0x52) = 0x20;
                    position = FIELD(obj, s32 *, 8);
                    position[0] = 0x02A00000;
                    position[1] = two;
                    position[2] = 0xFFC00000;
                    position[3] =
                        (((D_80026F24[FIELD(sprite, s16, 0x54)] +
                           FIELD(sprite, s16, 0x54) * 8) << 16) - position[0]) /
                        FIELD(sprite, s16, 0x52);
                    position[5] = 0xFFF40000;
                    position[4] = 0x180000 / FIELD(sprite, s16, 0x52);
                    FIELD(obj, void *, 0x20) = arg;
                    FIELD(sprite, s16, 0x50) = 0x40;
                }

                obj = func_8003FD64(1, main_state - 0x20);
                if (obj != NULL) {
                    FIELD(obj, void *, 0x10) = D_80023F6C;
                    func_8004491C(obj, &D_80053A88);
                    secondary = (u8 *)obj + 0x20;
                    FIELD(secondary, s16, 0xC) = 0x78;
                    FIELD(secondary, s16, 0xE) = 0x72;
                    FIELD(secondary, s16, 0x10) = 0x50;
                    FIELD(secondary, s16, 0x12) = 0x10;
                    FIELD(secondary, s16, 0x14) = 2;
                    FIELD(secondary, s16, 0x16) = 1;
                    FIELD(secondary, s32, 8) = 0x404040;
                    FIELD(secondary, void *, 4) = arg;
                }

                obj = func_8003FD64(1, main_state - 0x20);
                if (obj != NULL) {
                    s32 first;
                    s32 second;
                    register s32 color ASM_REG("$5");
                    register s32 base ASM_REG("$4");

                    sprite = (u8 *)obj + 0x20;

                    FIELD(obj, void *, 0x10) = D_80024070;
                    func_8004491C(obj, D_80053858);
                    first = FIELD(secondary, u16, 0xC) + 4;
                    FIELD(sprite, s16, 0x14) = first;
                    second = FIELD(secondary, u16, 0xE) + 4;
                    FIELD(sprite, s16, 0x18) = 3;
                    base = D_80026F34;
                    FIELD(sprite, s16, 0x1A) = 0x7C80;
                    color = 0x808080;
                    FIELD(sprite, s32, 0x10) = color;
                    FIELD(sprite, void *, 0xC) = arg;
                    FIELD(sprite, s32, 4) = base;
                    FIELD(sprite, s16, 0x16) = second;
                }
                FIELD(arg, u16, 0)++;
            }
        }
        break;

    case 0x22:
        if (FIELD(main_state, s16, 0x10) != 0) {
            FIELD(main_state, u16, 0x10) =
                (FIELD(main_state, u16, 0x10) + 0x200) & 0xFFF;
        }
        if (FIELD(arg, u16, 6) & 2) {
            FIELD(arg, u16, 2) = 6;
            FIELD(arg, u16, 0)++;
        }
        break;

    case 0x23:
        if ((s16)timer <= 0) {
            func_80053DA8(0xB1);
            FIELD(arg, u16, 2) = 0x3C;
            FIELD(arg, u16, 0) = 0xFF;
        }
        break;

    case 0xFF:
        if ((s16)timer <= 0) {
            func_80053DA8(0x200);
            func_80093D48(main_state, &D_80083780, D_80082E80);
            FIELD(arg, s16, 0) = 0;
        }
        break;

    default:
        break;
    }
}
