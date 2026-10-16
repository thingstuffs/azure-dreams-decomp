#include "common.h"

typedef struct { s32 words[15]; } State;
extern State D_80701964;
void func_8070190C(State *state) { D_80701964 = *state; }
