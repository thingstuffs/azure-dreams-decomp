#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

    switch (FIELD(arg0, u8, 0x9B)) {
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
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) &= 0x9FFF;

state_1:
    count = FIELD(arg0, s16, 0x96);
    if (count == 0 || count == 7) {
        s16 i;

        if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
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
            ASM_KEEP_NV(object);
            {
                register s32 ry ASM_REG("$16");
                s32 shifted_ry;
                register s32 rx ASM_REG("$17");
                s32 shifted_rx;
                s32 rz;
                s32 position_z;
                register s32 new_y ASM_REG("$2");
                register s32 position_x ASM_REG("$3");
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
                FIELD(motion, s16, 0x96) = 0x28 - FIELD(arg0, u16, 0x96);
                FIELD(motion, u8, 0x9B) = 0;
                render = FIELD(object, u8 *, 0x0C);
                FIELD(object, void *, 0x10) = D_80171040;

                src = arg2;
                dst = render;
                end = (u8 *)arg2 + 0x30;
                do {
                    *(Copy16 *)dst = *(Copy16 *)src;
                    src += 0x10;
                    dst += 0x10;
                } while (src != end);

                FIELD(render, u16, 0x14) &= 0xFFFC;
                func_8004491C(object, &D_80045340);
                animation = D_8017541C[0];
                FIELD(render, u8 *, 0x2C) = D_8017541C;
                func_80047784(render, animation, 0);

                position = FIELD(object, u8 *, 0x08);
                FIELD(position, u16, 0x02) = FIELD(arg1, u16, 0x02);
                FIELD(position, u16, 0x06) = FIELD(arg1, u16, 0x06);
                FIELD(position, u16, 0x0A) = FIELD(arg1, u16, 0x0A);

                map = FIELD(arg0, void *, -0x14);
                if (func_8003DF74(FIELD(map, void *, 0x08), map, &delta, 1)) {
                    FIELD(position, u16, 0x02) += delta.x;
                    FIELD(position, u16, 0x06) += delta.y;
                    FIELD(position, u16, 0x0A) += delta.z;
                }

                rx = func_80069EF8() & 0x1F;
                rx -= 0x10;
                ry = func_80069EF8() & 0x1F;
                ry -= 0x10;
                position_x = FIELD(position, u16, 0x02);
                position_x += rx;
                new_y = FIELD(position, u16, 0x06) + ry;
                FIELD(position, u16, 0x02) = position_x;
                ASM_KEEP(new_y);
                FIELD(position, u16, 0x06) = new_y;
                rz = func_80069EF8() & 0x1F;
                shifted_rx = (s32)(rx << 16) >> 4;
                shifted_ry = (s32)(ry << 16) >> 4;
                position_z = FIELD(position, u16, 0x0A);
                position_z -= 0x14;
                position_z += rz;
                FIELD(position, u16, 0x0A) = position_z;
                FIELD(motion, s32, 0xA4) = shifted_rx;
                FIELD(motion, s32, 0xA8) = shifted_ry;

                table_off = (FIELD(arg3, u16, 0x2A) >> 7) & 0x1C;
                FIELD(motion, s32, 0xA4) += (s32)((TableEntry *)((u8 *)entries + table_off))->x << 19;
                table_off = (FIELD(arg3, u16, 0x2A) >> 7) & 0x1C;
                FIELD(motion, s32, 0xA8) += (u32)((TableEntry *)((u8 *)entries + table_off))->y << 19;
                FIELD(motion, s32, 0xAC) = -((func_80069EF8() & 0x7FFF) * 2);
                FIELD(motion, s32, 0xB0) = 0x1000;
                FIELD(render, s16, 0x1E) = 0x1000;
                FIELD(render, s16, 0x1C) = 0x1000;
                FIELD(render, u8, 0x0E) = 0x80;
                FIELD(render, u8, 0x0D) = 0x80;
                FIELD(render, u8, 0x0C) = 0x80;
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
            ASM_KEEP_NV(object);
            {
                register s32 ry ASM_REG("$16");
                s32 shifted_ry;
                register s32 rx ASM_REG("$17");
                s32 shifted_rx;
                s32 rz;
                s32 position_z;
                register s32 new_y ASM_REG("$2");
                register s32 position_x ASM_REG("$3");
                u8 *position;
                u8 *motion;
                u8 *render;
                void *map;
                u32 table_off;

                motion = (u8 *)object + 0x20;
                FIELD(motion, s16, 0x24) = 0x19 - FIELD(arg0, u16, 0x96);
                FIELD(object, s16, 0x20) = 0;
                FIELD(object, void *, 0x10) = D_8017142C;
                func_8004491C(object, &D_80045340);

                render = FIELD(object, u8 *, 0x0C);
                FIELD(render, u16, 0x14) |= 0x0C;
                FIELD(render, s16, 0x10) = 0x60;
                FIELD(render, u16, 0x14) |= 2;

                position = FIELD(object, u8 *, 0x08);
                FIELD(position, u16, 0x02) = FIELD(arg1, u16, 0x02);
                FIELD(position, u16, 0x06) = FIELD(arg1, u16, 0x06);
                FIELD(position, u16, 0x0A) = FIELD(arg1, u16, 0x0A);

                map = FIELD(arg0, void *, -0x14);
                if (func_8003DE58(FIELD(map, void *, 0x08), map, &delta, 1)) {
                    FIELD(position, u16, 0x02) += delta.x;
                    FIELD(position, u16, 0x06) += delta.y;
                    FIELD(position, u16, 0x0A) += delta.z;
                }

                rx = func_80069EF8() & 0x1F;
                rx -= 0x10;
                ry = func_80069EF8() & 0x1F;
                ry -= 0x10;
                position_x = FIELD(position, u16, 0x02);
                position_x += rx;
                new_y = FIELD(position, u16, 0x06) + ry;
                FIELD(position, u16, 0x02) = position_x;
                ASM_KEEP(new_y);
                FIELD(position, u16, 0x06) = new_y;
                rz = func_80069EF8() & 0x1F;
                shifted_rx = (s32)(rx << 16) >> 4;
                shifted_ry = (s32)(ry << 16) >> 4;
                position_z = FIELD(position, u16, 0x0A);
                position_z -= 0x14;
                position_z += rz;
                FIELD(position, u16, 0x0A) = position_z;
                FIELD(motion, s32, 0x60) = shifted_rx;
                FIELD(motion, s32, 0x64) = shifted_ry;

                table_off = (FIELD(arg3, u16, 0x2A) >> 7) & 0x1C;
                FIELD(motion, s32, 0x60) += (s32)((TableEntry *)((u8 *)entries + table_off))->x << 19;
                table_off = (FIELD(arg3, u16, 0x2A) >> 7) & 0x1C;
                FIELD(motion, s32, 0x64) += (u32)((TableEntry *)((u8 *)entries + table_off))->y << 19;
                FIELD(motion, s32, 0x68) = -((func_80069EF8() & 0x7FFF) * 2);
                FIELD(motion, s32, 0x74) = 0x400;
                FIELD(render, s16, 0x1C) = 0x800;
                FIELD(render, s16, 0x1E) = 0x800;
                FIELD(render, u8, 0x0D) = 0x80;
                FIELD(render, u8, 0x0C) = 0x80;
                FIELD(render, u8, 0x0E) = 0;
                FIELD(render, s16, 0x12) = 0x7DCF;
                FIELD(render, u16, 0x14) |= 0x100;
                func_8003DB94(render, &D_800DE870, 0);
            }
particle2_increment:
            i++;
            } while (i < 4);
        }
    }

    FIELD(arg0, u16, 0x96)++;
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        void *active;

        FIELD(arg0, u8, 0x9B)++;
        active = FIELD(arg3, void *, 0x60);
        if (active != 0) {
            func_800C857C(arg3, active);
        }
    }
    goto done;

state_2:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        s32 index;

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, u8 *, 0x2C) != D_801753BC) {
            FIELD(arg2, u8 *, 0x2C) = D_801753BC;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
            func_80047784(arg2, FIELD(arg2, u8 *, 0x2C)[index & 7], 0);
            FIELD(arg0, u16, 0x96) = 0x14;
            FIELD(arg0, u8, 0x9B)++;
        }
    }
    goto done;

state_3:
    {
        u16 old_count;

        old_count = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = old_count - 1;
        if ((s16)old_count <= 0 || (FIELD(arg2, u16, 0x14) & 0xE000)) {
            func_800AD594(arg3, 0x1000);
            FIELD(arg0, void *, 0x8C) = D_80171E20;
            D_8008346C = 0;
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
    }

done:
    return;
}
