#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

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

extern u16 D_80013714[];
extern s32 D_80175D50;

/* End the floor: clear the visible flags, run the two teardown passes and release both resident objects. */
void func_8016ED98(void)
{
    s32 i;
    s32 value;
    S_8016ED98_1 *object;

    object = (void *)(D_80175D50 + 0x20);
    dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
    object->unk_46 &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4();
    func_8016ECFC();
    i = 0;
    do {
        value = ((S_8016ED98_2 *)(((s32)D_800E3D7C) + i * 4))->unk_AC;
        if (value != 0) {
            func_80099FDC((void *)(value - 0x20));
        }
        i++;
    } while (i < 2);
}
