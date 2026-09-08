#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801714B0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801714B0_0;   /* entity in func_801714B0 */

typedef struct S_801714B0_1 {
    u8 pad_00[0x94];
    s16 unk_94;
} S_801714B0_1;   /* arg0 in func_801714B0 */




extern s16 D_80083228;
extern u8 D_8006CCF8[];
extern void *D_80174CDC[3];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);

void func_801714B0(S_801714B0_1 *arg0, void *arg1, Rec_D_80082E80 *arg2)
{
    S_801714B0_0 *entity;
    u8 *table;
    s16 calculated_direction;
    s32 direction;

    entity = (u8 *)D_80174CDC[0] + 0x20;
    func_800478B8(arg2);
    if (D_80174CDC[0] != 0) {
        calculated_direction =
            ((D_80083228 + entity->unk_2A + 0x100) >> 9) & 7;
        direction = calculated_direction;

        if (arg0->unk_94 != direction) {
            func_80047738(arg2,
                arg2->unk_2C.as_pu8[direction],
                arg2->unk_04.as_s8);
            arg0->unk_94 = calculated_direction;
        }

        table = D_8006CCF8;
        if (table[direction] != 0) {
            arg2->unk_14.at00_u16.v |= 1;
        } else {
            arg2->unk_14.at00_u16.v &= 0xFFFE;
        }
    }
}
