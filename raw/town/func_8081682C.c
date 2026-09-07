#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_8003DB94();
extern void *func_8003FD64();
extern s32 func_8004491C();

typedef struct {
    u16 field_0;
    u16 field_2;
} D_80026DE0Entry;

extern s32 D_80022698[3];
extern D_80026DE0Entry D_80026DE0[3][8];
extern s32 D_80045340;
extern s32 D_80083498[3];
extern s32 D_800F29B4[3];

void func_8002082C(void *arg0) {
    s32 offset;
    s32 count;
    void *object_data;
    void *object;
    void *image;

    count = 7;
    do {
        object = func_8003FD64(0x136, D_80083498);
        FIELD((u8 *)arg0 + count * 4, void *, 8) = object;
        offset = count * 4;
        if (object != 0) {
            FIELD(object, void *, 0x10) = D_80022698;
            func_8004491C(object, &D_80045340);
            FIELD(object, void *, 0x20) = arg0;
            image = FIELD(object, void *, 8);
            object_data = FIELD(object, void *, 0xC);
            FIELD(image, u16, 2) = D_80026DE0[FIELD(arg0, s16, 0x34)][count].field_0;
            FIELD(image, u16, 6) = D_80026DE0[FIELD(arg0, s16, 0x34)][count].field_2;
            FIELD(object_data, s16, 0x10) = 0x60;
            FIELD(object_data, s32, 0xC) = 0;
            FIELD(object_data, s16, 0x1E) = 0x1000;
            FIELD(object_data, s16, 0x1C) = 0x1000;
            FIELD(object_data, u16, 0x14) |= 0xC;
            func_8003DB94(object_data, D_800F29B4, 0);
        }
        count--;
    } while (count >= 0);
}

/* MECHANISM: Two-u16 table records force one D_80026DE0 base and lhu offsets 0/2.
   Array decay holds D_80022698 in s6; count-indexed slot access lets strength reduction
   place s3 after both held bases, reproducing the -0x30 frame, save order, and loop CFG. */
