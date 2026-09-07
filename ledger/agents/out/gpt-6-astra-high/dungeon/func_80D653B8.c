#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80D653B8_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80D653B8_0;   /* work in func_80D653B8 */

typedef struct S_80D653B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D653B8_1;   /* linked in func_80D653B8 */

typedef struct S_80D653B8_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80D653B8_2;   /* object_data in func_80D653B8 */

typedef struct S_80D653B8_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80D653B8_3;   /* arg3 in func_80D653B8 */

typedef struct S_80D653B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D653B8_4;   /* position in func_80D653B8 */

typedef struct S_80D653B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_80D653B8_5;   /* arg1 in func_80D653B8 */



typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80045340(void);
extern void func_80047784();

extern s16 D_80083228[];
extern u8 D_80083498[];
extern u8 D_800D6FEC[];
extern u8 D_800E23D0[];

/* Creates an object from a template, selects its direction, and positions it at the anchor. */
void func_80D653B8(void *unused, S_80D653B8_5 *anchor, Block16 *object_template,
                   S_80D653B8_3 *facing_source, s32 initial_value)
{
    Block16 *copy_end;
    void *object;
    S_80D653B8_2 *object_data;
    Block16 *copy_dst;
    Block16 *copy_src;
    S_80D653B8_4 *position;
    S_80D653B8_0 *object_work;

    (void)unused;
    object = func_8003FD64(0x112, D_80083498);
    if (object != NULL) {
        copy_src = object_template;
        object_work = (u8 *)object + 0x20;
        object_work->unk_96 = initial_value;
        object_work->unk_AA = initial_value;
        ((S_80D653B8_1 *)object)->unk_10 = D_800D6FEC;
        object_work->unk_B0 = anchor;
        object_data = ((S_80D653B8_1 *)object)->unk_0C;
        copy_end = copy_src + 3;
        copy_dst = (Block16 *)object_data;
        do {
            *copy_dst = *copy_src;
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);

        object_data->unk_1E = 0x1000;
        object_data->unk_1C = 0x1000;
        object_data->unk_0E = 0x80;
        object_data->unk_0D = 0x80;
        object_data->unk_0C = 0x80;
        object_data->unk_10 = 0x20;
        object_data->unk_12 = 0xFF80;
        object_data->unk_06 = -6;
        object_data->unk_14 |= 0xC;
        func_8004491C(object, func_80045340, copy_src, copy_dst);

        {
            u8 *direction_table = D_800E23D0;

            object_data->unk_2C = direction_table;
            func_80047784(object_data,
                direction_table[((D_80083228[0] + facing_source->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        position = ((S_80D653B8_1 *)object)->unk_08;
        position->unk_02 = anchor->unk_02;
        position->unk_06 = anchor->unk_06;
        position->unk_0A =
            anchor->unk_0A + anchor->unk_16;
    }
}
