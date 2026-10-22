#include "common.h"
#include "shared/minigame_body.h"
#include "shared/vector.h"
#include "town/scene/effect.h"
extern int abs(int);

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8052F2C8_0 {
    void * unk_00;
    s32 unk_04;
    s32 unk_08;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    s16 unk_0E;
    u16 unk_10;
} S_8052F2C8_0;   /* obj_held in animate_rising_effect_object */

typedef struct S_8052F2C8_1 {
    void * unk_00;
    u8 pad_04[0x50];
    union { s16 s; u16 u; } unk_54;   /* accessed as both */
    s16 unk_56;
    u16 unk_58;
} S_8052F2C8_1;   /* root in animate_rising_effect_object */

   /* state_held in animate_rising_effect_object */

typedef struct S_8052F2C8_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union { u8 u8; void * p32; } unk_0C;   /* accessed as both */
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    void * unk_20;
    s32 unk_24;
} S_8052F2C8_3;   /* work in animate_rising_effect_object */

typedef struct S_8052F2C8_4 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_8052F2C8_4;   /* data0 in animate_rising_effect_object */

typedef struct S_8052F2C8_5 {
    u8 pad_00[0x16];
    u16 unk_16;
} S_8052F2C8_5;   /* root_obj in animate_rising_effect_object */

   /* data1 in animate_rising_effect_object */

   /* spawn_data in animate_rising_effect_object */

typedef struct S_8052F2C8_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8052F2C8_8;   /* position in animate_rising_effect_object */

typedef struct S_8052F2C8_9 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8052F2C8_9;   /* entity_data in animate_rising_effect_object */


extern void *func_800373DC();
extern void func_8003BC18();
extern void func_80058F88();
extern s32 func_80071494();
extern void create_object_position_configures_color();
extern void func_8052F960();
extern void func_8052FB08();
extern u8 D_8003C558[12];
extern s32 D_80084D5C;
extern s32 D_80095AAC;
extern s32 D_80132AEC;
extern u8 D_8028E17C[];
extern u8 D_8028E188[];
extern void D_8052F8C4();

