#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BEAD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BEAD0_0;   /* temp_v0 in event_pool_clean_in */

typedef struct S_800BEAD0_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BEAD0_1;   /* temp_v1 in event_pool_clean_in */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK SD_Call();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8007789C;
extern s32 D_80083780;
extern M2C_UNK D_800BEBA4;

/* event_pool_clean_in: creates the pool cleaning object and initializes its motion and display. */
s32 event_pool_clean_in(void)
{
    s32 *origin;
    s32 color;
    volatile s32 *motion;
    s32 origin_z;
    void *object;
    void *object_part;

    object = func_8003FC64(0x136);
    if (object != NULL) {
        SD_Call(0x512);
        motion = ((S_800BEAD0_0 *)object)->unk_08;
        ((S_800BEAD0_0 *)object)->unk_10 = &D_800BEBA4;
        func_8004491C(object, &D_80045340);
        object_part = object + 0x20;
        ASM_KEEP(object_part);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        (*(s16 *)((u8 *)object_part + 2)) = 0x10;
        color = 0x00800000;
        motion[0] = D_80083780;
        origin = &D_80083780;
        motion[1] = origin[1];
        color |= 0x8080;
        origin_z = origin[2];
        motion[3] = 0x100000;
        motion[5] = 0xFFF00000;
        motion[2] = origin_z + 0xFFA00000;
        object_part = ((S_800BEAD0_0 *)object)->unk_0C;
        ((S_800BEAD0_1 *)object_part)->unk_1E = 0x1000;
        ((S_800BEAD0_1 *)object_part)->unk_1C = 0x1000;
        ((S_800BEAD0_1 *)object_part)->unk_08 = &D_8007789C;
        ((S_800BEAD0_1 *)object_part)->unk_0C = color;
    }
    return 0;
}

/* MECHANISM: The 0x20 frame and s0/s1 holds already matched retail.
   Depinning the page base and color restored the page-lui/color-lui sched2 order.
   Retaining only ASM_KEEP(object_part) preserves the standalone s1+0x20 address word. */
