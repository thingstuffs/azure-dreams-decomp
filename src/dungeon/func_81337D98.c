#include "common.h"

typedef struct S_8016ED98_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016ED98_0;   /* state in func_8016ED98 */

typedef struct S_8016ED98_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_8016ED98_1;   /* object in func_8016ED98 */

typedef struct S_8016ED98_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016ED98_2;   /* D_800E3D7C + i * 4 in func_8016ED98 */



extern void func_8009FAC4(void);
extern void func_8016ECFC(void);
extern void func_80099FDC(void *);

extern s32 D_80083460;
extern u16 D_80013714[];
extern s32 D_80175D50;
extern s32 D_800E3D7C;

void func_8016ED98(void)
{
    s32 i;
    s32 value;
    S_8016ED98_1 *object;
    u8 *state;

    object = (void *)(D_80175D50 + 0x20);
    state = (u8 *)&D_80083460;
    ((S_8016ED98_0 *)state)->unk_0A = ((S_8016ED98_0 *)state)->unk_0A - 1;
    object->unk_46 &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4();
    func_8016ECFC();
    i = 0;
    do {
        value = ((S_8016ED98_2 *)(D_800E3D7C + i * 4))->unk_AC;
        if (value != 0) {
            func_80099FDC((void *)(value - 0x20));
        }
        i++;
    } while (i < 2);
}
