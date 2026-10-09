#include "common.h"

extern s32 func_800AB538(void *, void *, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void func_80173504(void *state, void *context, void *data, void *extra_data)
{
    func_800AB538(state, context, data, extra_data);
}
