#ifndef SLUS_COMMAND_WORDS_H
#define SLUS_COMMAND_WORDS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"


typedef struct {
    s32 field_0;
    s32 field_4;
} S_80053CFC;

extern void Control_CD(s32 command_code, void *command_ptr, s32 value);
extern void func_8003F320(void);
extern s32 D_80081568;
extern s32 D_8008156C;

/* Builds and submits a command from the source fields and packed value. */

void func_80053CFC(S_80053CFC *source, s32 packed_value);

#endif
