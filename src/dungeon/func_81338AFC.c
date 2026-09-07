#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct PackedVec3 {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3;


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80044BB0[];
extern u8 D_8016F99C[];
extern u8 D_80173B1C[];
extern u8 D_80173B28[];
extern void *D_80175D58[];
extern void *D_80175D5C[];


typedef struct S_8016FAFC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
} S_8016FAFC_0;   /* part in func_8016FAFC */

typedef struct S_8016FAFC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016FAFC_1;   /* sprite in func_8016FAFC */

typedef struct S_8016FAFC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016FAFC_2;   /* coords in func_8016FAFC */

typedef struct S_8016FAFC_3 {
    u8 pad_00[0x5D58];
    void * unk_5D58;
    void * unk_5D5C;
} S_8016FAFC_3;   /* store_page in func_8016FAFC */

void func_8016FAFC(s32 arg0)
{
    u8 *obj;
    u8 *part;
    register u8 *call_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *sprite ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    register u8 *copy_page ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register u8 *copy_src ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u8 *store_page;
    u8 *dest;
    u8 *coords;

    obj = func_8003FC64(0x12);
    if (obj != NULL) {
        call_obj = obj;
        part = obj + 0x20;
        ASM_KEEP(part);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_8016FAFC_0 *)part)->unk_18 = 0;
        ((S_8016FAFC_0 *)part)->unk_1C = arg0;
        (*(void * *)((u8 *)obj + 0x10)) = D_8016F99C;
        func_8004491C(call_obj, D_80044BB0);

        sprite = (*(u8 * *)((u8 *)obj + 0xC));
        ((S_8016FAFC_1 *)sprite)->unk_14 &= 0xFFF3;

        coords = (*(u8 * *)((u8 *)obj + 8));
        ((S_8016FAFC_2 *)coords)->unk_02 = 0xA0;
        ((S_8016FAFC_2 *)coords)->unk_06 = 0xA;
        ((S_8016FAFC_2 *)coords)->unk_0A = 2;

        sprite = (*(u8 * *)((u8 *)obj + 0xC));
        ((S_8016FAFC_1 *)sprite)->unk_1E = 0x1000;
        ((S_8016FAFC_1 *)sprite)->unk_1C = 0x1000;
        ((S_8016FAFC_1 *)sprite)->unk_0E = 0x80;
        ((S_8016FAFC_1 *)sprite)->unk_0D = 0x80;
        ((S_8016FAFC_1 *)sprite)->unk_0C = 0x80;

        if (arg0 == 0) {
            copy_page = (u8 *)0x80170000;
            ASM_KEEP(copy_page);   /* MATCH pin: load-bearing for the whole function shape */
            copy_src = copy_page + 0x3B1C;
            ASM_KEEP(copy_src);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)((u8 *)copy_src + 0));
            ASM_KEEP(copy_page);   /* MATCH pin: load-bearing for the whole function shape */
            store_page = (u8 *)0x80170000;
            ASM_KEEP(store_page);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_8016FAFC_3 *)store_page)->unk_5D58 = obj;
        } else {
            copy_page = (u8 *)0x80170000;
            ASM_KEEP(copy_page);   /* MATCH pin: load-bearing for the whole function shape */
            copy_src = copy_page + 0x3B28;
            ASM_KEEP(copy_src);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)((u8 *)copy_src + 0));
            ASM_KEEP(copy_page);   /* MATCH pin: load-bearing for the whole function shape */
            store_page = (u8 *)0x80170000;
            ASM_KEEP(store_page);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_8016FAFC_3 *)store_page)->unk_5D5C = obj;
        }
        dest = part + 0x28;
        ((S_8016FAFC_1 *)sprite)->unk_08 = dest;
    }
}

/* MECHANISM: The true-space body uses a local join, not a phantom call at 0x8016FC28.
   A 0x20 frame holds arg0, obj, and obj+0x20 in s2/s0/s1; packed 12-byte
   assignments reproduce the two unaligned vector-copy arms. */
