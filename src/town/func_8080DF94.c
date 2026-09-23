#include "common.h"


typedef struct Copy12 {
    s32 word[3];
} Copy12;

extern s32 func_80034A1C();
extern s32 func_8003EA54();
extern s32 func_80071494();
extern s32 func_80245C10();
extern s16 func_8025E01C();
extern s32 D_80084D5C;
extern s32 D_80526430[3];
extern u8 D_80288EE0[];
extern u8 D_80288FF0[];
extern u8 D_80289030[];
extern u8 D_80289058[];
extern u8 D_80288F60[];
extern u8 D_80288F88[];

__asm__(".set D_80288FF0, D_80288EE0 + 0x110");
__asm__(".set D_80289030, D_80288EE0 + 0x150");
__asm__(".set D_80289058, D_80288EE0 + 0x178");

typedef struct S_8080DF94_0 {
    void * unk_00;
    s16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_8080DF94_0;   /* obj in func_8080DF94 */

typedef struct S_8080DF94_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x2E];
    s16 unk_36;
} S_8080DF94_1;   /* owner in func_8080DF94 */

typedef struct S_8080DF94_2 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_8080DF94_2;   /* part in func_8080DF94 */

typedef struct S_8080DF94_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080DF94_3;   /* motion in func_8080DF94 */

typedef struct S_8080DF94_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8080DF94_4;   /* target in func_8080DF94 */

