#include "common.h"

#include "common.h"

typedef s8 s8_local;

typedef struct S_80037030_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void ** unk_10;
} S_80037030_0;   /* arg0 in func_80037030 */

typedef struct S_80037030_1 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_80037030_1;   /* call_arg2 in func_80037030 */



extern void func_80036D4C(s32, void *, s32 *, s16, s32, s32);
extern void func_80037090(void *, void *, void *);

/* Initialize the object, install its color update callback, and run it once. */
void func_80037030(void *object, void *model, s32 *data, s16 index, s16 table_index, s32 list) {
    void *state;
    void *context;
    S_80037030_1 *output;

    func_80036D4C((s32)object, model, data, index, table_index, list);
    state = (s8_local *)object + 0x20;
    context = ((S_80037030_0 *)object)->unk_08;
    output = ((S_80037030_0 *)object)->unk_0C;
    ((S_80037030_0 *)object)->unk_10 = (void *)&func_80037090;
    output->unk_0C = 0;
    func_80037090(state, context, output);
}
