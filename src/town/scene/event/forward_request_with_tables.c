#include "common.h"
#include "town/scene/entry_requests.h"

extern s32 func_80018044(void *, void *, s32, s32);
extern u8 D_80018B20[];
extern u8 D_80018E34[];

/* Call func_80018044 with the global buffers and the first and third arguments. */
s32 dispatch_scene_request_with_tables(s32 request, s32 unused, s32 value)
{
    return func_80018044(D_80018B20, D_80018E34, request, value);
}
