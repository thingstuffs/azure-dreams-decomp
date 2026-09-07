#include "common.h"

typedef struct S_80025874_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025874_0;   /* obj in func_80025874 */

typedef struct S_80025874_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2A];
    u8 unk_40;
    s8 unk_41;
    s8 unk_42;
} S_80025874_1;   /* fields in func_80025874 */



typedef struct {
    s32 words[6];
} Copy24;

extern void *func_8003FC64();
extern s32 D_800253F4;

/* Allocates and initializes an object, copying 24 bytes of source data into it. */
void *func_80025874(s32 state_value, Copy24 *source_data, s16 initial_setting) {
    void *obj;
    S_80025874_1 *fields;
    void *object_data;
    register void *result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    do { obj = func_8003FC64(0x212); } while (0);
    result = 0;
    if (obj != 0) {
        ((S_80025874_0 *)obj)->unk_10 = &D_800253F4;
        fields = obj + 0x20;
        ((S_80025874_0 *)obj)->unk_20 = state_value;
        fields->unk_08 = 8;
        fields->unk_10 = 2;
        fields->unk_0E = 0x48;
        fields->unk_12 = 1;
        fields->unk_04 = 0;
        fields->unk_06 = 0;
        fields->unk_0A = 0;
        fields->unk_0C = 0;
        fields->unk_40 = 0xC0;
        fields->unk_42 = 0;
        fields->unk_41 = 0;
        fields->unk_14 = initial_setting;
        object_data = ((S_80025874_0 *)obj)->unk_08;
        result = obj;
        *(Copy24 *)object_data = *source_data;
    }
    return result;
}
