#include "common.h"

typedef struct SubA {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
} SubA;

typedef struct SubB {
    u8 pad0[6];
    s16 f6;
    void *f8;
    u32 fC;
    u8 pad10[4];
    u16 f14;
    u8 pad16[6];
    s16 f1C;
    s16 f1E;
} SubB;

typedef struct Obj {
    u8 pad0[8];
    SubA *subA;
    SubB *subB;
    void *state;
} Obj;

typedef struct Aux {
    void *f0;
    u8 pad4[6];
    s16 fA;
    u8 padC[2];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    u8 pad14[2];
    u16 f16;
    u8 pad18[2];
    u16 f1A;
    u8 pad1C[0xC];
    void *f28;
    void *f2C;
} Aux;

typedef struct D_80083780_t {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} D_80083780_t;

extern s32 func_8003FA44(s32);
extern Obj *func_8003FC64(s32);
extern void func_8004491C(Obj *, void *);
extern void func_800C77D0(Obj *, SubA *, s32, s16);
extern s32 func_8004A658(u8, u8);
extern void func_8003DB94(SubB *, void *, s32);
extern void *func_800BA110();
extern void *func_800BA1D0();
extern void *func_800BA224();
extern void func_800BA2A0(void);
extern void func_800BA308(void);
extern s32 func_800BA33C(s32);
extern void func_800B1768(s32, s32, s32, s32, s32, s32);
extern void func_800B1B10(void *, s32, s32, s32, s32, s32);

extern s32 D_80045340;
extern u8 D_80045C34[];
extern u8 D_80079444[];
extern void *D_800814A8;
extern s32 D_80083460;
extern D_80083780_t D_80083780;
extern u8 D_800B9A78[];
extern s16 D_800DCE66[5];
extern u8 D_800DDC40[];
extern u8 D_800DF368[];
extern u8 *D_800E3D7C[];



typedef struct S_800BA074_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800BA074_0;   /* current in func_800BA074 */

typedef struct S_800BA074_1 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800BA074_1;   /* page in func_800BA074 */

typedef struct S_800BA074_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    s32 unk_B0;
} S_800BA074_2;   /* ((S_800BA074_1 *)page)->unk_3D7C in func_800BA074 */

/* Creates three linked display objects for the selection and initializes their appearance. */
void *func_800BA074(u8 *selection_data) {
    Obj *objects[3];
    u8 *selection;
    D_80083780_t *layout;
    Obj **object_slot;
    s32 part_index;
    register u8 *global_page ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 last_part;

    selection = selection_data;

    if (func_8003FA44(3) == 0) {
        return 0;
    }

    part_index = 0;
    last_part = 2;
    layout = &D_80083780;
    global_page = (u8 *)0x800E0000;
    object_slot = objects;
loop:
    *object_slot = func_8003FC64(0x12);
    if (*object_slot != 0) {
        SubA *transform;
        SubB *sprite;

        (*object_slot)->state = D_800B9A78;
        if (part_index == last_part) {
            func_8004491C(objects[2], D_80045C34);
            goto after_call;
        }

        {
            Obj *object;
            void *state_def;
            object = *object_slot;
            state_def = &D_80045340;
            func_8004491C(object, state_def);
        }
    after_call:
        transform = (*object_slot)->subA;
        transform->f2 = layout->f2;
        transform->f6 = layout->f6;
        sprite = (*object_slot)->subB;
        sprite->f1E = 0x1000;
        sprite->f1C = 0x1000;
        sprite->fC = 0x2C808080;
        sprite->f6 = 4;

        if (part_index == 0) {
            func_800C77D0(objects[0], transform, 8, D_800DCE66[0]);
            sprite->f8 = (void *)func_8004A658(selection[1], selection[0]);
        } else if (part_index == 1) {
            sprite->f8 = D_800DF368;
        } else {
            func_8003DB94(sprite, D_80079444, 0);
            sprite->f14 |= 0xC;
        }
        {
            Obj *object;
            Aux *part_state;

            object = *object_slot;
            part_state = (Aux *)((u8 *)object + 0x20);
            part_state->fA = layout->fA - D_800DDC40[0];
            ((S_800BA074_0 *)object)->unk_20 = &D_800814A8;
            part_state->f12 = part_index;
            part_state->f16 = transform->f2;
            part_state->f1A = transform->f6;
            ASM_USE_G_NV(transform);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (part_index != 0) {
                part_state->f28 = objects[0];
            } else {
                part_state->f2C = selection;
            }
            if (func_800BA33C(((S_800BA074_2 *)(((S_800BA074_1 *)global_page)->unk_3D7C))->unk_AC) != 0) {
                part_state->fE = 8;
                part_state->f0 = ((S_800BA074_1 *)global_page)->unk_3D7C + 0xAC;
                if (part_state->f12 == last_part) {
                    sprite->fC = 0x101080;
                }
                goto next;
            }
            if (func_800BA33C(((S_800BA074_2 *)(((S_800BA074_1 *)global_page)->unk_3D7C))->unk_B0) != 0) {
                part_state->fE = 8;
                part_state->f0 = ((S_800BA074_1 *)global_page)->unk_3D7C + 0xB0;
                if (part_state->f12 == last_part) {
                    sprite->fC = 0x801010;
                }
            }
        }
    }

next:
    part_index++;
    object_slot++;
    if (part_index < 3) {
        goto loop;
    }

    {
        u8 *counter_base = (u8 *)&D_80083460;
        *(u16 *)(counter_base + 0xA) += 1;
    }
    func_800B1768(0, 0x27, 0x40, 0x209, 0, 0);
    func_800B1B10(selection, 0x4C, 0x50, 0x200, 0, 2);
    return objects[0];
}
