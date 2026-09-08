#include "common.h"

extern s32 func_80018044(void *, void *, s32, s32);
extern u8 D_80018B20[];
extern u8 D_80018E34[];

/* Call func_80018044 with the global buffers and the first and third arguments. */
s32 func_80016968(s32 first_value, s32 unused, s32 second_value)
{
    return func_80018044(D_80018B20, D_80018E34, first_value, second_value);
}
