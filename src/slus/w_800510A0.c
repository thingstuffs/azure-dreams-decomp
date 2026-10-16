#include "common.h"

extern void sceneLoadTextureAndDataPair(void *a0);
extern s32 func_80126890(void *a0);

typedef struct S_800510A0 {
    s32 unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
} S_800510A0;

/* Processes the record's unkC field and stores the result for unk4 in unk8. */
void func_800510A0(S_800510A0 *record)
{
    sceneLoadTextureAndDataPair(&record->unkC);
    record->unk8 = func_80126890(record->unk4);
}