/* Per-frame step for the town scene object: dispatch its mode and update the sprite it draws. */
void animate_rising_effect_object(void *obj, void *state_in, void *input) {
    register void *obj_held = obj;
    register void *state_held = state_in;
    register void *work;
    s16 state;
    s16 mode;
    s16 timer;
    s32 timer0;
    s32 timer_end;
    s32 step;
    s32 sum;
    s32 sum3;
    s32 count;
    s32 count4;
    s32 x;
    s32 rnd;
    s32 x4;
    s32 color4;
    s32 work_value;
    s16 scale;
    u16 kind;
    register void *root;
    void *root_obj;
    void *position;
    void *data0;
    TownScoreCounterView *data1;
    TownScoreCounterView *spawn_data;
    void *entity_data;
    s32 *money;

    do {
        root = ((S_8052F2C8_0 *)obj_held)->unk_00;
    } while (0);
    ((S_8052F2C8_1 *)root)->unk_58 |= 1;
    root_obj = ((S_8052F2C8_1 *)root)->unk_00;
    work = input;

    if (((S_8052F2C8_1 *)root)->unk_54.s == 9) {
        mode = ((S_8052F2C8_0 *)obj_held)->unk_0C.s;
        if (mode == 1 && ((IntVector3 *)state_held)->x <= 0x04DFFFFF) {
            state = ((S_8052F2C8_1 *)root)->unk_56;
            switch (state) {
            case 0:
                ((S_8052F2C8_3 *)work)->unk_0C.u8 = 0xFF;
                count = 3;
                do {
                    func_8052F960(state_held);
                    count--;
                } while (count >= 0);
                break;
            case 1:
                ((S_8052F2C8_3 *)work)->unk_14 |= 0xC;
                count = 2;
                do {
                    func_8052FB08(state_held);
                    count--;
                } while (count >= 0);
                break;
            case 2:
                timer = ((S_8052F2C8_3 *)work)->unk_1E + 0x200;
                ((S_8052F2C8_3 *)work)->unk_1E = timer;
                ((S_8052F2C8_3 *)work)->unk_1C = timer;
                break;
            }
        }
    }

    switch (((S_8052F2C8_0 *)obj_held)->unk_0C.s) {
    case 0:
        if (((S_8052F2C8_0 *)obj_held)->unk_0E == 0x10) {
            ((S_8052F2C8_1 *)root)->unk_58 |= 4;
        } else {
            ((S_8052F2C8_1 *)root)->unk_58 &= 0xFFFB;
        }
        timer0 = (u16)((S_8052F2C8_0 *)obj_held)->unk_0E - 1;
        ((S_8052F2C8_0 *)obj_held)->unk_0E = timer0;
        if ((timer0 << 16) > 0) {
            break;
        }
        func_80058F88(0x518);
        data0 = ((S_8052F2C8_1 *)root)->unk_00;
        ((S_8052F2C8_4 *)data0)->unk_12++;
        ((S_8052F2C8_0 *)obj_held)->unk_0C.s = 1;
        ((S_8052F2C8_3 *)work)->unk_14 &= 0xFF7F;
        break;

    case 1:
        step = ((S_8052F2C8_0 *)obj_held)->unk_04 + ((S_8052F2C8_0 *)obj_held)->unk_08;
        ((S_8052F2C8_0 *)obj_held)->unk_04 = step;
        sum = ((IntVector3 *)state_held)->x + ((S_8052F2C8_0 *)obj_held)->unk_04;
        ((IntVector3 *)state_held)->x = sum;
        if (sum <= 0x0427FFFF) {
            ((S_8052F2C8_0 *)obj_held)->unk_0E = 6;
            money = &D_80095AAC;
            if (*(u8 *)money >= 9U) {
                *money += 0xFFF7F7F8;
            }
            ((S_8052F2C8_3 *)work)->unk_14 |= 0x80;
            func_80058F88(0x506);
            ((S_8052F2C8_0 *)obj_held)->unk_0C.s = 2;
            break;
        }
        {
            s32 current_y;
            s32 delta;
            s32 target_y;
            s32 *target_y_addr;

            target_y_addr = &D_80132AEC;
            target_y = *target_y_addr;
            current_y = ((IntVector3 *)state_held)->y;
            delta = target_y - current_y;
            delta = abs(delta);
            if (delta > 0x200000) {
                break;
            }
        }
        if (sum > 0x043FFFFF) {
            break;
        }
        if (((S_8052F2C8_0 *)obj_held)->unk_10 & 4) {
            break;
        }

        kind = ((S_8052F2C8_5 *)root_obj)->unk_16 - 3;
        if (kind < 3U) {
            func_80058F88(0x513);
            ((S_8052F2C8_0 *)obj_held)->unk_04 = 0x180000;
            ((S_8052F2C8_0 *)obj_held)->unk_0C.s = 3;
            ((S_8052F2C8_0 *)obj_held)->unk_10 |= 4;
            data1 = ((S_8052F2C8_1 *)root)->unk_00;
            ((S_8052F2C8_1 *)root)->unk_54.u++;
            data1->unk_14 += 2;
            if (((S_8052F2C8_1 *)root)->unk_54.s == 10) {
                data1 = ((S_8052F2C8_1 *)root)->unk_00;
                data1->unk_14 += 10;
            }
            break;
        }
        if (kind >= 7U) {
            break;
        }

        func_80058F88(0x510);
        ((S_8052F2C8_0 *)obj_held)->unk_10 |= 4;
        spawn_data = ((S_8052F2C8_1 *)root)->unk_00;
        count = 1;
        spawn_data->unk_14++;
        scale = 0x1000;
        do {
            work = func_800373DC(0x136);
            if (work != NULL) {
                ((S_8052F2C8_3 *)work)->unk_10 = D_8052F8C4;
                func_8003BC18(work, D_8003C558);
                position = ((S_8052F2C8_3 *)work)->unk_08;
                entity_data = ((S_8052F2C8_3 *)work)->unk_0C.p32;
                ((S_8052F2C8_8 *)position)->unk_00 = ((IntVector3 *)state_held)->x;
                ((S_8052F2C8_8 *)position)->unk_04 = ((IntVector3 *)state_held)->y;
                ((S_8052F2C8_8 *)position)->unk_08 = ((IntVector3 *)state_held)->z;
                work_value = ((S_8052F2C8_0 *)obj_held)->unk_04;
                ((S_8052F2C8_3 *)work)->unk_20 = root;
                ((S_8052F2C8_3 *)work)->unk_24 = work_value;
                ((S_8052F2C8_9 *)entity_data)->unk_1E = scale;
                ((S_8052F2C8_9 *)entity_data)->unk_1C = scale;
                if (count != 0) {
                    ((S_8052F2C8_9 *)entity_data)->unk_08 = D_8028E188;
                    ((S_8052F2C8_8 *)position)->unk_10 = 0x80000;
                } else {
                    ((S_8052F2C8_9 *)entity_data)->unk_08 = D_8028E17C;
                    ((S_8052F2C8_8 *)position)->unk_10 = 0xFFF80000;
                }
                ((S_8052F2C8_9 *)entity_data)->unk_04 = 0;
                ((S_8052F2C8_9 *)entity_data)->unk_05 = 0;
                ((S_8052F2C8_9 *)entity_data)->unk_0C = 0x808080;
            }
            count--;
        } while (count >= 0);
        ((S_8052F2C8_0 *)obj_held)->unk_0C.u = 0xFF;
        break;

    case 2:
        count = 7;
        do {
            count--;
            x = (((func_80071494() & 0xFF) - 0x80) << 14) + ((IntVector3 *)state_held)->x;
            rnd = func_80071494();
            create_object_position_configures_color(0, x, ((IntVector3 *)state_held)->y + 0x80000,
                          ((rnd % 80) << 16) + 0xFFB00000);
        } while (count >= 0);
        timer_end = (u16)((S_8052F2C8_0 *)obj_held)->unk_0E - 1;
        ((S_8052F2C8_0 *)obj_held)->unk_0E = timer_end;
        if ((timer_end << 16) <= 0) {
            ((S_8052F2C8_0 *)obj_held)->unk_0C.u = 0xFF;
        }
        break;

    case 3:
        ((S_8052F2C8_1 *)root)->unk_58 |= 2;
        sum3 = ((IntVector3 *)state_held)->x + ((S_8052F2C8_0 *)obj_held)->unk_04;
        ((IntVector3 *)state_held)->x = sum3;
        if (sum3 > 0x055FFFFF) {
            ((S_8052F2C8_0 *)obj_held)->unk_0E = 5;
            func_80058F88(0x50C);
            ((S_8052F2C8_0 *)obj_held)->unk_0C.s = 4;
        }
        break;

    case 4:
        ((S_8052F2C8_1 *)root)->unk_58 |= 2;
        for (count4 = 7; count4 >= 0; count4--) {
            x4 = (((func_80071494() & 0xFF) - 0x80) << 14) + 0x05600000;
            color4 = ((func_80071494() & 0x3F) << 16) | 0xFFC00000;
            create_object_position_configures_color(0, x4, ((IntVector3 *)state_held)->y + 0x80000, color4);
        }


        timer_end = (u16)((S_8052F2C8_0 *)obj_held)->unk_0E - 1;
        ((S_8052F2C8_0 *)obj_held)->unk_0E = timer_end;
        if ((timer_end << 16) <= 0) {
            ((S_8052F2C8_0 *)obj_held)->unk_0C.u = 0xFF;
        }
        break;

    case 0xFF:
        ((S_8052F2C8_1 *)root)->unk_58 &= 0xFFFE;
        (*(u16 *)((u8 *)obj_held + -2)) |= 0x8000;
        D_80084D5C |= 0x8000;
        break;

    default:
        break;
    }
}
