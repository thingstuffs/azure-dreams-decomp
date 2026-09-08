#include "common.h"
#include "records/Rec_D_80175D50.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80170700_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_80170700_1;   /* temp_v0 in func_80170700 */

typedef struct S_80170700_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80170700_2;   /* temp_s0_2 in func_80170700 */

typedef struct S_80170700_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170700_3;   /* temp_a0 in func_80170700 */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_80047784();
extern s32 D_80045340;
typedef struct {
    u16 x0;
    u16 x2;
    u16 x4;
    u16 x6;
    u16 x8;
    u16 xA;
} D_80083780_S;
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
} Copy16;
extern D_80083780_S D_80083780;
extern s32 D_80170534;
extern u8 D_80170000[0x3A81];
extern void *D_80175D50;
extern void *D_80175D64;

/* Creates an object from the current object's data and initializes its position and appearance. */
void func_80170700(void) {
    s32 copy_end;
    s32 data_index;
    S_80170700_3 *position;
    void *source_data;
    S_80170700_2 *render_data;
    S_80170700_1 *object;
    void *copy_dst;
    void *copy_src;
    register void *call_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    source_data = ((Rec_D_80175D50 *)D_80175D50)->unk_0C;
    object = func_8003FC64(0x112);
    copy_src = source_data;
    if (object != NULL) {
        copy_end = (s32)copy_src + 0x30;
        render_data = object->unk_0C;
        object->unk_38 = 0;
        object->unk_10 = &D_80170534;
        copy_dst = render_data;
        do {
            *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
            copy_src = (u8 *)copy_src + 0x10;
            copy_dst = (u8 *)copy_dst + 0x10;
        } while (copy_src != (void *)copy_end);
        render_data->unk_14 =
            (render_data->unk_14 & 0xFF7F) | 0x400;
        func_8004491C(object, &D_80045340, copy_dst, copy_src);
        call_obj = render_data;
        data_index = *(&D_80170000[0x3A80]);
        ASM_KEEP(data_index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render_data->unk_2C = &D_80170000[0x3A80];
        func_80047784(call_obj, data_index, 0);
        render_data->unk_06 = 6;
        render_data->unk_14 &= 0xFFF3;
        position = object->unk_08;
        position->unk_02 = D_80083780.x2;
        position->unk_06 = D_80083780.x6 - 0x400;
        position->unk_0A = D_80083780.xA;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        D_80175D64 = object;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame and long-lived s0/s1 roles.
   A widened byte local plus call_obj pinned in a0 fixes the pre-call order.
   ASM_KEEP(data_index) delays a2=0 while the following store fills the jal slot. */
