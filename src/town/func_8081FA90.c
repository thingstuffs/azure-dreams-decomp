#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022290_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80022290_0;   /* obj1 in func_80022290 */

typedef struct S_80022290_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80022290_1;   /* data1 in func_80022290 */

typedef struct S_80022290_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80022290_2;   /* obj2 in func_80022290 */

typedef struct S_80022290_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_80022290_3;   /* data2 in func_80022290 */



typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void *func_8004DA74(void *, void *, s32);
extern void func_800BC1DC(void *, void *, void *);

extern Packed8 D_8002021C;
extern u8 D_800223D8[8];
extern u8 D_800223E0[8];
extern u8 D_800223E8[8];
extern void *D_80024468;
extern void *D_8002446C;
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_800782EC[8];

/* Initializes display resources and creates rectangle and image objects. */
void func_80022290(void *context)
{
    Packed8 setup_words;
    void *rect_obj;
    S_80022290_1 *rect_data;
    void *image_obj;
    S_80022290_3 *image_data;
    void *image_resource;

    setup_words = D_8002021C;
    func_800BC1DC(&setup_words, D_800223D8,
                  func_8004DA74(context, D_8002446C, 0));
    func_800BC1DC((u8 *)&setup_words + 4, D_800223D8, D_800782EC);

    rect_obj = func_8003FC64(1);
    if (rect_obj != NULL) {
        rect_data = rect_obj + 0x20;
        ((S_80022290_0 *)rect_obj)->unk_10 = D_800223E0;
        func_8004491C(rect_obj, &D_80053A88);
        rect_data->unk_0C = 0xB8;
        rect_data->unk_0E = 0x14;
        rect_data->unk_10 = 0x7C;
        rect_data->unk_12 = 0x18;
        rect_data->unk_16 = 1;
        rect_data->unk_08 = 0x402020;
    }

    image_obj = func_8003FC64(1);
    if (image_obj != NULL) {
        image_data = image_obj + 0x20;
        ((S_80022290_2 *)image_obj)->unk_10 = D_800223E8;
        func_8004491C(image_obj, D_80053858);
        image_data->unk_14 = 0xF0;
        image_data->unk_16 = 0x20;
        image_data->unk_18 = 3;
        image_resource = D_80024468;
        image_data->unk_1A = 0x7C80;
        image_data->unk_10 = 0x808080;
        image_data->unk_04 = image_resource;
    }
}
