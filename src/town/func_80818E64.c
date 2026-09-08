#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022E64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80022E64_0;   /* obj in func_80022E64 */

typedef struct S_80022E64_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_80022E64_1;   /* data in func_80022E64 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80046398[];

typedef struct Copy24 {
    s32 word[6];
} Copy24;

/* Allocates an object, copies six source words, and initializes its data. */
void func_80022E64(void *source_words, s32 data_value_08, s32 object_value_10, s32 object_value_20) {
    S_80022E64_0 *object;
    void *copy_dst;
    S_80022E64_1 *object_data;

    object = func_8003FC64(0x136);
    if (object != NULL) {
        func_8004491C(object, D_80046398);
        copy_dst = object->unk_08;
        *(Copy24 *)copy_dst = *(Copy24 *)source_words;
        object_data = object->unk_0C;
        object->unk_20 = object_value_20;
        object->unk_10 = object_value_10;
        object_data->unk_1C = 0x1000;
        object_data->unk_1E = 0x1000;
        object_data->unk_20 = 0x1000;
        object_data->unk_12 = 0;
        object_data->unk_14 = 0;
        object_data->unk_10 = 0;
        object_data->unk_16 = 0;
        object_data->unk_18 = 0;
        object_data->unk_1A = 0;
        object_data->unk_00 = 0;
        object_data->unk_04 = 0;
        object_data->unk_05 = 0;
        object_data->unk_06 = 0xA;
        object_data->unk_0C = 0x808080;
        object_data->unk_08 = data_value_08;
    }
}
