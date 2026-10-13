#ifndef SHARED_SCRATCHPAD_H
#define SHARED_SCRATCHPAD_H
#include "common.h"
/* PS1 1 KB scratchpad RAM at 0x1F800000. Halfword and word accesses
 * address the same storage; the base remains explicit at each caller. */
typedef union ScratchPad { u8 b[0x400]; s8 sb[0x400]; u16 h[0x200]; s16 sh[0x200]; u32 w[0x100]; s32 sw[0x100]; } ScratchPad;
#endif
