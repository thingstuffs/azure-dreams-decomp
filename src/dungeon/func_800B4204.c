#include "common.h"

typedef struct SubA {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fA;
} SubA;

typedef struct SubB {
    u8 pad0[6];
    u16 f6;
    u8 pad8[4];
    u32 fC;
    u16 f10;
    u8 pad12[2];
    u16 f14;
    u8 pad16[6];
    u16 f1C;
    u16 f1E;
} SubB;

typedef struct Obj {
    u8 pad0[8];
    SubA *sub1;
    SubB *sub2;
    void (*stateFn)(void *);
    u8 pad14[0x20 - 0x14];
    void *owner;
} Obj;

typedef struct EntityHdr {
    u8 pad[0x88];
    u16 f88;
} EntityHdr;

typedef struct {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} D_80083780_t;

extern void *D_80083498;
extern D_80083780_t D_80083780;
extern u8 D_80079444[];
extern s16 D_800DCE66[5];
extern void *D_8008346C;

extern void *func_8003FD64(s32 a0, void *a1);
extern void func_8004491C(void *a0, void *a1);
extern s32 func_80045C34(u8 *a0, s32 a1, void *a2);
extern void func_800B96C4(void *a0);
extern void func_8003DB94(void *a0, void *a1, s16 a2);
extern void func_800C77D0(void *a0, void *a1, s32 a2, s16 a3);

/* Creates and initializes a display object attached to the entity. */
void *func_800B9964(EntityHdr **entity_ref) {
    Obj *object;
    SubA *transform;
    SubB *sprite;

    object = func_8003FD64(18, &D_80083498);
    if (object != 0) {
        func_8004491C(object, (void *)func_80045C34);
        object->stateFn = func_800B96C4;

        transform = object->sub1;
        sprite = object->sub2;
        transform->f2 = D_80083780.f2;
        transform->f6 = D_80083780.f6;
        transform->fA = (*entity_ref)->f88;
        func_8003DB94(sprite, D_80079444, 0);

        {
            Obj *init_object;
            SubA *init_transform;
            s32 init_mode;
            u32 color;
            u16 flags;

            color = 0x2c808080;
            init_object = object;
            init_transform = transform;
            __asm__ __volatile__("" : "+r"(init_object), "+r"(init_transform));

            sprite->f1E = 256;
            sprite->f1C = 256;
            sprite->f10 = 32;
            flags = sprite->f14;
            __asm__ __volatile__("" : : "r"(flags));
            init_mode = 8;
            ASM_KEEP(init_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sprite->fC = color;
            sprite->f6 = 4;
            __asm__ __volatile__("" : : "m"(sprite->f6));
            sprite->f14 = flags | 0xC;

            {
                u8 *owner_data = (u8 *)object + 0x20;
                *(s16 *)(owner_data + 0xE) = 4;
                __asm__ __volatile__("" : : "r"(owner_data));
            }
            object->owner = entity_ref;

            D_8008346C = object;
            func_800C77D0(init_object, init_transform, init_mode, D_800DCE66[0]);
        }
    }

    return (void *)object;
}
