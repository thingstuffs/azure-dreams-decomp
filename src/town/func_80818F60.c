#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022F60_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
} S_80022F60_0;   /* arg in func_80022F60 */

typedef struct S_80022F60_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_80022F60_1;   /* main_state in func_80022F60 */

typedef struct S_80022F60_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80022F60_2;   /* motion in func_80022F60 */

typedef struct S_80022F60_3 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80022F60_3;   /* obj in func_80022F60 */

typedef struct S_80022F60_4 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80022F60_4;   /* secondary in func_80022F60 */

typedef struct S_80022F60_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x34];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
} S_80022F60_5;   /* sprite in func_80022F60 */

typedef struct S_80022F60_6 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80022F60_6;   /* image in func_80022F60 */




extern void func_80033B78(s32);
extern s32 func_80033BC0(s32);
extern s32 func_800352FC(void);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void SD_Call(s32);
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
    register u8 *arg ASM_REG("$21") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *secondary = NULL;
    u8 *main_state = D_800834B8;
    s32 state;
    u16 timer;
    register s32 two ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *obj;
    register u8 *sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(arg);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    state = ((S_80022F60_0 *)arg)->unk_00.s;
    timer = ((S_80022F60_0 *)arg)->unk_02.s - 1;
    ((S_80022F60_0 *)arg)->unk_02.s = timer;
    switch (state) {
    case 0:
        if (func_80033BC0(0x524) != 0) {
            u8 *motion;
            s32 angle;

            angle = ((S_80022F60_1 *)main_state)->unk_10.s;
            angle = (angle + 0x1000) & 0xFE00;
            ((S_80022F60_1 *)main_state)->unk_10.u = angle;
            SD_Call(0xB1);
            func_80033B78(0x524);
            ((S_80022F60_0 *)arg)->unk_02.s = 4;
            ((S_80022F60_0 *)arg)->unk_06 = 0;
            (*(u16 *)((u8 *)arg + 0))++;
            motion = (u8 *)&D_80083780;
            ((S_80022F60_2 *)motion)->unk_10 = 0;
            ((S_80022F60_2 *)motion)->unk_0C = 0;
            ((S_80022F60_2 *)motion)->unk_14 = 0xFFE00000;
            *(void **)D_800834B8 = D_80097D2C;
            ((S_80022F60_1 *)main_state)->unk_04 = D_80023934;
            ((S_80022F60_0 *)arg)->unk_08 = 0;
        }
        break;

    case 1:
        ((S_80022F60_1 *)main_state)->unk_10.u =
            (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
        if (((S_80022F60_0 *)arg)->unk_02.u <= 0) {
            u8 *motion = (u8 *)&D_80083780;
            s32 value;

            (*(u16 *)((u8 *)arg + 2)) = 8;
            ((S_80022F60_2 *)motion)->unk_0C =
                (0x03800000 - ((S_80022F60_2 *)motion)->unk_00) / ((S_80022F60_0 *)arg)->unk_02.u;
            value = (0x03800000 - ((S_80022F60_2 *)motion)->unk_04) /
                ((S_80022F60_0 *)arg)->unk_02.u;
            ((S_80022F60_2 *)motion)->unk_14 = 0xFFF40000;
            ((S_80022F60_2 *)motion)->unk_10 = value;
            ((S_80022F60_0 *)arg)->unk_00.u++;
        }
        break;

    case 2:
        {
            register u16 angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            register s32 raw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            raw = ((S_80022F60_1 *)main_state)->unk_10.u + 0x200;
            angle = raw & 0xFFF;
            ((S_80022F60_1 *)main_state)->unk_10.u = angle;
            if (((S_80022F60_0 *)arg)->unk_02.u <= 0) {
                u8 *motion = (u8 *)&D_80083780;

                ((S_80022F60_2 *)motion)->unk_10 = 0;
                ((S_80022F60_2 *)motion)->unk_0C = 0;
                if (angle == 0) {
                    ((S_80022F60_0 *)arg)->unk_00.u++;
                }
            }
        }
        break;

    case 3:
        {
            u8 *motion = (u8 *)&D_80083780;
            u8 *loop_asset;
            register s32 *table_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 one ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            s32 flag_one;
            u8 *alloc_page;

            ((S_80022F60_1 *)main_state)->unk_10.u =
                (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
            if (((S_80022F60_2 *)motion)->unk_0A >= func_800C2AE8(motion)) {
                s32 cur_angle = ((S_80022F60_1 *)main_state)->unk_10.s;

                ((S_80022F60_2 *)motion)->unk_10 = 0;
                ((S_80022F60_2 *)motion)->unk_0C = 0;
                if ((cur_angle == 0) && (func_800352FC() == 0)) {
                    SD_Call(0x200);
                    one = 1;
                    alloc_page = main_state - 0x20;
                    flag_one = D_800272C8;
                    ((S_80022F60_1 *)main_state)->unk_04 = D_80023934;
                    flag_one = 1;
                    D_800272C8 = flag_one;
                    ((S_80022F60_2 *)motion)->unk_04 = 0x03800000;
                    (*(s32 *)((u8 *)motion + 0x10)) = 0;
                    D_800272CA = 0;
                    *(s32 *)&D_80083780 = D_80026F26 << 16;

                    obj = func_8003FD64(one, alloc_page);
                    if (obj != NULL) {
                        ((S_80022F60_3 *)obj)->unk_10 = D_80023F6C;
                        func_8004491C(obj, &D_80053A88);
                        secondary = (u8 *)obj + 0x20;
                        ((S_80022F60_4 *)secondary)->unk_0C.s = 0xC8;
                        ((S_80022F60_4 *)secondary)->unk_0E.s = 0xA0;
                        ((S_80022F60_4 *)secondary)->unk_10 = 0x60;
                        ((S_80022F60_4 *)secondary)->unk_12 = 0x1C;
                        ((S_80022F60_4 *)secondary)->unk_14 = 2;
                        ((S_80022F60_4 *)secondary)->unk_16 = 1;
                        ((S_80022F60_4 *)secondary)->unk_08 = 0x404040;
                        ((S_80022F60_4 *)secondary)->unk_04 = arg;
                    }

                    secondary = (u8 *)1;
                    loop_asset = D_80023FF8;
                    table_base = D_80026F2C;
                    two = (s32)(table_base + 1);
                    main_state = (u8 *)0xB0;
                    do {
                        obj = func_8003FD64(1, D_80083498);
                        if (obj != NULL) {

                            sprite = (u8 *)obj + 0x20;

                            ((S_80022F60_3 *)obj)->unk_10 = loop_asset;
                            func_8004491C(obj, D_80053858);
                            ((S_80022F60_5 *)sprite)->unk_14 = 0xCC;
                            ((S_80022F60_5 *)sprite)->unk_18 = 3;
                            ((S_80022F60_5 *)sprite)->unk_16 = (s32)main_state;
                            ((S_80022F60_5 *)sprite)->unk_1A = 0x7C80;
                            ((S_80022F60_5 *)sprite)->unk_10 = 0x808080;
                            ((S_80022F60_5 *)sprite)->unk_0C = arg;
                            ((S_80022F60_5 *)sprite)->unk_08 =
                                (s32)secondary ? (void *)(arg + 8)
                                               : (void *)0x800135C2;
                            ((S_80022F60_5 *)sprite)->unk_04 = *(s32 *)two;
                        }
                        two -= 4;
                        secondary = (u8 *)((s32)secondary - 1);
                        main_state -= 0xC;
                    } while ((s32)secondary >= 0);

                    obj = func_8003FC64(0x136);
                    if (obj != NULL) {
                        register u8 *image ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                        register s32 *position ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        sprite = (u8 *)obj + 0x20;

                        ((S_80022F60_3 *)obj)->unk_10 = D_80023B14;
                        func_8004491C(obj, D_80045340);
                        image = ((S_80022F60_3 *)obj)->unk_0C;
                        ((S_80022F60_6 *)image)->unk_1E = 0x1000;
                        ((S_80022F60_6 *)image)->unk_1C = 0x1000;
                        ((S_80022F60_6 *)image)->unk_08 = &D_800F9B40;
                        ((S_80022F60_6 *)image)->unk_04 = 0;
                        ((S_80022F60_6 *)image)->unk_05 = 0;
                        ((S_80022F60_6 *)image)->unk_0C = 0x808080;
                        position = ((S_80022F60_3 *)obj)->unk_08;
                        position[0] = 0x03800000;
                        position[1] = 0x03C00000;
                        position[2] = 0;
                        ((S_80022F60_3 *)obj)->unk_20 = arg;
                        ((S_80022F60_5 *)sprite)->unk_50 = 0x20;
                        ((S_80022F60_5 *)sprite)->unk_52 = 4;
                    }
                    func_80093CEC(&D_800D0120);
                    ((S_80022F60_0 *)arg)->unk_00.u++;
                }
            }
        }
        break;

    case 4:
        if (D_80082E94 & 0x6000) {
            func_80093CEC(&D_800D0128);
            ((S_80022F60_0 *)arg)->unk_00.u++;
        }
        break;

    case 5:
        {
            u16 angle;

            angle = (((S_80022F60_1 *)main_state)->unk_10.u + 0xE00) & 0xFFF;
            ((S_80022F60_1 *)main_state)->unk_10.u = angle;
            if (angle == 0xC00) {
                func_80093CEC(&D_800D0138);
                ((S_80022F60_0 *)arg)->unk_00.u++;
            }
        }
        break;

    case 6:
        if (D_80082E94 & 0x6000) {
            ((S_80022F60_0 *)arg)->unk_02.s = 1;
            func_80093CEC(&D_800D0120);
            ((S_80022F60_1 *)main_state)->unk_04 = D_80023994;
            ((S_80022F60_0 *)arg)->unk_00.u = 0x20;
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
                    register u8 *image ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                    s32 *position;
                    s32 random;

                    sprite = (u8 *)obj + 0x20;
                    ((S_80022F60_3 *)obj)->unk_10 = D_80023B14;
                    func_8004491C(obj, D_80045340);
                    image = ((S_80022F60_3 *)obj)->unk_0C;
                    ((S_80022F60_6 *)image)->unk_1E = 0x1000;
                    ((S_80022F60_6 *)image)->unk_1C = 0x1000;
                    ((S_80022F60_6 *)image)->unk_08 = &D_800F9B40;
                    ((S_80022F60_6 *)image)->unk_04 = 0;
                    ((S_80022F60_6 *)image)->unk_05 = 0;
                    ((S_80022F60_6 *)image)->unk_0C = 0x808080;
                    random = rand();
                    ((S_80022F60_5 *)sprite)->unk_54 = random % 3;
                    ((S_80022F60_5 *)sprite)->unk_52 = (rand() & 0x1F) + 0x20;
                    position = ((S_80022F60_3 *)obj)->unk_08;
                    position[0] = 0x02A00000;
                    position[1] = 0x03800000;
                    position[2] = 0xFFC00000;
                    position[3] =
                        (((D_80026F24[((S_80022F60_5 *)sprite)->unk_54] +
                           ((S_80022F60_5 *)sprite)->unk_54 * 8) << 16) - position[0]) /
                        ((S_80022F60_5 *)sprite)->unk_52;
                    position[5] = 0xFFF40000;
                    position[4] = 0x180000 / ((S_80022F60_5 *)sprite)->unk_52;
                    ((S_80022F60_3 *)obj)->unk_20 = arg;
                }
            }
            if (((S_80022F60_0 *)arg)->unk_06 & 1) {
                ((S_80022F60_1 *)main_state)->unk_04 = D_80023934;
                func_80093CEC(&D_800D0138);
                D_800272CA = 0;
                D_800272C8 = 1;
                D_8008378C = 0;
                ((S_80022F60_0 *)arg)->unk_02.s = 0x40;
                ((S_80022F60_0 *)arg)->unk_00.u++;
            }
        }
        break;

    case 0x21:
        {
            s32 current;

            two = 0x03800000;
            current = ((Rec_D_800E3D7C *)(&D_80083780))->unk_00.at00_s32.v;
            ((Rec_D_800E3D7C *)(&D_80083780))->unk_00.at00_s32.v =
                current + ((two - current) >> 1);
            if (((S_80022F60_0 *)arg)->unk_02.u <= 0) {
                obj = func_8003FC64(0x136);

                if (obj != NULL) {
                    register u8 *image ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                    s32 *position;

                    sprite = (u8 *)obj + 0x20;
                    ((S_80022F60_3 *)obj)->unk_10 = D_80023B14;
                    func_8004491C(obj, D_80045340);
                    image = ((S_80022F60_3 *)obj)->unk_0C;
                    ((S_80022F60_6 *)image)->unk_1E = 0x1000;
                    ((S_80022F60_6 *)image)->unk_1C = 0x1000;
                    ((S_80022F60_6 *)image)->unk_08 = &D_800F9B40;
                    ((S_80022F60_6 *)image)->unk_04 = 0;
                    ((S_80022F60_6 *)image)->unk_05 = 0;
                    ((S_80022F60_6 *)image)->unk_0C = 0x808080;
                    ((S_80022F60_5 *)sprite)->unk_54 = 1;
                    ((S_80022F60_5 *)sprite)->unk_52 = 0x20;
                    position = ((S_80022F60_3 *)obj)->unk_08;
                    position[0] = 0x02A00000;
                    position[1] = two;
                    position[2] = 0xFFC00000;
                    position[3] =
                        (((D_80026F24[((S_80022F60_5 *)sprite)->unk_54] +
                           ((S_80022F60_5 *)sprite)->unk_54 * 8) << 16) - position[0]) /
                        ((S_80022F60_5 *)sprite)->unk_52;
                    position[5] = 0xFFF40000;
                    position[4] = 0x180000 / ((S_80022F60_5 *)sprite)->unk_52;
                    ((S_80022F60_3 *)obj)->unk_20 = arg;
                    ((S_80022F60_5 *)sprite)->unk_50 = 0x40;
                }

                obj = func_8003FD64(1, main_state - 0x20);
                if (obj != NULL) {
                    ((S_80022F60_3 *)obj)->unk_10 = D_80023F6C;
                    func_8004491C(obj, &D_80053A88);
                    secondary = (u8 *)obj + 0x20;
                    ((S_80022F60_4 *)secondary)->unk_0C.s = 0x78;
                    ((S_80022F60_4 *)secondary)->unk_0E.s = 0x72;
                    ((S_80022F60_4 *)secondary)->unk_10 = 0x50;
                    ((S_80022F60_4 *)secondary)->unk_12 = 0x10;
                    ((S_80022F60_4 *)secondary)->unk_14 = 2;
                    ((S_80022F60_4 *)secondary)->unk_16 = 1;
                    ((S_80022F60_4 *)secondary)->unk_08 = 0x404040;
                    ((S_80022F60_4 *)secondary)->unk_04 = arg;
                }

                obj = func_8003FD64(1, main_state - 0x20);
                if (obj != NULL) {
                    s32 first;
                    s32 second;
                    s32 color;
                    s32 base;

                    sprite = (u8 *)obj + 0x20;

                    ((S_80022F60_3 *)obj)->unk_10 = D_80024070;
                    func_8004491C(obj, D_80053858);
                    first = ((S_80022F60_4 *)secondary)->unk_0C.u + 4;
                    ((S_80022F60_5 *)sprite)->unk_14 = first;
                    second = ((S_80022F60_4 *)secondary)->unk_0E.u + 4;
                    ((S_80022F60_5 *)sprite)->unk_18 = 3;
                    base = D_80026F34;
                    ((S_80022F60_5 *)sprite)->unk_1A = 0x7C80;
                    color = 0x808080;
                    ((S_80022F60_5 *)sprite)->unk_10 = color;
                    ((S_80022F60_5 *)sprite)->unk_0C = arg;
                    ((S_80022F60_5 *)sprite)->unk_04 = base;
                    ((S_80022F60_5 *)sprite)->unk_16 = second;
                }
                ((S_80022F60_0 *)arg)->unk_00.u++;
            }
        }
        break;

    case 0x22:
        if (((S_80022F60_1 *)main_state)->unk_10.s != 0) {
            ((S_80022F60_1 *)main_state)->unk_10.u =
                (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
        }
        if (((S_80022F60_0 *)arg)->unk_06 & 2) {
            ((S_80022F60_0 *)arg)->unk_02.s = 6;
            ((S_80022F60_0 *)arg)->unk_00.u++;
        }
        break;

    case 0x23:
        if ((s16)timer <= 0) {
            SD_Call(0xB1);
            ((S_80022F60_0 *)arg)->unk_02.s = 0x3C;
            ((S_80022F60_0 *)arg)->unk_00.u = 0xFF;
        }
        break;

    case 0xFF:
        if ((s16)timer <= 0) {
            SD_Call(0x200);
            func_80093D48(main_state, &D_80083780, D_80082E80);
            ((S_80022F60_0 *)arg)->unk_00.s = 0;
        }
        break;

    default:
        break;
    }
}
