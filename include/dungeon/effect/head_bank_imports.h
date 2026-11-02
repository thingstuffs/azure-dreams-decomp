#ifndef DUNGEON_EFFECT_HEAD_BANK_IMPORTS_H
#define DUNGEON_EFFECT_HEAD_BANK_IMPORTS_H
/*
 * Imports of the effect code at the head of the DUNGEON file (+0x0..+0x15000; check-only rows registered at the
 * 0x7FFE0000 placeholder, func_7FFExxxx).  It was linked against another build: its calls into the executable
 * (spelled func_7003xxxx / func_7006xxxx / func_7007xxxx, the jal target's low 28 bits under the placeholder's
 * upper nibble, and func_8003xxxx) are mid-function or data in the retail SLUS, and its calls to 0x8010xxxx /
 * 0x7010xxxx reach nothing any image or load region covers.  Each import is declared once here with its address
 * spelling, so the call keeps its bytes.
 *
 * foreign-program: dungeon 0x0-0x15000
 */
#include "common.h"

/* --- imports (tools/headers/foreign_imports.py): one declaration per address --- */
void func_7003A7C4(void *, void *, s32);
void *func_7003CF18(s32);
void func_70040A18(void *, void *);
s32 func_7006DC5C(s32);
s32 func_7006DD28(s32);
s32 func_700750E0(void);
s32 func_7010AE28(void *, void *, void *, s32);
void func_7010B30C(void *, void *, void *, s32);
s32 func_7010B864(void *, void *, void *, s32);
s32 func_7010BD54(void *, void *, void *, s32);
s32 func_7010C274(void *, void *, s32, s32);
s32 func_7010C7A8(void *, void *, s32, s32);
s32 func_7010CD00(void *, void *, s32, s32);
void func_7010D230(void *, void *, s32, s32);
void func_7010D810(void *, void *, void *, s32);
void func_8003A7C4(void *, void *, u32);
void *func_8003CF18(u32);
void D_8010B008(void);
void func_8010BB90(void);
void func_8010C0F8(void);
void func_8010D440(void);
/* --- end of imports --- */

#endif
