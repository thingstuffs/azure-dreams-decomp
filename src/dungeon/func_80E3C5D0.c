#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175DD0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
} S_80175DD0_0;   /* arg2 in func_80175DD0 */

typedef struct S_80175DD0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 * unk_20;
    u8 pad_24[0x1C];
    s16 unk_40;
} S_80175DD0_1;   /* object in func_80175DD0 */

typedef struct S_80175DD0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80175DD0_2;   /* object_data in func_80175DD0 */

typedef struct S_80175DD0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_80175DD0_3;   /* coords in func_80175DD0 */

typedef struct S_80175DD0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175DD0_4;   /* arg1 in func_80175DD0 */

typedef struct S_80175DD0_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175DD0_5;   /* arg0 in func_80175DD0 */



extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_80047784();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80175C60;
extern s32 D_80175D74;

void func_80175DD0(void *arg0, S_80175DD0_4 *arg1, S_80175DD0_0 *arg2, s16 arg3) {
    u16 position[3];
    u16 angle;
    s32 table_offset;
    S_80175DD0_3 *coords;
    S_80175DD0_2 *object_data;
    S_80175DD0_1 *object;

    if (func_8003DE58(arg2->unk_08, arg2, position, arg3) != 0) {
        object = func_8003FD64(0x300, (u8 *)arg0 - 0x20);
        if ((object != NULL) &&
            ((object_data = object->unk_0C,
              coords = object->unk_08,
              object->unk_10 = &D_80175C60,
              object_data->unk_1E = 0x400,
              object_data->unk_1C = 0x400,
              object_data->unk_0C = 0x808080,
              object_data->unk_28 = arg2->unk_28,
              coords->unk_02 = arg1->unk_02 + position[0],
              coords->unk_06 = arg1->unk_06 + position[1],
              coords->unk_0A = arg1->unk_0A + position[2],
              table_offset = (((S_80175DD0_5 *)arg0)->unk_2A >> 8) & 0xE,
              coords->unk_0E = *(u16 *)(&D_8006CCD8 + table_offset),
              coords->unk_12 = *(u16 *)(&D_8006CCE8 + table_offset),
              object->unk_40 = 0x10,
              object->unk_20 = (s16 *)((u8 *)arg0 + 0x2A),
              func_80047784(object_data, 0x45, 0, coords),
              func_8004491C(object, &D_80175D74),
              angle = ((((D_80083228 + *object->unk_20 + 0x100) >> 9) & 7) + 2) << 9,
              object_data->unk_18 = angle,
              angle == 0x400) ||
             (angle == 0xC00))) {
            object_data->unk_18 = angle + 0x100;
        }
    }
}
