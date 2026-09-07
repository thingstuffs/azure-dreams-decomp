#include "common.h"

typedef struct S_80174BEC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174BEC_0_pre;   /* the 0x14 bytes before arg0 in func_80174BEC, addressed as arg0[-1] */

typedef struct S_80174BEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BEC_0;   /* arg0 in func_80174BEC */

typedef struct S_80174BEC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174BEC_1;   /* arg1 in func_80174BEC */

typedef struct S_80174BEC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174BEC_2;   /* arg2 in func_80174BEC */

typedef struct S_80174BEC_3 {
    u8 pad_00[0x24];
    s16 unk_24;
    u8 pad_26[0x3A];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
    u8 pad_78[0x1E];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80174BEC_3;   /* motion in func_80174BEC */

typedef struct S_80174BEC_4 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80174BEC_4;   /* object in func_80174BEC */

typedef struct S_80174BEC_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80174BEC_5;   /* render in func_80174BEC */

typedef struct S_80174BEC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174BEC_6;   /* position in func_80174BEC */

typedef struct S_80174BEC_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174BEC_7;   /* map in func_80174BEC */

typedef struct S_80174BEC_8 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
} S_80174BEC_8;   /* arg3 in func_80174BEC */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u;

typedef struct {
    s16 x;
    u16 y;
} TableEntry;

typedef struct {
    u32 words[4];
} Copy16;

typedef struct {
    u32 words[8];
} __attribute__((packed)) PackedTable;

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DE58(void *, void *, Vec3u *, s32);
extern s32 func_8003DF74(void *, void *, Vec3u *, s32);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern s32 func_80069EF8(void);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800C857C(void *, void *);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern s32 D_800DE870;
extern u8 D_80170854[];
extern u8 D_80171040[];
extern u8 D_8017142C[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
extern u8 D_8017541C[];

void func_80174BEC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    Vec3u delta;
    PackedTable table;
    s16 count;

    table = *(PackedTable *)D_80170854;

    switch (((S_80174BEC_0 *)arg0)->unk_9B) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        goto done;
    }

state_0:
    ((S_80174BEC_1 *)arg1)->unk_14 = 0;
    ((S_80174BEC_1 *)arg1)->unk_10 = 0;
    ((S_80174BEC_1 *)arg1)->unk_0C = 0;
    ((S_80174BEC_0 *)arg0)->unk_96.s = 0;
    ((S_80174BEC_0 *)arg0)->unk_9B++;
    ((S_80174BEC_2 *)arg2)->unk_14 &= 0x9FFF;

