#include "common.h"
#include "records/Rec_func_800AD058_arg2.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} __attribute__((packed)) unaligned_s32;

#ifndef NULL
#define NULL 0
#endif


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *, s32);
extern s32 func_8004A658(s32, s32);
extern void func_800BC26C(void *, s32, s32, s32);

extern u8 D_80045340[9];
extern u8 D_8006E240[9];
extern u8 D_80174978[9];


typedef struct S_80174D48_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174D48_0;   /* temp_v0 in func_80174D48 */

typedef struct S_80174D48_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_80174D48_1;   /* temp_s2 in func_80174D48 */

typedef struct S_80174D48_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D48_2;   /* temp_v1 in func_80174D48 */

typedef struct S_80174D48_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80174D48_3;   /* temp_s1 in func_80174D48 */


/* Creates and initializes a display object from the source position and appearance. */
void func_80174D48(void *source, Rec_func_800AD058_arg2 *record, void *appearance)
{
    s32 coord_z;
    s32 record_byte;
    s32 coord_value;
    void *init_object;
    u32 init_address;
    void *active_object;
    s32 zero;
    s32 sprite_size;
    S_80174D48_3 *sprite;
    register void *data_base ASM_REG("$18");
    void *object_data;
    void *texture;
    void *object;
    S_80174D48_2 *transform;

    if (((*(u8 *)((u8 *)appearance + 0x49)) != 0) &&
        (object = func_8003FC64(0x12), object != NULL)) {
        init_object = object;
        ASM_KEEP(init_object);
        transform = ((S_80174D48_0 *)object)->unk_08;
        data_base = source;
        coord_value = ((S_80174D48_1 *)data_base)->unk_00;
        sprite = ((S_80174D48_0 *)object)->unk_0C;
        ASM_SCHED_BARRIER();
        init_address = 0x80040000;
        ASM_KEEP(init_address);
        transform->unk_00 = coord_value;
        init_address += 0x5340;
        transform->unk_04 = ((S_80174D48_1 *)data_base)->unk_04;
        coord_z = ((S_80174D48_1 *)data_base)->unk_08;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        transform->unk_14 = 0xFFEE0000;
        transform->unk_08 = coord_z;
        func_8004491C(init_object, (void *)init_address, coord_z);
        sprite->unk_0C = 0x808080;
        ASM_SCHED_BARRIER();
        sprite_size = 0xC90;
        ASM_KEEP(sprite_size);
        object_data = (u8 *)object + 0x20;
        sprite->unk_1E = sprite_size;
        sprite->unk_1C = sprite_size;
        data_base = object_data;
        if ((*(u8 *)((u8 *)appearance + 0x49)) == 0x12) {
            texture = (void *)0x80070000;
            ASM_KEEP(texture);
            texture = (u8 *)texture - 0x1DC0;
        } else {
            texture = (void *)func_8004A658((*(volatile u8 *)((u8 *)appearance + 0x49)),
                          (*(u8 *)((u8 *)appearance + 0x48)));
        }
        sprite->unk_08 = (s32)texture;
        record_byte = record->unk_24;
        ASM_KEEP(record_byte);
        active_object = object;
        ASM_KEEP(active_object);
        ((S_80174D48_1 *)data_base)->unk_A8 = record_byte;
        record_byte = record->unk_25;
        ASM_KEEP(record_byte);
        zero = 0;
        ASM_KEEP(zero);
        ((S_80174D48_1 *)data_base)->unk_AA = record_byte;
        (*(unaligned_s32 *)((u8 *)object_data + 0x48)) = (*(unaligned_s32 *)((u8 *)appearance + 0x48));
        func_800BC26C(active_object, zero, zero, zero);
        ((S_80174D48_0 *)object)->unk_10 = D_80174978;
    }
}
