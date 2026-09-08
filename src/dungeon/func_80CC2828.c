#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80093E74(void *, void *, void *, void *);
extern void func_8009A028(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A18E8(u8, s32);
extern u8 func_800A1BD0(void *);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80175DA4(void *);
extern void func_8017614C(void) __attribute__((noreturn));

extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 *D_800E3D7C;
extern u8 D_80173B98;


typedef struct S_80176028_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_80176028_0;   /* arg2 in func_80176028 */


typedef struct S_80176028_2 {
    u8 pad_00[0x8A];
    u16 unk_8A;
} S_80176028_2;   /* value_map in func_80176028 */

typedef struct S_80176028_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80176028_3;   /* counter in func_80176028 */

typedef struct S_80176028_4 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_80176028_4;   /* actor in func_80176028 */

typedef struct S_80176028_5 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x26];
    u16 unk_46;
} S_80176028_5;   /* work in func_80176028 */

typedef struct S_80176028_6 {
    u8 pad_00[0x8C];
    void * unk_8C;
} S_80176028_6;   /* owner in func_80176028 */

void func_80176028(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register u8 *owner = arg0;
    u8 *work = arg3;
    register s32 state = owner[0x9B];
    register u8 *actor = *(u8 **)(work + 0x60);
    register s32 type_check ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        type_check = 3;
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    {
        return;
    }

state_0:
    {
        if ((((S_80176028_0 *)arg2)->unk_04 == type_check) &&
            (((S_80176028_0 *)arg2)->unk_14 & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (((S_80176028_0 *)arg2)->unk_14 & 0xE000) {
            func_8017614C();
            return;
        }
        goto done;
    }

state_1:
    {
        u8 *saved_actor;
        u8 *counter;
        u8 *value_map;
        u16 saved_value;
        u8 value;
        register u8 *table1;
        register u8 *table2;

        saved_value = ((Rec_D_800E3D7C *)D_800E3D7C)->unk_8A.as_u16;
        saved_actor = ((Rec_D_800E3D7C *)D_800E3D7C)->unk_60.as_pu8;
        value = func_800A1BD0(actor);
        table1 = D_80083780;
        table2 = D_80082E80;
        value_map = D_800E3D7C;
        owner[0xA9] = value;
        ASM_KEEP_DEP_NV(actor, value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_JALDELAY_PIN(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((Rec_D_800E3D7C *)D_800E3D7C)->unk_60.as_pu8 = actor;
        ((S_80176028_2 *)value_map)->unk_8A = value;
        func_80093E74(D_800E3D7C, table1, table2, D_800E3D7C);
        (*(u8 * *)((u8 *)D_800E3D7C + (0x60))) = saved_actor;
        ((Rec_D_800E3D7C *)D_800E3D7C)->unk_8A.as_u16 = saved_value;
        counter = (u8 *)&D_80083460;
        ((S_80176028_3 *)counter)->unk_0A--;
        owner[0x9B]++;
        return;
    }

state_2:
    {
        u8 *map;
        u8 *tile;
        u8 x;
        u8 y;
        s32 mode;

        if (!(((S_80176028_4 *)actor)->unk_1C & 0x00800000)) {
            goto done;
        }

        map = D_800E3D7C;
        *(u32 *)(map + 0xAC + owner[0xA9] * 4) = 0;
        *(u32 *)(map + 0xD0 + owner[0xA9] * 4) = 0;
        func_800A18E8(actor[0x13], 3);
        tile = *(u8 **)(actor - 0x14);
        x = tile[0x24];
        y = tile[0x25];
        mode = (((S_80176028_4 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000;
        func_8009A3D0(x, y, mode);
        func_8009A028(actor);
        (*(u16 *)((u8 *)actor + (-2))) |= 0x8000;
        D_800814A0 |= 0x8000;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
            u8 *map_value;
            s32 owner_index;

            map_value = D_800E3D7C;
            owner_index = owner[0xA9];
            map_value += owner_index;
            map_value[0xFA] = state;
        }
        owner[0xA8] = owner[0xA9] + 1;
        owner[0x9B]++;
        return;
    }

state_3:
    {
        register u8 *entry = arg2;

        func_800AD594(work, 0x800);
        ((S_80176028_5 *)work)->unk_1C |= 0x2000;
        func_8009A3D0(entry[0x24], entry[0x25], 0x3000);
        func_8009A21C(entry[0x24], entry[0x25], 0x300);
        work[0x12] = state;
        func_80175DA4(*(void **)(work + 0x60));
        ((S_80176028_5 *)work)->unk_46 &= 0x7FFF;
        ((S_80176028_6 *)owner)->unk_8C = &D_80173B98;
        func_800A4ACC(work);
        work[0x6D]--;
    }

done:
    return;
}