state_1:
    count = ((S_80174BEC_0 *)arg0)->unk_96.u;
    if (count == 0 || count == 7) {
        s16 i;

        if (!(((S_80174BEC_2 *)arg2)->unk_14 & 0x8000)) {
            func_800A56E0(0x80D);
        }

        i = 0;
        {
            TableEntry *entries;

            entries = (TableEntry *)&table;
            do {
            void *object;

            object = func_8003FD64(0x112, D_80083498);
            if (object == 0) goto particle1_increment;
            ASM_KEEP_NV(object);   /* MATCH pin: retail keeps a computation the compiler would drop */
            {
                s32 ry;
                s32 shifted_ry;
                register s32 rx ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
                s32 shifted_rx;
                s32 rz;
                s32 position_z;
                s32 new_y;
                s32 position_x;
                u8 *position;
                u8 *render;
                u8 *motion;
                u8 *src;
                u8 *dst;
                u8 *end;
                u8 animation;
                void *map;
                u32 table_off;

                motion = (u8 *)object + 0x20;
                ((S_80174BEC_3 *)motion)->unk_96 = 0x28 - ((S_80174BEC_0 *)arg0)->unk_96.s;
                ((S_80174BEC_3 *)motion)->unk_9B = 0;
                render = ((S_80174BEC_4 *)object)->unk_0C;
                ((S_80174BEC_4 *)object)->unk_10 = D_80171040;

                src = arg2;
                dst = render;
                end = (u8 *)arg2 + 0x30;
                do {
                    *(Copy16 *)dst = *(Copy16 *)src;
                    src += 0x10;
                    dst += 0x10;
                } while (src != end);

                ((S_80174BEC_5 *)render)->unk_14 &= 0xFFFC;
                func_8004491C(object, &D_80045340);
                animation = D_8017541C[0];
                ((S_80174BEC_5 *)render)->unk_2C = D_8017541C;
                func_80047784(render, animation, 0);

                position = ((S_80174BEC_4 *)object)->unk_08;
                ((S_80174BEC_6 *)position)->unk_02 = ((S_80174BEC_1 *)arg1)->unk_02;
                ((S_80174BEC_6 *)position)->unk_06 = ((S_80174BEC_1 *)arg1)->unk_06;
                ((S_80174BEC_6 *)position)->unk_0A = ((S_80174BEC_1 *)arg1)->unk_0A;

                map = ((S_80174BEC_0_pre *)arg0)[-1].unk_00;
                if (func_8003DF74(((S_80174BEC_7 *)map)->unk_08, map, &delta, 1)) {
                    ((S_80174BEC_6 *)position)->unk_02 += delta.x;
                    ((S_80174BEC_6 *)position)->unk_06 += delta.y;
                    ((S_80174BEC_6 *)position)->unk_0A += delta.z;
                }

                rx = func_80069EF8() & 0x1F;
                rx -= 0x10;
                ry = func_80069EF8() & 0x1F;
                ry -= 0x10;
                position_x = ((S_80174BEC_6 *)position)->unk_02;
                position_x += rx;
                new_y = ((S_80174BEC_6 *)position)->unk_06 + ry;
                ((S_80174BEC_6 *)position)->unk_02 = position_x;
                ASM_KEEP(new_y);   /* MATCH pin: retail register colouring depends on it */
                ((S_80174BEC_6 *)position)->unk_06 = new_y;
                rz = func_80069EF8() & 0x1F;
                shifted_rx = (s32)(rx << 16) >> 4;
                shifted_ry = (s32)(ry << 16) >> 4;
                position_z = ((S_80174BEC_6 *)position)->unk_0A;
                position_z -= 0x14;
                position_z += rz;
                ((S_80174BEC_6 *)position)->unk_0A = position_z;
                ((S_80174BEC_3 *)motion)->unk_A4 = shifted_rx;
                ((S_80174BEC_3 *)motion)->unk_A8 = shifted_ry;

                table_off = (((S_80174BEC_8 *)arg3)->unk_2A.s >> 7) & 0x1C;
                ((S_80174BEC_3 *)motion)->unk_A4 += (s32)((TableEntry *)((u8 *)entries + table_off))->x << 19;
                table_off = (((S_80174BEC_8 *)arg3)->unk_2A.s >> 7) & 0x1C;
                ((S_80174BEC_3 *)motion)->unk_A8 += (u32)((TableEntry *)((u8 *)entries + table_off))->y << 19;
                ((S_80174BEC_3 *)motion)->unk_AC = -((func_80069EF8() & 0x7FFF) * 2);
                ((S_80174BEC_3 *)motion)->unk_B0 = 0x1000;
                ((S_80174BEC_5 *)render)->unk_1E = 0x1000;
                ((S_80174BEC_5 *)render)->unk_1C = 0x1000;
                ((S_80174BEC_5 *)render)->unk_0E = 0x80;
                ((S_80174BEC_5 *)render)->unk_0D = 0x80;
                ((S_80174BEC_5 *)render)->unk_0C = 0x80;
            }
particle1_increment:
            i++;
            } while (i < 5);
        }

        i = 0;
        {
            TableEntry *entries;

            entries = (TableEntry *)&table;
            do {
            void *object;

            object = func_8003FC64(0x212);
            if (object == 0) goto particle2_increment;
            ASM_KEEP_NV(object);   /* MATCH pin: retail keeps a computation the compiler would drop */
            {
                s32 ry;
                s32 shifted_ry;
                register s32 rx ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
                s32 shifted_rx;
                s32 rz;
                s32 position_z;
                s32 new_y;
                s32 position_x;
                u8 *position;
                u8 *motion;
                u8 *render;
                void *map;
                u32 table_off;

                motion = (u8 *)object + 0x20;
                ((S_80174BEC_3 *)motion)->unk_24 = 0x19 - ((S_80174BEC_0 *)arg0)->unk_96.s;
                ((S_80174BEC_4 *)object)->unk_20 = 0;
                ((S_80174BEC_4 *)object)->unk_10 = D_8017142C;
                func_8004491C(object, &D_80045340);

                render = ((S_80174BEC_4 *)object)->unk_0C;
                ((S_80174BEC_5 *)render)->unk_14 |= 0x0C;
                ((S_80174BEC_5 *)render)->unk_10 = 0x60;
                ((S_80174BEC_5 *)render)->unk_14 |= 2;

                position = ((S_80174BEC_4 *)object)->unk_08;
                ((S_80174BEC_6 *)position)->unk_02 = ((S_80174BEC_1 *)arg1)->unk_02;
                ((S_80174BEC_6 *)position)->unk_06 = ((S_80174BEC_1 *)arg1)->unk_06;
                ((S_80174BEC_6 *)position)->unk_0A = ((S_80174BEC_1 *)arg1)->unk_0A;

                map = ((S_80174BEC_0_pre *)arg0)[-1].unk_00;
                if (func_8003DE58(((S_80174BEC_7 *)map)->unk_08, map, &delta, 1)) {
                    ((S_80174BEC_6 *)position)->unk_02 += delta.x;
                    ((S_80174BEC_6 *)position)->unk_06 += delta.y;
                    ((S_80174BEC_6 *)position)->unk_0A += delta.z;
                }

                rx = func_80069EF8() & 0x1F;
                rx -= 0x10;
                ry = func_80069EF8() & 0x1F;
                ry -= 0x10;
                position_x = ((S_80174BEC_6 *)position)->unk_02;
                position_x += rx;
                new_y = ((S_80174BEC_6 *)position)->unk_06 + ry;
                ((S_80174BEC_6 *)position)->unk_02 = position_x;
                ASM_KEEP(new_y);   /* MATCH pin: retail register colouring depends on it */
                ((S_80174BEC_6 *)position)->unk_06 = new_y;
                rz = func_80069EF8() & 0x1F;
                shifted_rx = (s32)(rx << 16) >> 4;
                shifted_ry = (s32)(ry << 16) >> 4;
                position_z = ((S_80174BEC_6 *)position)->unk_0A;
                position_z -= 0x14;
                position_z += rz;
                ((S_80174BEC_6 *)position)->unk_0A = position_z;
                ((S_80174BEC_3 *)motion)->unk_60 = shifted_rx;
                ((S_80174BEC_3 *)motion)->unk_64 = shifted_ry;

                table_off = (((S_80174BEC_8 *)arg3)->unk_2A.s >> 7) & 0x1C;
                ((S_80174BEC_3 *)motion)->unk_60 += (s32)((TableEntry *)((u8 *)entries + table_off))->x << 19;
                table_off = (((S_80174BEC_8 *)arg3)->unk_2A.s >> 7) & 0x1C;
                ((S_80174BEC_3 *)motion)->unk_64 += (u32)((TableEntry *)((u8 *)entries + table_off))->y << 19;
                ((S_80174BEC_3 *)motion)->unk_68 = -((func_80069EF8() & 0x7FFF) * 2);
                ((S_80174BEC_3 *)motion)->unk_74 = 0x400;
                ((S_80174BEC_5 *)render)->unk_1C = 0x800;
                ((S_80174BEC_5 *)render)->unk_1E = 0x800;
                ((S_80174BEC_5 *)render)->unk_0D = 0x80;
                ((S_80174BEC_5 *)render)->unk_0C = 0x80;
                ((S_80174BEC_5 *)render)->unk_0E = 0;
                ((S_80174BEC_5 *)render)->unk_12 = 0x7DCF;
                ((S_80174BEC_5 *)render)->unk_14 |= 0x100;
                func_8003DB94(render, &D_800DE870, 0);
            }
particle2_increment:
            i++;
            } while (i < 4);
        }
    }

    ((S_80174BEC_0 *)arg0)->unk_96.s++;
    if (((S_80174BEC_2 *)arg2)->unk_14 & 0xE000) {
        void *active;

        ((S_80174BEC_0 *)arg0)->unk_9B++;
        active = ((S_80174BEC_8 *)arg3)->unk_60;
        if (active != 0) {
            func_800C857C(arg3, active);
        }
    }
    goto done;

