## Stock-compiler objects (round 84; read work/native_lane/r84_fable_build/REPORT.md and r84_opus_stock/REPORT.md)
These rows belong to REAL stock-compiler objects (Sony/devkit card code, the devkit blob, the town gym/survival
minigame image): FSF `2.6.3` / stock `2.7.2` (with -G0 where registered) - work them at the row's proven stock recipe
(VERDICT.tsv `proven_TU_recipe` in r84_fable_build), never at cdk. Stock cells do not split addresses and have no
cygnus loop/sched changes. Earlier lanes fitted their pins in cdk terms. r84_opus_stock solved 6 of 7 such rows with
PLAIN Sony-style statements - in 4 of 6 the old text had split one statement into extra locals:
- a register-pinned local that only copies an s32 parameter -> use the parameter directly;
- `ASM_REG` on `field | K` with K a local set before the if (a delay-slot fill read back as C) -> `ptr->field |= LITERAL;`
  inside the arm;
- a pinned constant stored to adjacent fields -> write the stores in ascending field-offset order;
- `ASM_USE2` on locals feeding a call -> pass the arguments directly; loop inits at the loop head;
- `ASM_KEEP` on a returned value of a 2.6.3 object row registered at 2.7.2 (often with `packed`) -> u8-struct copy,
  score at 2.6.3(-G0) (2.6.3 reorg never fills the epilogue slot with the return move; 2.7.2 does);
- 2.6.3 sched.c birthing boost: a value set once and live at block end gets top priority (8001BA1C still open on it).
Diff the row against an exact pin-free sibling of the same object before guessing.
