#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 func_800990FC(void);
extern s32 func_80099194(void *src, s32 dst);
extern void func_80099290(s32 byte_ptr);
extern s32 func_80099734(s32 record, s32 out);
extern void func_800A5720(s32 text);
/* Adjusts a computed value for application to the source and finalizes the original value. */
void func_80099844(s32 context, void *source, s32 first_input, s32 second_input)
{
    void *source_copy;
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;
    adjusted_value = func_80099734(context, current_value = func_800990FC());
    original_value = current_value;
    current_value = adjusted_value;
    func_80099290(func_80099194(source_copy = source, current_value));
    func_800A5720(original_value);
}
