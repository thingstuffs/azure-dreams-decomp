#include "common.h"

typedef struct S_80175180_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} S_80175180_0;   /* state in func_80175180 */

typedef struct S_80175180_1 {
    u8 pad_00[0x96];
    u16 unk_96;
} S_80175180_1;   /* arg0 in func_80175180 */

typedef struct S_80175180_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80175180_2;   /* obj in func_80175180 */

typedef struct S_80175180_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_80175180_3;   /* part in func_80175180 */

typedef struct S_80175180_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80175180_4;   /* pos in func_80175180 */

typedef struct S_80175180_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80175180_5;   /* arg1 in func_80175180 */


#define VFIELD(p, type, off) (*(volatile type *)((u8 *)(p) + (off)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340[];
extern u8 D_801749EC[];

void func_80175180(void *in_arg0, void *in_arg1)
{
    register void *arg0 ASM_REG("$17") = in_arg0;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register void *arg1 ASM_REG("$18") = in_arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 flags;
    void *obj;
    S_80175180_3 *part;
    S_80175180_4 *pos;
    u8 *state;

    obj = func_8003FC64(0x12);
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    state = (u8 *)obj + 0x20;
    if (obj != 0) {
        ((S_80175180_0 *)state)->unk_08 = 0x4A;
        ((S_80175180_0 *)state)->unk_0A = ((S_80175180_1 *)arg0)->unk_96;
        ((S_80175180_0 *)state)->unk_0C = 0;
        ((S_80175180_2 *)obj)->unk_10 = D_801749EC;
        func_8004491C(obj, D_80045340);
        part = ((S_80175180_2 *)obj)->unk_0C;
        part->unk_10 = 0x20;
        flags = VFIELD(part, u16, 0x14);
        flags |= 0xC;
        VFIELD(part, u16, 0x14) = flags;
        flags |= 0x80;
        VFIELD(part, u16, 0x14) = flags;
        pos = ((S_80175180_2 *)obj)->unk_08;
        pos->unk_00 = ((S_80175180_5 *)arg1)->unk_00;
        pos->unk_04 = ((S_80175180_5 *)arg1)->unk_04;
        pos->unk_08 = ((S_80175180_5 *)arg1)->unk_08 + 0xFFE80000;
        part = ((S_80175180_2 *)obj)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        part->unk_0E = 0x80;
        part->unk_0C = 0x80;
        part->unk_0D = 0x80;
    }
}

/* MECHANISM: Pin arg0/arg1 to s1/s2 and keep them just after the allocator call,
   preserving the 0x20 frame/save order without blocking retail call setup.
   A volatile u16 RMW retains both flag stores; source order and u8 fields close the residue. */
