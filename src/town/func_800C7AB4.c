#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C5214_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA8];
    s32 unk_BC;
} S_800C5214_0;   /* object in func_800C5214 */

typedef struct S_800C5214_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5214_1;   /* part in func_800C5214 */


extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern u8 D_800345B8[];
extern u8 D_800C52D0[];
extern u8 D_800F148C[];

/* Allocates an object and initializes its display part and user data. */
void *func_800C5214(s32 user_data)
{
    S_800C5214_1 *part;
    S_800C5214_0 *object;

    object = func_8003FC64(0x136);
    if (object == NULL) {
        return NULL;
    }

    {
        register void *return_object;
        register u16 flags;
        register s32 part_value;

        object->unk_10 = D_800C52D0;
        object->unk_BC = user_data;
        part = object->unk_0C;
        part->unk_1E = 0x1800;
        part->unk_1C = 0x1800;
        part->unk_0E = 0x4C;
        part->unk_0D = 0x4C;
        part->unk_0C = 0x4C;
        part->unk_08 = D_800F148C;
        part->unk_00 = 0;
        part->unk_04 = 0;
        part->unk_05 = 0;
        part->unk_06 = -0x10;
        func_8004491C(object, D_800345B8);
        return_object = object;
        flags = part->unk_14;
        part_value = 0x20;
        part->unk_10 = part_value;
        part->unk_14 = flags | 0x1C;
        return return_object;
    }
}
