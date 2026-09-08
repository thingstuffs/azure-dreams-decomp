#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_801717D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801717D0_0;   /* self in func_801717D0 */


typedef struct S_801717D0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801717D0_2;   /* counter_base in func_801717D0 */

typedef struct S_801717D0_3 {
    u8 pad_00[0x98];
    union { s32 s32; u16 u16; } unk_98;   /* accessed as both */
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801717D0_3;   /* player in func_801717D0 */


typedef struct S_801717D0_5 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 unk_13;
} S_801717D0_5;   /* entry in func_801717D0 */

typedef struct S_801717D0_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801717D0_6;   /* call_arg2 in func_801717D0 */



extern u8 D_8006DE24[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 *D_800E3D7C;

extern void func_80047784(void *, u8, s32);
extern s32 func_800A05A4(void *, u8, u8, s16, u8);
extern s32 func_800A2B5C(void *);
extern void func_800A4ACC(void *);
extern s32 func_800A6D30(void);
extern void func_800C77D0(void *, s32, s32, s32);

void func_801717D0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3, s32 arg4)
{
    register s32 call_arg1 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *call_arg2 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *call_arg3 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *self;
    u8 *player;
    u8 *slot;
    u8 *counter_base;
    u8 *table_base;
    u8 *entry;
    volatile u16 *field_46;
    u16 counter;
    s32 active;
    s32 index;
    s32 table_index;
    register s32 field_14 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    call_arg1 = arg1;
    call_arg2 = arg2;
    call_arg3 = arg3;
    active = 0;
    self = arg0;
    ASM_KEEP(call_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(call_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_801717D0_0 *)self)->unk_71 &= 0x7F;

    if (((S_801717D0_0 *)self)->unk_1C & 0x2000) {
        if ((((S_801717D0_0 *)self)->unk_46 & 0x3FFF) >= 5) {
            active = 1;
            if (((Rec_D_800E3D7C *)D_800E3D7C)->unk_A4.at02_u16.v == 2) {
                counter_base = (u8 *)&D_80083460;
                ASM_KEEP(counter_base);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                counter = ((S_801717D0_2 *)counter_base)->unk_0A;
                counter--;
                ((S_801717D0_2 *)counter_base)->unk_0A = counter;
            }

            player = D_800E3D7C;
            if ((((S_801717D0_3 *)player)->unk_98.s32 & 0x3000) == 0x2000 &&
                ((S_801717D0_3 *)player)->unk_A6 != active) {
                ((S_801717D0_3 *)player)->unk_A6 = active;
                ((S_801717D0_3 *)player)->unk_98.u16 |= 0x1000;
                counter_base = (u8 *)&D_80083460;
                ((S_801717D0_2 *)counter_base)->unk_0A++;
                goto process;
            }

            func_800A4ACC(self);
            ((S_801717D0_0 *)self)->unk_6D--;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = arg4;
            goto done;
        }
    }

    if (D_80083462 & 8) {
        goto done;
    }
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

    func_800C77D0(self - 0x20, call_arg1, 8, 0x300);
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

process:
    if (active == 0) {
        if (((S_801717D0_0 *)self)->unk_1C & 0x400) {
            field_14 = ((S_801717D0_0 *)self)->unk_14;
            if (field_14 >= 0) {
                field_14 |= 0x80000000;
                ((S_801717D0_0 *)self)->unk_14 = field_14;
                ((S_801717D0_0 *)self)->unk_2A.u += (func_800A6D30() & 7) << 9;
            }
        }

        field_46 = (volatile u16 *)(self + 0x46);
        if (!(*field_46 & 0x4000)) {
            index = *field_46 & 0x3FFF;
            table_index = index - 1;
            table_base = D_8006DE24;
            slot = self;
            slot += table_index * 3;
            table_index = slot[8];
            entry = table_base + table_index * 20;
            if (((S_801717D0_5 *)entry)->unk_12 == 2) {
                ((S_801717D0_0 *)self)->unk_60 =
                    func_800A05A4(self,
                                  ((S_801717D0_6 *)call_arg2)->unk_24,
                                  ((S_801717D0_6 *)call_arg2)->unk_25,
                                  ((S_801717D0_0 *)self)->unk_2A.s,
                                  ((S_801717D0_5 *)entry)->unk_13);
            }
        }
    }

    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0x12;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;

    if (call_arg3 != 0) {
        (*(u8 * *)((u8 *)call_arg2 + 0x2C)) = call_arg3;
        index = (D_80083228 + ((S_801717D0_0 *)self)->unk_2A.s + 0x100) >> 9;
        func_80047784(call_arg2, call_arg3[index & 7], 0);
        ASM_KEEP(call_arg3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }

    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ((S_801717D0_2 *)counter_base)->unk_0A++;

done:
    return;
}
