/* config/noreturn_evidence.main.c -- TRACKED noreturn evidence for the `main`
 * family census (config/noreturn_syms.txt, written by tools/gen_noreturn_syms.py).
 *
 * THIS FILE IS NEVER COMPILED AND MUST NEVER BE #included.
 * It is scanned, and only scanned, by tools/gen_noreturn_syms.py (its glob is
 * listed in CONTAINERS["main"]["globs"]).  It is a declaration-only evidence
 * source, exactly like a landed TU's own `extern ... __attribute__((noreturn));`
 * line -- symbol-level truth about a callee, not a per-caller rule.
 *
 * WHY THE DECLARATIONS CANNOT LIVE IN THE CALLER TUs (the load-bearing reason).
 * Every symbol below is a genuine zero-arg noreturn callee, and each of the
 * seven MAIN.BIN rows that call it needs maspsx LEAD 18 to rewrite its `jal SYM`
 * into retail's tail `j SYM`.  That rewrite needs the census.  But the converted
 * `j` still has a delay slot, and retail fills it with the instruction that
 * FOLLOWS the call in the caller's own source (a `var_s1++`, a pointer bump, a
 * `move $s0,$v0`).  If the caller TU carried the `__attribute__((noreturn))`
 * itself, gcc would know the call never returns, delete that trailing
 * instruction as dead, and the delay slot would come back as `nop` -- the row
 * would stop matching for a different reason.  Three of the seven TUs say so in
 * a code comment (quoted per symbol below).  So the declaration has to exist
 * SOMEWHERE TRACKED, and it cannot be in the TU that needs it: this file is that
 * somewhere.
 *
 * HISTORY.  These seven were census members from their landings (2026-07-09 ..
 * 2026-08-24) until commit 337355ce (2026-09-01) correctly cut the census's
 * untracked `work/overlay_wave/candidates_*` scan globs -- which happened to be
 * their ONLY source.  All seven rows silently stopped rebuilding byte-exact
 * (`jal` where retail has `j`) and MAIN.BIN stopped rebuilding in the
 * `main_boot` window.  Root cause + bisect:
 * work/bridge_remediation_20260905/E_maspsx_drift/REPORT.txt.  This file
 * restores the fact through a tracked, reviewable source, which is what
 * 337355ce's `_assert_tracked_source_globs` hardening asks for.
 *
 * EVIDENCE STANDARD.  Every line below carries a RETAIL BYTE DECODE of
 * work/s3_splat/extract/MAIN_MAIN.BIN (md5 4cb19f1855cc7c0d485f5f55cbf6d77e):
 * the container-wide count of `j SYM` vs `jal SYM` words.  All seven are
 * `j`-ONLY with ZERO `jal` anywhere in the container -- i.e. no caller anywhere
 * in MAIN.BIN uses a return value, so none of them is a
 * config/noreturn_false_members.jsonl CLASS 1 "both-ways" symbol.  No file under
 * src/ (the SLUS EXE half of the `main` family) names any of them, so no
 * main-EXE TU is affected either.
 */

/* func_8040680C -- retail MAIN.BIN: 1 `j` (foff 0x26F7F8), 0 `jal`.
 * The single site is word 15 of landed row func_8001F7BC (true func_804067BC),
 * whose own source says: "func_8040680C is a known zero-arg noreturn
 * (config/noreturn_syms.txt); it is NOT annotated here so gcc keeps the trailing
 * var_s1++ live for the fall-through merge. maspsx then rewrites the jal into a
 * tail `j` and the (semantically dead) increment fills the converted j's delay
 * slot exactly as retail." (overlays/main/first_pass_matched/func_8001F7BC.c:6-9) */
extern void func_8040680C(void) __attribute__((noreturn));

/* func_80025E18 -- retail MAIN.BIN: 1 `j` (foff 0x262E04), 0 `jal`.
 * Word 15 of landed row func_80012DC8 (true func_80025DC8), which declares it
 * `extern void func_80025E18(void);` WITHOUT the attribute and keeps the pointer
 * bump alive across the call with its own KEEP_VALUE(p) asm barrier -- the same
 * delay-slot-filler idiom, spelled with a barrier instead of a comment.
 * (overlays/main/first_pass_matched/func_80012DC8.c:3-12,26) */
extern void func_80025E18(void) __attribute__((noreturn));

/* func_80405C0C -- retail MAIN.BIN: 2 `j` (foff 0x26EBD4, 0x26EBF8), 0 `jal`.
 * Both sites are words 15 and 24 of landed row func_8001EB98 (true
 * func_80405B98), which declares it plain and relies on the census; its trailing
 * `var_s1++` fills each converted j's delay slot.
 * (overlays/main/first_pass_matched/func_8001EB98.c:7,20,25) */
extern void func_80405C0C(void) __attribute__((noreturn));

/* func_80405B5C -- retail MAIN.BIN: 1 `j` (foff 0x26EB48), 0 `jal`.
 * Word 24 of landed row func_8001EAE8 (true func_80405AE8), whose own source
 * says: "noreturn only via config/noreturn_syms.txt so maspsx jal->j keeps delay
 * fill" and marks the site "no return: fall through is dead; avoids j-epilogue
 * after tail j". (overlays/main/first_pass_matched/func_8001EAE8.c:6-7,27-30) */
extern void func_80405B5C(void) __attribute__((noreturn));

/* func_8002515C -- retail MAIN.BIN: 2 `j` (foff 0x262124, 0x262148), 0 `jal`.
 * Words 15 and 24 of landed row func_800120E8 (true func_800250E8), which
 * declares it plain and lets the following `entry += 4` fill each delay slot.
 * (overlays/main/first_pass_matched/func_800120E8.c:7,19-20,24-25) */
extern void func_8002515C(void) __attribute__((noreturn));

/* func_804021F4 -- retail MAIN.BIN: 1 `j` (foff 0x26B1DC), 0 `jal`.
 * Word 34 of landed row func_8001B154 (true func_80402154), which declares it
 * plain; the trailing `func_8007BF18(D_80400138)` argument load fills the slot.
 * (overlays/main/first_pass_matched/func_8001B154.c:7,24) */
extern void func_804021F4(void) __attribute__((noreturn));

/* func_80027B6C -- retail MAIN.BIN: 1 `j` (foff 0x264B44), 0 `jal`.
 * Word 18 of landed row func_80014AFC (true func_80027AFC), whose own source
 * says: "Intentionally NOT noreturn: fallthrough to the shared success path
 * keeps `node = func_8003FE78(...)` live so gcc schedules `move $s0,$v0` into
 * the jal's delay slot. config/noreturn_syms.txt still drives LEAD 18 jal->j."
 * (overlays/main/first_pass_matched/func_80014AFC.c:27-30) */
extern void func_80027B6C(void) __attribute__((noreturn));
