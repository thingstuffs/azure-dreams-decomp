#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct PackedVec3 {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80044BB0[];
extern u8 D_8016F99C[];
extern u8 D_80173B1C[];
extern u8 D_80173B28[];
extern void *D_80175D58[];
extern void *D_80175D5C[];

void func_8016FAFC(s32 arg0)
{
    u8 *obj;
    register u8 *part ASM_REG("$17");
    register u8 *call_obj ASM_REG("$4");
    register u8 *sprite ASM_REG("$7");
    register u8 *copy_page ASM_REG("$2");
    register u8 *copy_src ASM_REG("$6");
    register u8 *store_page ASM_REG("$2");
    register u8 *dest ASM_REG("$2");
    u8 *coords;

    obj = func_8003FC64(0x12);
    if (obj != NULL) {
        call_obj = obj;
        part = obj + 0x20;
        ASM_KEEP(call_obj);
        ASM_KEEP(part);
        FIELD(part, s16, 0x18) = 0;
        FIELD(part, s16, 0x1C) = arg0;
        FIELD(obj, void *, 0x10) = D_8016F99C;
        func_8004491C(call_obj, D_80044BB0);

        sprite = FIELD(obj, u8 *, 0xC);
        ASM_KEEP(sprite);
        FIELD(sprite, u16, 0x14) &= 0xFFF3;

        coords = FIELD(obj, u8 *, 8);
        FIELD(coords, s16, 2) = 0xA0;
        FIELD(coords, s16, 6) = 0xA;
        FIELD(coords, s16, 0xA) = 2;

        sprite = FIELD(obj, u8 *, 0xC);
        ASM_KEEP(sprite);
        FIELD(sprite, s16, 0x1E) = 0x1000;
        FIELD(sprite, s16, 0x1C) = 0x1000;
        FIELD(sprite, u8, 0xE) = 0x80;
        FIELD(sprite, u8, 0xD) = 0x80;
        FIELD(sprite, u8, 0xC) = 0x80;

        if (arg0 == 0) {
            copy_page = (u8 *)0x80170000;
            ASM_KEEP(copy_page);
            copy_src = copy_page + 0x3B1C;
            ASM_KEEP(copy_src);
            FIELD(obj, PackedVec3, 0x48) =
                FIELD(copy_src, PackedVec3, 0);
            ASM_KEEP(copy_page);
            store_page = (u8 *)0x80170000;
            ASM_KEEP(store_page);
            FIELD(store_page, void *, 0x5D58) = obj;
        } else {
            copy_page = (u8 *)0x80170000;
            ASM_KEEP(copy_page);
            copy_src = copy_page + 0x3B28;
            ASM_KEEP(copy_src);
            FIELD(obj, PackedVec3, 0x48) =
                FIELD(copy_src, PackedVec3, 0);
            ASM_KEEP(copy_page);
            store_page = (u8 *)0x80170000;
            ASM_KEEP(store_page);
            FIELD(store_page, void *, 0x5D5C) = obj;
        }
        dest = part + 0x28;
        ASM_KEEP(dest);
        FIELD(sprite, void *, 8) = dest;
    }
}

/* MECHANISM: The true-space body uses a local join, not a phantom call at 0x8016FC28.
   A 0x20 frame holds arg0, obj, and obj+0x20 in s2/s0/s1; packed 12-byte
   assignments reproduce the two unaligned vector-copy arms. */
