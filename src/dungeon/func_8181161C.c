#include "common.h"

typedef struct {
    s8 pad_00[0x10];
    s32 index;
    s32 field_14;
    u8 pad_18[0x58];
    s32 field_70;
} Func8181161CData;

extern u8 D_800294F8[9];

extern void memset(s32, s32, s32);
extern void strcpy(s32, s32);
extern void func_800263C0(s32, s32);

void func_8002661C(s8 *arg0, s32 arg1) {
    Func8181161CData *data = (Func8181161CData *)(arg0 + 0x20);

    memset(data->field_14, 0, (D_800294F8[data->index] << 1) | 1);
    strcpy(data->field_14, arg1);
    func_800263C0(data->field_70, data->field_14);
}
