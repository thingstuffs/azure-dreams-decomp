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

/* Builds a record with two 16.16 values and a zero third value, then invokes the context callbacks. */
void func_805D365C(void) {
    Context *context;
    OutputRecord *output;
    s32 source_value2;

    context = D_80016000;
    D_80019AE0.value0 = context->fields->value1 << 16;
    source_value2 = context->fields->value2;
    output = &D_80019AE0;
    output->value2 = 0;
    output->value1 = source_value2 << 16;
    context->methods->method_208(0);
    D_80016000->methods->method_224(output);
}
