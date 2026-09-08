#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024BBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_80024BBC_0;   /* object in func_80024BBC */


typedef struct S_80024BBC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024BBC_2;   /* dest1 in func_80024BBC */

typedef struct S_80024BBC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80024BBC_3;   /* dest2 in func_80024BBC */

typedef struct S_80024BBC_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80024BBC_4;   /* dest3 in func_80024BBC */

typedef struct S_80024BBC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x1C];
    s32 unk_50;
} S_80024BBC_5;   /* base in func_80024BBC */

typedef struct S_80024BBC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024BBC_6;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80024BBC */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *);
extern void func_80024B6C(void);
extern void func_800248EC(void);

/* Creates an object with randomized position offsets and initializes its state and callbacks. */
void func_80024BBC(
    Rec_D_800E3D7C *source, s16 field_14_value, void *payload, s16 field_32_value,
    s32 x_offset, s32 y_offset, s32 z_offset)
{
    register s32 held_x_offset ASM_REG("$18") = x_offset;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 held_y_offset ASM_REG("$19") = y_offset;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 held_z_offset ASM_REG("$20") = z_offset;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *object;
    S_80024BBC_5 *state;

    object = func_8003FD64(0x211, source);
    if (object != NULL) {
        s32 x_jitter;
        s32 y_jitter;
        s32 z_jitter;
        s32 x_bias;
        s32 y_bias;
        s32 z_bias;
        s32 x_pos;
        s32 y_pos;
        s32 z_pos;
        S_80024BBC_2 *x_dest;
        S_80024BBC_3 *y_dest;
        S_80024BBC_4 *z_dest;

        ((S_80024BBC_0 *)object)->unk_10 = func_80024B6C;

        x_jitter = rand() & 0x1F;
        x_pos = ((S_80024BBC_6 *)(source->unk_08.at00_pv.v))->unk_02;
        x_dest = ((S_80024BBC_0 *)object)->unk_08;
        x_pos += x_jitter;
        x_bias = held_x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = x_pos;
        y_jitter = rand() & 0x1F;
        y_pos = ((S_80024BBC_6 *)(source->unk_08.at00_pv.v))->unk_06;
        y_dest = ((S_80024BBC_0 *)object)->unk_08;
        y_pos += y_jitter;
        y_bias = held_y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = y_pos;

        state = (u8 *)object + 0x20;
        z_jitter = rand() & 0x1F;
        z_pos = ((S_80024BBC_6 *)(source->unk_08.at00_pv.v))->unk_0A;
        z_dest = ((S_80024BBC_0 *)object)->unk_08;
        z_pos += z_jitter;
        z_bias = held_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = z_pos;
        state->unk_14 = field_14_value;
        state->unk_32 = field_32_value;
        func_8004491C(object, func_800248EC);
        state->unk_50 = -0x2000;
        state->unk_08 = payload;
        ASM_KEEP(held_x_offset);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_y_offset);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_z_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s4 stack-argument holds fall out of guarded pins.
   Separate random/value/destination/offset names give v1/a0/v0 one live range per field.
   Tail ASM_KEEPs prevent destructive saved-register updates without fencing call slots. */
