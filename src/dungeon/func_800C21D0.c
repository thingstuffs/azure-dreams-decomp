#include "common.h"

typedef struct S_800C7930_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7930_0;   /* camera in func_800C7930 */

typedef struct S_800C7930_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_1;   /* source in func_800C7930 */

typedef struct S_800C7930_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800C7930_2;   /* work in func_800C7930 */

typedef struct S_800C7930_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_3;   /* destination in func_800C7930 */



extern u8 D_80083780;
extern u16 D_800DCEAC;
extern u16 D_800DCEBC;
extern u8 D_800E58F8;
extern void func_800C77D0(void *arg0, void *arg1, s16 arg2);

/* Apply table offsets to a position near the camera and pass it to func_800C77D0. */
s32 func_800C7930(s32 object_addr, void *source_pos, s32 helper_arg)
{
    s32 delta;
    s32 source_coord;
    s32 x_offset_index;
    s32 y_offset_index;
    s32 adjusted_x;
    u16 y_offset;
    register u16 source_x ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_800C7930_2 *work;
    register u8 *camera;
    register u8 *destination ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *x_offsets;
    register u8 *y_offsets;
    register s32 object ASM_REG("$10") = object_addr;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    S_800C7930_1 *source = source_pos;

    ASM_KEEP_NV(object);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    camera = &D_80083780;
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(camera);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    delta = ((S_800C7930_0 *)camera)->unk_02;
    source_coord = source->unk_02.s;
    source_x = source->unk_02.u;
    delta -= source_coord;
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 0xC1) {
        delta = ((S_800C7930_0 *)camera)->unk_06;
        source_coord = source->unk_06.s;
        delta -= source_coord;
        if (delta < 0) {
            delta = -delta;
        }
        work = (u8 *)object + 0x20;
        if (delta < 0xC1) {
            destination = &D_800E58F8;
            x_offsets = (u8 *)&D_800DCEAC;
            x_offset_index = (work->unk_2A >> 8) & 0xE;
            adjusted_x = (s16)*(u16 *)(x_offsets + x_offset_index) / 2;
            adjusted_x = source_x - -adjusted_x;
            ((S_800C7930_3 *)destination)->unk_02 = adjusted_x;
            y_offsets = (u8 *)&D_800DCEBC;
            y_offset_index = (work->unk_2A >> 8) & 0xE;
            y_offset = *(u16 *)(y_offsets + y_offset_index);
            ((S_800C7930_3 *)destination)->unk_06 = source->unk_06.u + (s16)y_offset / 2;
            ((S_800C7930_3 *)destination)->unk_0A = source->unk_0A;
            func_800C77D0((void *)object, destination, (s16)helper_arg);
        }
    }
    return 0;
}
