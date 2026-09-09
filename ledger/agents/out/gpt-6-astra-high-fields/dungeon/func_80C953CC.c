#include "common.h"

typedef struct S_func_80C953CC_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_func_80C953CC_1;

typedef struct S_func_80C953CC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_80C953CC_2;

typedef struct S_func_80C953CC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void *unk_2C;
} S_func_80C953CC_3;

typedef struct S_func_80C953CC_4 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union {
        u8 u8;
        s8 s8;
    } unk_72;
    union {
        u8 u8;
        s8 s8;
    } unk_73;
} S_func_80C953CC_4;

typedef struct S_func_80C953CC_5 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_func_80C953CC_5;

typedef struct S_func_80C953CC_6 {
    u8 pad_00[0x24];
    s16 unk_24;
    s16 unk_26;
} S_func_80C953CC_6;

typedef struct S_func_80C953CC_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_80C953CC_7;

typedef struct S_func_80C953CC_8 {
    u8 pad_00[0x6];
    s16 unk_06;
    void *unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_func_80C953CC_8;

typedef struct S_func_80C953CC_9 {
    u8 unk_00;
    u8 pad_01[0x9];
    u16 unk_0A;
    s32 unk_0C;
} S_func_80C953CC_9;

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

/* Advance the actor's item action, spawn its effect, and restore its position when finished. */
void func_80172BCC(S_func_80C953CC_1 *work, S_func_80C953CC_2 *position, S_func_80C953CC_3 *entity, S_func_80C953CC_4 *actor)
{
    S_func_80C953CC_9 *part;
    s32 alternate = 0;
    static void *const part_labels[] = {
        &&alternate_e, &&alternate_b, &&alternate_8,
        &&no_part, &&part_8, &&part_b, &&part_e
    };

    (void)part_labels;

    switch (work->unk_9B) {
    case 0:
        if (actor->unk_1C & 0x2000) {
            u32 part_index = (actor->unk_46 & 0x3FFF) - 1;

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
            switch (actor->unk_46 & 0x3FFF) {
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
        part = (S_func_80C953CC_9 *)((u8 *)actor + 0xE);
        goto part_ready;
part_b:
        part = (S_func_80C953CC_9 *)((u8 *)actor + 0xB);
        goto part_ready;
part_8:
        part = (S_func_80C953CC_9 *)((u8 *)actor + 8);
        goto part_ready;
no_part:
        part = 0;
part_ready:
        if (part->unk_00 != 0) {
            void *target_actor;
            S_func_80C953CC_3 *target_entity;

            (*(volatile u16 *)((u8 *)work + 0x98)) &= 0xFF7F;
            if ((s8)alternate) {
                actor->unk_60 = target_actor = D_800814A8;
                target_entity = *(S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                actor->unk_72.u8 = target_entity->unk_24;
                actor->unk_73.u8 = target_entity->unk_25;
            } else if (D_8006DE24[part->unk_00].kind == 2) {
                if ((target_actor = actor->unk_60) != 0) {
                    target_entity = *(S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                    actor->unk_72.u8 = target_entity->unk_24;
                    actor->unk_73.u8 = target_entity->unk_25;
                }
            } else {
                s32 target_x;
                s32 target_y;

                do {
                    actor->unk_60 =
                        func_800A05A4(actor, entity->unk_24,
                                      entity->unk_25,
                                      actor->unk_2A, 0x10);
                } while (0);
                target_x = actor->unk_72.s8;
                target_y = actor->unk_73.s8;
                if (target_x < 0) {
                    target_x = -target_x;
                }
                if (target_y < 0) {
                    target_y = -target_y;
                }
                actor->unk_72.u8 = target_x;
                actor->unk_73.u8 = target_y;
            }

            if (func_800A94A0(actor, part, alternate, (u8 *)work + 0x98) != 0) {
                work->unk_9B++;
            }
        } else {
            S_func_80C953CC_5 *active_actor;

            position->unk_14 = 0;
            position->unk_10 = 0;
            position->unk_0C = 0;
            func_800A2B04(position, entity->unk_24,
                          entity->unk_25);
            active_actor = D_800814A8;
            D_8008346C = 0;
            (*(u16 *)((u8 *)active_actor + 0xA6))--;
            func_800A4ACC(actor);
            actor->unk_6D--;
            work->unk_8C = D_8017102C;
            actor->unk_73.u8 = 0;
            actor->unk_72.u8 = 0;
            actor->unk_46 &= 0x7FFF;
        }
        break;

    case 1:
        if (func_8003F270() != 0) {
            entity->unk_14 |= 0x800;
            break;
        }

        entity->unk_14 &= 0xF7FF;
        work->unk_9B++;
        actor = func_8003FC64(0x212);
        if (actor != 0) {
            S_func_80C953CC_6 *transform;
            S_func_80C953CC_7 *node;
            S_func_80C953CC_8 *model;

            func_8017087C(actor, work, position);
            transform = (S_func_80C953CC_6 *)((u8 *)actor + 0x20);
            transform->unk_24 = 10;
            transform->unk_26 = 10;
            node = actor->unk_08;
            actor->unk_10 = D_80170920;
            node->unk_0A -= 0x1E;
            model = actor->unk_0C;
            model->unk_10 = 0x60;
            model->unk_06 = 6;
            model->unk_1E = 0;
            model->unk_1C = 0;
            model->unk_0E = 0;
            model->unk_0D = 0;
            model->unk_0C = 0;
            *(Copy12 *)((u8 *)actor + 0x9A) = D_8017539C;
            model->unk_08 = (u8 *)actor + 0x9A;
        }
        func_800A56E0(0x703);
        break;

    case 2:
        if ((entity->unk_04 == 5 &&
             (entity->unk_14 & 0x1000)) ||
            (entity->unk_14 & 0xE000)) {
            work->unk_96 = 0x20;
            work->unk_98 |= 0x80;
            work->unk_9B++;
        }
        break;

    case 3:
        part = (S_func_80C953CC_9 *)((u8 *)&D_8008346C - 0x0C);
        if (part->unk_0C == 0) {
            work->unk_96 = 0;
        }
        if (!(entity->unk_14 & 0xE000)) {
            break;
        }

        position->unk_14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, entity->unk_24,
                      entity->unk_25);
        if (entity->unk_2C != D_801752B4) {
            s32 direction;

            (*(void **)((u8 *)entity + 0x2C)) = D_801752B4;
            direction = (D_80083228 + actor->unk_2A + 0x100) >> 9;
            func_80047784(entity, D_801752B4[direction & 7], 0);
        }
        if (part->unk_0C != 0) {
            break;
        }

        part->unk_0A--;
        work->unk_8C = D_8017102C;
        func_800A4ACC(actor);
        actor->unk_73.u8 = 0;
        actor->unk_72.u8 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}