state_2:
    if (((S_80174BEC_2 *)arg2)->unk_14 & 0xE000) {
        s32 index;

        ((S_80174BEC_1 *)arg1)->unk_14 = 0;
        ((S_80174BEC_1 *)arg1)->unk_10 = 0;
        ((S_80174BEC_1 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80174BEC_2 *)arg2)->unk_24, ((S_80174BEC_2 *)arg2)->unk_25);
        if (((S_80174BEC_2 *)arg2)->unk_2C != D_801753BC) {
            ((S_80174BEC_2 *)arg2)->unk_2C = D_801753BC;
            ((S_80174BEC_2 *)arg2)->unk_14 &= 0xF7FF;
            index = (D_80083228 + ((S_80174BEC_8 *)arg3)->unk_2A.u + 0x100) >> 9;
            func_80047784(arg2, ((S_80174BEC_2 *)arg2)->unk_2C[index & 7], 0);
            ((S_80174BEC_0 *)arg0)->unk_96.s = 0x14;
            ((S_80174BEC_0 *)arg0)->unk_9B++;
        }
    }
    goto done;

state_3:
    {
        u16 old_count;

        old_count = ((S_80174BEC_0 *)arg0)->unk_96.s;
        ((S_80174BEC_0 *)arg0)->unk_96.s = old_count - 1;
        if ((s16)old_count <= 0 || (((S_80174BEC_2 *)arg2)->unk_14 & 0xE000)) {
            func_800AD594(arg3, 0x1000);
            ((S_80174BEC_0 *)arg0)->unk_8C = D_80171E20;
            D_8008346C = 0;
            (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        }
    }

done:
    return;
}
