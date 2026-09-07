#include "common.h"

typedef struct OutputRecord {
    s32 value0;
    s32 value1;
    s32 value2;
} OutputRecord;

typedef struct SourceFields {
    s32 unk0;
    s32 value1;
    s32 value2;
} SourceFields;

typedef struct MethodTable {
    u8 pad_000[0x208];
    void (*method_208)(s32);
    u8 pad_20C[0x18];
    void (*method_224)(OutputRecord *);
} MethodTable;

typedef struct Context {
    u8 pad_00[0x1C];
    SourceFields *fields;
    MethodTable *methods;
} Context;

extern Context *D_80016000;
extern OutputRecord D_80019AE0;

void func_805D365C(void) {
    Context *context;
    OutputRecord *output;
    s32 value;

    context = D_80016000;
    D_80019AE0.value0 = context->fields->value1 << 16;
    value = context->fields->value2;
    do {
        output = &D_80019AE0;
    } while (0);
    output->value2 = 0;
    output->value1 = value << 16;
    context->methods->method_208(0);
    D_80016000->methods->method_224(output);
}
