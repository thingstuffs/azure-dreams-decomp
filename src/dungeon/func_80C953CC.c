#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Copy12 {
    u8 bytes[12];
} Copy12;

typedef struct Item {
    u8 pad[0x12];
    u8 kind;
    u8 pad2;
} Item;

extern Item D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170838[7];
extern u8 D_80170920[];
extern u8 D_8017102C[];
extern u8 D_801752B4[8];
extern Copy12 D_8017539C;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_8017087C(void *, void *, void *);

void func_80172BCC(u8 *work, u8 *position, u8 *entity, u8 *actor)
{
    u8 *part;
    s32 alternate = 0;
    static void *const jt_keep[] = {
        &&alternate_e, &&alternate_b, &&alternate_8,
        &&no_part, &&part_8, &&part_b, &&part_e
    };

    (void)jt_keep;

    switch (FIELD(work, u8, 0x9B)) {
    case 0:
        if (FIELD(actor, s32, 0x1C) & 0x2000) {
            u32 part_index = (FIELD(actor, u16, 0x46) & 0x3FFF) - 1;

            if (part_index >= 7) {
                goto no_part;
            }
            goto *D_80170838[part_index];

alternate_e:
            alternate = 1;
            goto part_e;
alternate_b:
            alternate = 1;
            goto part_b;
alternate_8:
            alternate = 1;
            goto part_8;
        } else {
            switch (FIELD(actor, u16, 0x46) & 0x3FFF) {
            case 1:
                goto part_8;
            case 2:
                goto part_b;
            case 3:
                goto part_e;
            default:
                goto no_part;
            }
        }

part_e:
        part = actor + 0xE;
        goto part_ready;
part_b:
        part = actor + 0xB;
        goto part_ready;
part_8:
        part = actor + 8;
        goto part_ready;
no_part:
        part = 0;
part_ready:
        if (*part != 0) {
            void *ptr;
            u8 *linked;

            (*(volatile u16 *)((u8 *)work + 0x98)) &= 0xFF7F;
            if ((s8)alternate) {
                FIELD(actor, void *, 0x60) = ptr = D_800814A8;
                linked = *(u8 **)((u8 *)ptr - 0x14);
                FIELD(actor, u8, 0x72) = FIELD(linked, u8, 0x24);
                FIELD(actor, u8, 0x73) = FIELD(linked, u8, 0x25);
            } else if (D_8006DE24[*part].kind == 2) {
                if ((ptr = FIELD(actor, void *, 0x60)) != 0) {
                    linked = *(u8 **)((u8 *)ptr - 0x14);
                    FIELD(actor, u8, 0x72) = FIELD(linked, u8, 0x24);
                    FIELD(actor, u8, 0x73) = FIELD(linked, u8, 0x25);
                }
            } else {
                s32 x;
                s32 y;

                do {
                    FIELD(actor, void *, 0x60) =
                        func_800A05A4(actor, FIELD(entity, u8, 0x24),
                                      FIELD(entity, u8, 0x25),
                                      FIELD(actor, s16, 0x2A), 0x10);
                } while (0);
                x = FIELD(actor, s8, 0x72);
                y = FIELD(actor, s8, 0x73);
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                FIELD(actor, u8, 0x72) = x;
                FIELD(actor, u8, 0x73) = y;
            }

            if (func_800A94A0(actor, part, alternate, work + 0x98) != 0) {
                FIELD(work, u8, 0x9B)++;
            }
        } else {
            void *linked;

            FIELD(position, s32, 0x14) = 0;
            FIELD(position, s32, 0x10) = 0;
            FIELD(position, s32, 0x0C) = 0;
            func_800A2B04(position, FIELD(entity, u8, 0x24),
                          FIELD(entity, u8, 0x25));
            linked = D_800814A8;
            D_8008346C = 0;
            FIELD(linked, u16, 0xA6)--;
            func_800A4ACC(actor);
            FIELD(actor, u8, 0x6D)--;
            FIELD(work, void *, 0x8C) = D_8017102C;
            FIELD(actor, u8, 0x73) = 0;
            FIELD(actor, u8, 0x72) = 0;
            FIELD(actor, u16, 0x46) &= 0x7FFF;
        }
        break;

    case 1:
        if (func_8003F270() != 0) {
            FIELD(entity, u16, 0x14) |= 0x800;
            break;
        }

        FIELD(entity, u16, 0x14) &= 0xF7FF;
        FIELD(work, u8, 0x9B)++;
        actor = func_8003FC64(0x212);
        if (actor != 0) {
            u8 *transform;
            u8 *node;
            u8 *model;

            func_8017087C(actor, work, position);
            transform = actor + 0x20;
            FIELD(transform, s16, 0x24) = 10;
            FIELD(transform, s16, 0x26) = 10;
            node = FIELD(actor, u8 *, 8);
            FIELD(actor, void *, 0x10) = D_80170920;
            FIELD(node, u16, 0x0A) -= 0x1E;
            model = FIELD(actor, u8 *, 0x0C);
            FIELD(model, s16, 0x10) = 0x60;
            FIELD(model, s16, 6) = 6;
            FIELD(model, s16, 0x1E) = 0;
            FIELD(model, s16, 0x1C) = 0;
            FIELD(model, u8, 0x0E) = 0;
            FIELD(model, u8, 0x0D) = 0;
            FIELD(model, u8, 0x0C) = 0;
            *(Copy12 *)(actor + 0x9A) = D_8017539C;
            FIELD(model, void *, 8) = actor + 0x9A;
        }
        func_800A56E0(0x703);
        break;

    case 2:
        if ((FIELD(entity, s8, 4) == 5 &&
             (FIELD(entity, u16, 0x14) & 0x1000)) ||
            (FIELD(entity, u16, 0x14) & 0xE000)) {
            FIELD(work, u16, 0x96) = 0x20;
            FIELD(work, u16, 0x98) |= 0x80;
            FIELD(work, u8, 0x9B)++;
        }
        break;

    case 3:
        part = (u8 *)&D_8008346C - 0x0C;
        if (FIELD(part, s32, 0x0C) == 0) {
            FIELD(work, u16, 0x96) = 0;
        }
        if (!(FIELD(entity, u16, 0x14) & 0xE000)) {
            break;
        }

        FIELD(position, s32, 0x14) = 0;
        FIELD(position, s32, 0x10) = 0;
        FIELD(position, s32, 0x0C) = 0;
        func_800A2B04(position, FIELD(entity, u8, 0x24),
                      FIELD(entity, u8, 0x25));
        if (FIELD(entity, void *, 0x2C) != D_801752B4) {
            s32 index;

            FIELD(entity, void *, 0x2C) = D_801752B4;
            index = (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9;
            func_80047784(entity, D_801752B4[index & 7], 0);
        }
        if (FIELD(part, s32, 0x0C) != 0) {
            break;
        }

        FIELD(part, u16, 0x0A)--;
        FIELD(work, void *, 0x8C) = D_8017102C;
        func_800A4ACC(actor);
        FIELD(actor, u8, 0x73) = 0;
        FIELD(actor, u8, 0x72) = 0;
        FIELD(actor, u8, 0x6D)--;
        FIELD(actor, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}