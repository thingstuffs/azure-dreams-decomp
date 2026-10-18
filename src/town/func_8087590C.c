#include "common.h"

typedef struct { s32 words[15]; } State;
extern State D_80701964;
void copy_indexed_flag_words(State *state) { D_80701964 = *state; }