/* Per-frame step for the town cutscene actor: dispatch its state and drive its motion, colour fade and timers. */
void func_8080DF94(void *obj, void *motion, void *part) {
    Copy12 scratch;
    s16 state;
    s32 result;
    s32 *scratch_words;
    s32 flag;
    u16 count;
    u16 ticks;
    void *owner;
    void *target;
    s32 vel_x;
    s32 step_x;
    s32 pos_x;

    owner = ((S_8080DF94_0 *)obj)->unk_00;
    scratch_words = scratch.word;
    flag = 0;
    target = (*(void **)((u8 *)(((S_8080DF94_1 *)owner)->unk_04) + (8)));
    scratch = *(Copy12 *)D_80526430;
    func_8003EA54(part);
    func_80245C10(motion);
    state = ((S_8080DF94_0 *)obj)->unk_04;

    if (state == 0x21) {
        goto case_21;
    }
    if (state < 0x22) {
        if (state == 1) {
            goto case_1;
        }
        if (state < 2) {
            if (state == 0) {
                goto case_0;
            }
            goto block_60;
        }
        if (state == 0x20) {
            goto case_20;
        }
        goto block_60;
    }
    if (state == 0x100) {
        goto case_100;
    }
    if (state < 0x101) {
        if (state == 0x22) {
            goto case_22;
        }
        goto block_60;
    }
    if (state == 0x101) {
        goto case_101;
    }
    if (state == 0xFFF) {
        goto case_fff;
    }
    goto block_60;

case_0:
    ((S_8080DF94_2 *)part)->unk_0C = (s32)(((S_8080DF94_2 *)part)->unk_0C + 0x101010);
    if ((u8)((S_8080DF94_2 *)part)->unk_0C < 0xA0U) {
        goto block_60;
    }
    ((S_8080DF94_2 *)part)->unk_0C = 0x808080;
    ((S_8080DF94_2 *)part)->unk_14 = (u16)(((S_8080DF94_2 *)part)->unk_14 & 0xFFF3);
    ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
    goto block_60;

case_1:
    if (((S_8080DF94_0 *)obj)->unk_08 & 1) {
        result = func_80071494();
        flag = scratch_words[result % 3];
        ((S_8080DF94_3 *)motion)->unk_0C = (s32)(((func_80071494() & 0x7F) - 0x40) << 0xF);
        ((S_8080DF94_3 *)motion)->unk_14 = (s32)((0 - ((func_80071494() & 0xF) + 8)) << 0x10);
        if (((S_8080DF94_3 *)motion)->unk_0C > 0) {
            ((S_8080DF94_2 *)part)->unk_14 = (u16)(((S_8080DF94_2 *)part)->unk_14 | 1);
        }
        ((S_8080DF94_3 *)motion)->unk_10 = (s32)((S_8080DF94_4 *)target)->unk_10;
        ((S_8080DF94_0 *)obj)->unk_04 = 0x20;
    }
    if (((S_8080DF94_1 *)owner)->unk_36 == 0xA) {
        if (func_80071494() & 1) {
            flag = (s32)D_80289030;
        } else {
            flag = (s32)D_80289058;
        }
        {
            s32 next_state = 0x100;
            ((S_8080DF94_0 *)obj)->unk_04 = (s16)next_state;
        }
        goto block_60;
    }
    goto block_60;

case_20: {
    s16 floor_y;

    ((S_8080DF94_3 *)motion)->unk_14 = (s32)(((S_8080DF94_3 *)motion)->unk_14 + 0x40000);
    floor_y = func_8025E01C(motion);
    if (floor_y < ((S_8080DF94_3 *)motion)->unk_08) {
        ((S_8080DF94_3 *)motion)->unk_08 = (s32)floor_y;
        ((S_8080DF94_3 *)motion)->unk_14 = (s32)((s32)(0 - ((S_8080DF94_3 *)motion)->unk_14) >> 3);
    }
    if (((S_8080DF94_2 *)part)->unk_14 & 0x6000) {
        ((S_8080DF94_0 *)obj)->unk_06 = 0xA;
        if (((S_8080DF94_2 *)part)->unk_00 == (s32)D_80288FF0) {
            ((S_8080DF94_2 *)part)->unk_0C = 0xA0A0A0;
            ((S_8080DF94_2 *)part)->unk_14 = (u16)(((S_8080DF94_2 *)part)->unk_14 | 0xC);
            ((S_8080DF94_0 *)obj)->unk_04 = 0x22;
            goto block_60;
        }
        if (func_80071494(floor_y) & 1) {
            flag = (s32)D_80288F60;
        } else {
            flag = (s32)D_80288F88;
        }
        ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
    }
    pos_x = ((S_8080DF94_3 *)motion)->unk_0C;
    vel_x = ((S_8080DF94_3 *)motion)->unk_10;
    step_x = pos_x >> 3;
    pos_x -= step_x;
    ((S_8080DF94_3 *)motion)->unk_0C = pos_x;
    pos_x = vel_x >> 3;
    vel_x -= pos_x;
    ((S_8080DF94_3 *)motion)->unk_10 = vel_x;
    goto block_60;
}

case_21: {
    s16 floor_y;

    ((S_8080DF94_3 *)motion)->unk_14 = (s32)(((S_8080DF94_3 *)motion)->unk_14 + 0x40000);
    floor_y = func_8025E01C(motion);
    if (floor_y < ((S_8080DF94_3 *)motion)->unk_08) {
        ((S_8080DF94_3 *)motion)->unk_08 = (s32)floor_y;
        ((S_8080DF94_3 *)motion)->unk_14 = (s32)((s32)(0 - ((S_8080DF94_3 *)motion)->unk_14) >> 3);
    }
    pos_x = ((S_8080DF94_3 *)motion)->unk_0C;
    vel_x = ((S_8080DF94_3 *)motion)->unk_10;
    step_x = pos_x >> 3;
    pos_x -= step_x;
    ((S_8080DF94_3 *)motion)->unk_0C = pos_x;
    pos_x = vel_x >> 3;
    vel_x -= pos_x;
    ((S_8080DF94_3 *)motion)->unk_10 = vel_x;
    count = ((S_8080DF94_2 *)part)->unk_14;
    if (count & 0x6000) {
        ((S_8080DF94_2 *)part)->unk_14 = (u16)(count | 0xC);
        ((S_8080DF94_2 *)part)->unk_0C = 0xA0A0A0;
        ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
        goto block_60;
    }
    goto block_60;
}

case_22:
    ((S_8080DF94_2 *)part)->unk_0C = (s32)(((S_8080DF94_2 *)part)->unk_0C + 0xFFDFDFE0);
    if (((S_8080DF94_3 *)motion)->unk_08 > 0) {
        ((S_8080DF94_3 *)motion)->unk_14 = 0;
        ((S_8080DF94_3 *)motion)->unk_08 = 0;
    }
    if ((u8)((S_8080DF94_2 *)part)->unk_0C < 0x20U) {
        ((S_8080DF94_2 *)part)->unk_0C = 0;
    }
    if ((((S_8080DF94_1 *)owner)->unk_36 == 9) || (ticks = ((S_8080DF94_0 *)obj)->unk_06 - 1, ((S_8080DF94_0 *)obj)->unk_06 = ticks, ((ticks << 0x10) <= 0))) {
        ((S_8080DF94_0 *)obj)->unk_04 = 0xFFF;
        goto block_60;
    }
    goto block_60;

case_100:
    ((S_8080DF94_2 *)part)->unk_0C = 0xA0A0A0;
    ((S_8080DF94_2 *)part)->unk_14 = (u16)(((S_8080DF94_2 *)part)->unk_14 | 0xC);
    ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
case_101:
    ((S_8080DF94_2 *)part)->unk_0C = (s32)(((S_8080DF94_2 *)part)->unk_0C + 0xFFDFDFE0);
    if ((u8)((S_8080DF94_2 *)part)->unk_0C < 0x20U) {
        ((S_8080DF94_2 *)part)->unk_0C = 0;
        ((S_8080DF94_0 *)obj)->unk_04 = 0xFFF;
        goto block_60;
    }
    goto block_60;

case_fff: {
    s32 global_flags;

    (*(u16 *)((u8 *)(obj) + (-2))) = (u16)((*(u16 *)((u8 *)(obj) + (-2))) | 0x8000);
    global_flags = D_80084D5C;
    global_flags |= 0x8000;
    D_80084D5C = global_flags;
    goto block_60;
}

block_60:
    if (flag != 0) {
        func_80034A1C(part, flag, 0);
        ((S_8080DF94_2 *)part)->unk_14 = (u16)(((S_8080DF94_2 *)part)->unk_14 & 0x9FFF);
    }
    return;
}
