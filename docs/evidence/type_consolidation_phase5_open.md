# Phase 5 open items (orchestrator, 2026-09-28)

Excluded from apply5 (BUSY_ROWS5.txt): slus/w_8003D8B0, slus/w_8003F80C, slus/w_8004D614.
Cause (measured): their candidates reference `D_80082E80` BY NAME (via include/shared/tile_object.h). The SLUS
symbol file (build_slus/config/generated/slus_006.14.undefined_syms.txt, from tools/build/configure.py `US`) has
NO entry for D_80082E80 - no SLUS source named it before - so the SLUS link fails (`FAILED:
build/slus_006.14.elf`). Per-row verify.py passed for two of them (object identity does not link); w_8004D614's
plural partition build links, so it failed at verify. Fix: define D_80082E80 = 0x80082E80 for the SLUS link the
way other SLUS data symbols are defined (find where configure.py builds the US list), gate the SLUS image, then
re-run apply5.sh for these three rows (it is resumable). Check other data symbols the shared headers may
introduce into SLUS for the first time (D_80083780 already links: w_8004D5D0 landed).
