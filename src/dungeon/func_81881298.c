#include "common.h"

typedef struct S_80024A98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024A98_0;   /* node in func_80024A98 */

typedef struct S_80024A98_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024A98_1;   /* coords in func_80024A98 */

typedef struct S_80024A98_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024A98_2;   /* arg0 in func_80024A98 */

typedef struct S_80024A98_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024A98_3;   /* part in func_80024A98 */



extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern void func_800254C4();
extern s16 rand();

extern u8 D_80024A00[];
extern u8 D_80045340[];
extern u8 D_800DE938[];

void *func_80024A98(S_80024A98_2 *arg0)
{
    s16 angle;
    s32 i;
    S_80024A98_3 *part;
    S_80024A98_1 *coords;
    S_80024A98_0 *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        node->unk_10 = D_80024A00;
        func_8004491C(node, D_80045340);
        coords = node->unk_08;
        coords->unk_02 = arg0->unk_02;
        coords->unk_06 = arg0->unk_06;
        coords->unk_0A = arg0->unk_0A;
        part = node->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        part->unk_0C = 0x808080;
        func_8003DB94(part, D_800DE938, 0);
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        i = 0;
        angle = rand();
        do {
            func_800254C4(coords, angle, 0x10, 1);
            i++;
            angle += 0x100;
        } while (i < 0x10);
    }
    return node;
}
