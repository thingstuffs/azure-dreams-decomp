#ifndef COMMON_H
#define COMMON_H

/* Put each INCLUDE_ASM'd function in its own .text.<name> section so the linker
 * can sort all functions (C + asm, across multi-compiler TU files) back into
 * address order via SORT_BY_NAME(.text.func_*). Defined here (not in the
 * splat-regenerated include_asm.h) so a re-split can't clobber it; the guard
 * makes include_asm.h skip its own plain-.text definition. */
#if !defined(M2CTX) && !defined(PERMUTER)
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__( \
        ".section .text." #NAME ",\"ax\",@progbits\n" \
        "    .set noat\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )
#endif

/* Match-only register scaffolding (portability contract — see RUNBOOK).
 * A MIPS hardware-register pin (`register T v asm("$N")`) forces the register
 * allocation a byte-exact match needs, but the register name is MIPS-specific
 * and does NOT cross-compile: x86 gcc rejects it the moment the pinned value is
 * used as an inline-asm operand. Guard such pins so the port build
 * (-DNON_MATCHING) compiles portable plain C:
 *     register int v ASM_REG("$2");   // match: pins $v0 ; port: `register int v;`
 *     ASM_KEEP(v);                     // match: liveness/reschedule barrier ; port: no-op
 * Prefer a pure-C shape that doesn't need a pin at all; reach for these ONLY
 * when the register choice is genuinely forced. Emitting real instructions via
 * inline asm (`__asm__("lhu ...")`) is never allowed — that transcribes the
 * target (tools/match.py downgrades it to NO MATCH). */
#ifdef NON_MATCHING
#define ASM_REG(reg)
#define ASM_KEEP(var)   ((void)0)
#define ASM_KEEP_NV(var) ((void)0)
#define ASM_KEEP_DEP_NV(var, dep) ((void)(dep))
#define ASM_KEEP_MEMDEP(var, scratch, mem) ((void)(mem))
#define ASM_KEEP_MEMDEP_NV(var, scratch, mem) ((void)(mem))
#define ASM_KEEP_MEM_NV(var, mem) ((void)(mem))
#define ASM_KEEP4(a, b, c, d)     ((void)0)
#define ASM_KEEP4_NV(a, b, c, d)  ((void)0)
#define ASM_CLOBBER(reg) ((void)0)
#define ASM_SET(var)     ((void)0)
#else
#define ASM_REG(reg)    asm(reg)
/* "=r"(v) with a "0" input tie is the portable spelling of "+r"(v): identical
 * semantics, but gcc 2.7.x rejects the `+` constraint outright ("output
 * operand constraint contains `+`") while every gcc we use accepts the tied
 * form. Verified byte-identical across the full landed corpus (sha1 gate) at
 * the 2026-07-21 change. */
#define ASM_KEEP(var)   __asm__ __volatile__("" : "=r"(var) : "0"(var))
/* ASM_KEEP_NV -- NON-VOLATILE variant of ASM_KEEP, kept as a SEPARATE spelling
 * (never a replacement): the volatile in ASM_KEEP is a sched2 SCHEDULING
 * BARRIER that serialises the surrounding basic block, and on some rows that
 * barrier itself is the residue. The save-scatter family audit (2026-07-29,
 * w76_flight_fixes/family_save_scatter) proved retail's interleaved
 * callee-save order is plain sched2 output; a volatile keep sinks the paired
 * `move $sN,$aM` and drags its `sw $sN` down with it. ASM_KEEP_NV keeps the
 * copy-propagation pin (tied output is live-used, so DCE keeps it where the
 * value is used) WITHOUT the barrier. Exemplar: func_809F66D8 (dungeon,
 * byte-exact 208/208 with exactly one site respelled _NV; blanket
 * de-volatilisation regressed 30/59 exposed rows -- per SITE, like the
 * ASM_TAILSLOT_PIN_TIED precedent). If the kept value is otherwise dead, gcc
 * MAY delete a non-volatile keep -- that is its documented semantic; use
 * ASM_KEEP for dead-value retention. Port build (-DNON_MATCHING) compiles it
 * away identically. */
#define ASM_KEEP_NV(var) __asm__("" : "=r"(var) : "0"(var))
/* ASM_KEEP_DEP_NV -- ASM_KEEP_NV plus one EXTRA read-only input. Same tied
 * "=r"/"0" copy-propagation pin on `var`, but the asm also READS `dep`, so the
 * pin cannot be scheduled above dep's definition. Use when the residue is an
 * ORDER between two independent values (typically a page base and the pointer
 * derived from it) that a bare keep on either one alone does not fix: with two
 * separate keeps gcc is free to re-order them, and a volatile keep over-fences
 * the block (the ASM_KEEP/ASM_KEEP_NV split at @61). Provenance: func_81326938
 * (dungeon, byte-exact @2.7.2-cdk-G0 -- copy_src tied with copy_page as the
 * dep) and func_80D150D0 (dungeon, byte-exact @2.7.2-G0 -fno-schedule-insns --
 * body_link tied with mesh_flags), both of which hand-rolled this exact
 * fragment. Non-volatile like ASM_KEEP_NV: if `var` is otherwise dead gcc MAY
 * delete it. Port build (-DNON_MATCHING) keeps `dep` referenced and compiles
 * the pin away. */
#define ASM_KEEP_DEP_NV(var, dep) __asm__("" : "=r"(var) : "0"(var), "r"(dep))
/* ASM_KEEP_MEMDEP -- ASM_KEEP on `var` JOINED, in ONE empty asm, with (a) a
 * MEMORY input naming a global object `mem` and (b) an EARLY-CLOBBER scratch
 * output `scratch` (in practice an ASM_REG-pinned local naming the register
 * retail did NOT use for the symbol page). Emits zero bytes.
 * Purpose: the pre-prologue SYMBOL-PAGE SPLIT. Retail/ASPSX materialises
 * `lui $vA,%hi(G); lw $vB,%lo(G)($vA)` BEFORE frame setup and keeps the page
 * register $vA alive for a later `addiu $sN,$vA,%lo(G)`, i.e. the page and the
 * loaded pointer live in DIFFERENT caller regs. gcc-2.8.x instead re-uses one
 * register for both and sinks the pair below the prologue. The "m" operand is
 * what forces the %hi page to be materialised at this point (a plain "r" dep on
 * the loaded value does not -- verified: dropping it costs 9 words), and the
 * early-clobber output is what keeps the page out of the scratch register, so
 * the two land in retail's opposite colours. Neither half alone reproduces it,
 * and separate ASM_KEEP/ASM_SET statements do not either (they let the two
 * pseudos' live ranges end independently) -- hence the joint spelling, exactly
 * as for ASM_KEEP4 @80. `scratch` is write-only and indeterminate afterwards:
 * use a local that is dead at this point. Volatile, like ASM_KEEP: the barrier
 * is part of the effect (it is what holds the pair above the prologue).
 * Provenance: func_819611CC (dungeon, byte-exact @2.8.1-G0 -- spad tied,
 * page_color ASM_REG("$2") as the scratch, *(u8 **)D_80083160 as the memory
 * object; the row sat at aligned 5-9 for six lanes on this residue alone).
 * Port build (-DNON_MATCHING) keeps `mem` referenced and compiles the pin
 * away. */
#define ASM_KEEP_MEMDEP(var, scratch, mem) \
    __asm__ __volatile__("" : "=r"(var), "=&r"(scratch) : "0"(var), "m"(mem))
/* ASM_KEEP_MEMDEP_NV -- NON-VOLATILE sibling of ASM_KEEP_MEMDEP, kept as a
 * SEPARATE spelling exactly as ASM_KEEP_NV is to ASM_KEEP (@51): same joint
 * tied-keep + "m" symbol-page input + early-clobber scratch, WITHOUT the
 * sched2 barrier. Use when the page register must be materialised at a
 * given point in the pre-prologue stream but the volatile form over-fences
 * the block (it drags the remaining callee saves / arg moves along with it).
 * Provenance: func_800B6D74 (dungeon, true base func_800BC4D4, @2.8.1-G0):
 * the volatile form sat at aligned 2 for four lanes -- retail emits
 * `lui $v1,%hi(D_80083160)` immediately after the second scratch-pointer
 * setup, three words above where the volatile keep can place it -- and the
 * non-volatile dependency moves that ONE word into retail position with the
 * other 356 instructions unperturbed. Non-volatile like ASM_KEEP_NV: if `var`
 * is otherwise dead gcc MAY delete it. Port build (-DNON_MATCHING) keeps `mem`
 * referenced and compiles the pin away. */
#define ASM_KEEP_MEMDEP_NV(var, scratch, mem) \
    __asm__("" : "=r"(var), "=&r"(scratch) : "0"(var), "m"(mem))
/* ASM_KEEP_MEM_NV -- single-output sibling of ASM_KEEP_MEMDEP_NV: the same
 * tied keep + "m" symbol-page input WITHOUT the early-clobber scratch.
 * Why a separate spelling: the two-output PARALLEL form carries NO LOG_LINK
 * for its tied input or for the register inside its "m" address, so a
 * (lo_sum) that feeds the "m" operand keeps INSN_PRIORITY 1 and is placed at
 * its earliest legal slot; the single-SET form acquires that dependence and
 * pulls the %lo addiu to the asm's own slot. Provenance: func_800C9858
 * (dungeon, true name func_800CEFB8, @2.8.1-G0), close_800C9858_6: retail's
 * `move a3,a0` at word 35 and `addiu s7,t0,%lo(D_80083160)` at word 41
 * straddle one volatile fence that no MEMDEP placement satisfies (66 probes
 * flat at 9); the sched2 dump shows the addiu at retail's word 41 once the
 * asm carries the dependence. Non-volatile like ASM_KEEP_NV. Port build
 * (-DNON_MATCHING) keeps `mem` referenced and compiles the pin away. */
#define ASM_KEEP_MEM_NV(var, mem) \
    __asm__("" : "=r"(var) : "0"(var), "m"(mem))
/* ASM_KEEP4 / ASM_KEEP4_NV -- four-value JOINT keep in ONE empty asm, the
 * ASM_KEEP analogue of ASM_USE2's joint form @177: four separate ASM_KEEP
 * statements put three scheduling boundaries between the pins and let each
 * value's live range end independently, which is not the same barrier. The
 * whole group is pinned live at exactly one point. Written in the tied
 * "=r"/"0..3" spelling rather than "+r" because gcc 2.7.x rejects `+`
 * outright (see @44); verified byte-identical to the "+r" form on the
 * provenance row. Provenance: func_800B998C (town, byte-exact @2.8.1-G0,
 * volatile form) and func_80C16F00 (dungeon, byte-exact @2.7.2-cdk-G0,
 * _NV form). Volatile vs not is per SITE, exactly as for ASM_KEEP/_NV.
 * Port build (-DNON_MATCHING) compiles them away. */
#define ASM_KEEP4(a, b, c, d) \
    __asm__ __volatile__("" : "=r"(a), "=r"(b), "=r"(c), "=r"(d) \
                            : "0"(a), "1"(b), "2"(c), "3"(d))
#define ASM_KEEP4_NV(a, b, c, d) \
    __asm__("" : "=r"(a), "=r"(b), "=r"(c), "=r"(d) \
               : "0"(a), "1"(b), "2"(c), "3"(d))
/* Portable register clobber (forces reload / blocks caching of `reg`), the
 * sanctioned form of the hand-rolled `__asm__("" : : : "$4")` pins that wave
 * candidates kept reinventing. Pass the register as a string: ASM_CLOBBER("$4") */
#define ASM_CLOBBER(reg) __asm__ __volatile__("" : : : reg)
/* ASM_SET -- a compiler-visible SECOND SET of `var` that emits zero bytes: a
 * volatile write-only output with NO tied input (the tie in ASM_KEEP adds two
 * references and rotates the colouring -- measured on the provenance row).
 * Purpose: defeat sched1 adjust_priority's "birthing" bump, which is gated on
 * reg_n_sets == 1 (sched.c); a second set disqualifies the pseudo. This is NOT
 * expressible in ordinary C: any cheaper spelling is folded by cse before
 * flow.c counts sets (foldable => no set survives; un-foldable => it emits an
 * instruction), and combine's i2dest_in_i2src escape is never reached -- the
 * full derivation with the 38-candidate enumeration is
 * work/main_endgame_20260818/solve_wave5_final/ba1c_p2/mine/FINDINGS.md.
 * After the asm, `var`'s value is indeterminate: use only on values that are
 * dead at that point. Provenance: func_8001BA1C (main, byte-exact @2.7.2-G0,
 * the only asm-guarded row in MAIN). Port build (-DNON_MATCHING) is a no-op. */
#define ASM_SET(var) __asm__ __volatile__("" : "=r"(var))
#endif

/* LEAD 27 page-base tail-slot pin. Retail/ASPSX rematerialises a DEAD page base
 * into the delay slot of a noreturn/sibcall tail `j`; gcc-2.8.x shares one page
 * base across the branch and DCEs the rest, so nothing exists in gcc's stream to
 * reschedule and the dead fill must be MATERIALISED in C. Assign the page
 * constant (`page = 0xPPPP0000;`) into a pinned `register u32 ASM_REG("$2")`
 * AFTER the last intervening call, then ASM_PAGEBASE_PIN(page) right before the
 * tail call. Like ASM_KEEP it keeps `page` live across the barrier, but it ALSO
 * emits a reserved marker comment `#maspsx_pagebase_pin $R` naming the pinned
 * register. maspsx's _sink_dead_pagebase_into_tail_j_delay pass keys on that
 * marker to relocate ONLY genuinely-pinned bare luis into the tail-j slot --
 * never a natural `0xNNNN0000` mask constant, which carries no marker. gcc never
 * emits this token, so the marker is unforgeable by natural output. Port build
 * (-DNON_MATCHING) compiles it away. */
#ifdef NON_MATCHING
#define ASM_PAGEBASE_PIN(var)   ((void)0)
#else
#define ASM_PAGEBASE_PIN(var)   __asm__ __volatile__("#maspsx_pagebase_pin %0" : "+r"(var))
#endif

/* LEAD 28 tail-slot dead-value pin -- generalises the LEAD 27 page-base pin from
 * a bare `lui`/`li` to ANY dead value ASPSX rematerialises into a converted
 * noreturn/sibcall tail-`j` delay slot (e.g. a dead dispatch `addu $v0,$v0,$a1`,
 * base+index, that the callee ignores). gcc-2.8.x parks such a dead value
 * STANDALONE before the tail call and schedules the last call arg-move into the
 * branch delay instead; retail parks the dead value in the branch delay and
 * pulls the arg-move up into an earlier load-delay nop. Compute the dead value
 * into a pinned `register T v ASM_REG("$N")` AFTER the last intervening call,
 * then ASM_TAILSLOT_PIN(v) right before the tail call. Like ASM_KEEP it keeps
 * `v` live across the barrier; it ALSO emits the reserved marker comment
 * `#maspsx_tailslot_pin $R` naming the pinned register, on which maspsx's
 * _rotate_dead_value_into_tail_j_delay pass keys to sink ONLY genuinely-pinned
 * dead values into the tail-j delay slot (rotating the displaced arg-move up
 * into the load-delay). gcc never emits this token, so the marker is unforgeable
 * by natural output; a stray marker is a byte-neutral `#` comment. Port build
 * (-DNON_MATCHING) compiles it away. */
#ifdef NON_MATCHING
#define ASM_TAILSLOT_PIN(var)   ((void)0)
#else
#define ASM_TAILSLOT_PIN(var)   __asm__ __volatile__("#maspsx_tailslot_pin %0" : "+r"(var))
#endif

/* Evidence-scoped live sibcall pin.  Unlike ASM_TAILSLOT_PIN, the value is
 * live in a post-call continuation that gcc retains.  The paired per-TU
 * maspsx control converts only a proven sibcall, moves an identical constant
 * out of the predecessor branch delay, and materialises it in the tail-j
 * delay.  A separate marker prevents existing dead-value pins from opting in. */
#ifdef NON_MATCHING
#define ASM_LIVE_SIBCALL_PIN(var, imm)   ((void)0)
#else
#define ASM_LIVE_SIBCALL_PIN(var, imm) \
    __asm__ __volatile__("#maspsx_live_sibcall_pin %0," #imm : "+r"(var))
#endif

/* LEAD 29 SHAPE-D explicit live-continuation sibcall pin.  Place this
 * immediately before the intended C438 call.  The caller name, retail site
 * address, and direct callee are authenticated by maspsx; membership alone
 * never enables this conversion.  The port build erases the marker. */
#ifdef NON_MATCHING
#define ASM_SHAPE_D_SIBCALL_PIN(caller, site, callee)   ((void)0)
#else
#define ASM_SHAPE_D_SIBCALL_PIN(caller, site, callee) \
    __asm__ __volatile__("#maspsx_shape_d_pin " #caller "," #site "," #callee)
#endif

/* ASM_TAILSLOT_PIN_TIED -- tied-operand spelling of ASM_TAILSLOT_PIN, kept as a
 * SEPARATE variant (not a replacement) because the two are NOT interchangeable
 * for this pin. "+r"(v) and "=r"(v) with a "0"(v) input tie are semantically
 * identical, but gcc lowers them through different RTL and the resulting
 * tail-slot schedule can diverge: the ~40 landed ASM_TAILSLOT_PIN callers matched
 * with the "+r" form, while func_808B32AC (town, census-exact @2.7.2) REGRESSES
 * under "+r" and is byte-exact ONLY with the tied form (same disease as the
 * 800AB37C volatile park). Three wave lanes independently hand-rolled this exact
 * raw fragment for the tailslot trio (func_810886D4 / func_808B32AC /
 * func_808755AC); the portability lint rightly refuses the literal
 * `#maspsx_tailslot_pin` template as an instruction fragment, so the exact could
 * not land without a sanctioned spelling. Same unforgeable
 * `#maspsx_tailslot_pin $R` marker and %0 register naming as ASM_TAILSLOT_PIN, so
 * maspsx's _rotate_dead_value_into_tail_j_delay pass keys and fires identically
 * (%0 is the output = the tied register). Port build (-DNON_MATCHING) compiles it
 * away. Prefer ASM_TAILSLOT_PIN first; reach for _TIED only when the "+r" form
 * regresses the tail-slot schedule. */
#ifdef NON_MATCHING
#define ASM_TAILSLOT_PIN_TIED(var)   ((void)0)
#else
#define ASM_TAILSLOT_PIN_TIED(var)   __asm__ __volatile__("#maspsx_tailslot_pin %0" : "=r"(var) : "0"(var))
#endif

/* LEAD 30 jal-delay store pin -- the first marker in this family that governs a
 * REAL call instead of a converted tail `j`. ASPSX's schedule can hold a store of
 * an ALREADY-LOADED value pending until a `jal`'s delay slot, AFTER every outgoing
 * stack argument has been written, keeping the last argument store in front of the
 * call. gcc's dbr does the opposite at every pinned compiler (2.7.2 / 2.7.2-cdk /
 * 2.8.x and genuine PsyQ 4.4 cc1): it emits the store the moment its input is
 * ready and fills the delay slot with the last argument store. Same instruction
 * multiset, same registers, same length -- one rotation apart. Write the store
 * normally, then put ASM_JALDELAY_PIN(v) on the STORED VALUE anywhere between the
 * store and the call. Like ASM_USE_NV @220 it is an input-only, NON-VOLATILE
 * liveness tail: no DEF to rewrite the value's identity and no scheduling barrier
 * (both volatile spellings and the tied "=r"/"0" spelling were measured on the
 * provenance row -- volatile reshapes the whole block to 295 words / 9 aligned
 * edits, and the tied non-volatile form is DELETED outright because the pinned
 * value is dead after its store). It ALSO emits the reserved marker comment
 * `#maspsx_jaldelay_pin $R` naming the value's register, on which maspsx's
 * _rotate_marked_store_into_jal_delay pass keys to rotate ONLY genuinely-pinned
 * stores into the next call's delay slot (the displaced filler is lifted in front
 * of the call; the word count is unchanged). gcc never emits this token, so the
 * marker is unforgeable by natural output; a stray marker is a byte-neutral `#`
 * comment -- genuine ASPSX 2.67/2.77/2.79/2.86 assemble the marked and unmarked
 * streams to identical bytes.
 * THIS IS AN OPT-IN LEVER, NOT AN ASSEMBLER-EMULATION FIX: no shipped ASPSX
 * performs the rotation (measured, same four versions), so it must never be
 * reached for without a retail witness that actually shows the store in the delay
 * slot. Provenance: func_800463EC (MAIN, byte-exact 294/294 @2.7.2-cdk -O2, the
 * RotAverage4 call). Port build (-DNON_MATCHING) compiles it away. */
#ifdef NON_MATCHING
#define ASM_JALDELAY_PIN(var)   ((void)(var))
#else
#define ASM_JALDELAY_PIN(var)   __asm__("#maspsx_jaldelay_pin %0" : : "r"(var))
#endif

/* LEAD 31: opt one source edge into maspsx's direct-address label split.  The
 * marker is comment-only; the pass additionally requires the exact adjacent
 * slt/zero-test branch and matching lui/addiu target shape. */
#ifdef NON_MATCHING
#define ASM_BRANCH_LABEL_SPLIT(var)   ((void)(var))
#else
#define ASM_BRANCH_LABEL_SPLIT(var) \
    __asm__("#maspsx_branch_label_split %0" : : "r"(var))
#endif

/* Zero-operand scheduling barrier. ASM_KEEP(v)'s "+r" operand REWRITES v's
 * identity: a pointer-to-global routed through it stops being CSE-constant, so
 * RTL canonicalization no longer orders it as the constant addend and a
 * commutative op's operands rotate against retail (gap probe func_80FDB6A8:
 * the one-word addu rs/rt swap was induced by the keep itself). When only the
 * barrier POSITION is load-bearing (blocking gcc dbr/reorg from stealing an
 * insn into a branch delay slot) and no value needs its liveness extended, use
 * this instead: same reorg fence, zero register footprint, operand identities
 * untouched. Port build (-DNON_MATCHING) compiles it away. */
#ifdef NON_MATCHING
#define ASM_SCHED_BARRIER()     ((void)0)
#else
#define ASM_SCHED_BARRIER()     __asm__ __volatile__("")
#endif

/* ASM_MEM_BARRIER(): ASM_SCHED_BARRIER plus a "memory" clobber — a full
 * optimization fence: gcc must complete every pending store and forget every
 * cached memory value at this point (loads after it re-read memory). Use when
 * retail's schedule requires store/load ordering across a point that no
 * volatile qualification reproduces without cascading regressions (provenance
 * func_800BB400, fable tranche-1 2026-07-24: byte-exact @2.8.1 with the fence
 * between two RMW &=-8 stores and the event[0] load; ASM_SCHED_BARRIER @141,
 * volatile-load @141, volatile-store @162 — only the memory clobber holds the
 * whole tail's shape). Prefer volatile/ASM_SCHED_BARRIER first: this is the
 * bluntest fence and over-firing it reshapes everything downstream. Port
 * build (-DNON_MATCHING) compiles it away. */
#ifdef NON_MATCHING
#define ASM_MEM_BARRIER()       ((void)0)
#else
#define ASM_MEM_BARRIER()       __asm__ __volatile__("" : : : "memory")
#endif

/* ASM_USE(var): input-only liveness tail — extends var's live range to this
 * point WITHOUT a second DEF (ASM_KEEP's "+r" DEF reorders sched2 entry
 * groups; the "r"-only form does not — probe 81031F30, 2026-07-19). Use to
 * stop local-alloc tying a computed temp to a dying input. Port build
 * compiles it away. */
#ifdef NON_MATCHING
#define ASM_USE(var)            ((void)(var))
#define ASM_USE2(a, b)          ((void)(a), (void)(b))
#define ASM_USE_NV(var)         ((void)(var))
#define ASM_USE2_NV(a, b)       ((void)(a), (void)(b))
#define ASM_USE_G_NV(var)       ((void)(var))
#define ASM_UNDEF(var)          ((void)0)
#else
#define ASM_USE(var)            __asm__ __volatile__("" : : "r"(var))
/* Two-input liveness tail in ONE empty asm (two ASM_USE statements would put a
 * scheduling boundary between the reads; candidates needed the joint form). */
#define ASM_USE2(a, b)          __asm__ __volatile__("" : : "r"(a), "r"(b))
/* ASM_USE_NV / ASM_USE2_NV -- NON-VOLATILE spellings of the liveness tails,
 * kept as SEPARATE variants (never replacements), same per-SITE rule as
 * ASM_KEEP/ASM_KEEP_NV @61. Modern gcc documents an operand-less asm as
 * implicitly volatile, but gcc 2.7.2 does NOT lower the two the same way: the
 * volatile spelling parks a real scheduling boundary at the read. Measured on
 * func_800AB37C (town, @2.7.2, the same row named in the ASM_TAILSLOT_PIN_TIED
 * note @116): with ASM_USE the function compiles to 204 bytes against a
 * 188-byte target (44 words off) and with ASM_USE2 to 200; the non-volatile
 * spellings are byte-exact. Prefer ASM_USE/ASM_USE2 first; reach for _NV only
 * when the volatile park is itself the residue. Port build compiles them
 * away. */
#define ASM_USE_NV(var)         __asm__("" : : "r"(var))
#define ASM_USE2_NV(a, b)       __asm__("" : : "r"(a), "r"(b))
/* ASM_USE_G_NV -- NON-VOLATILE input-only lifetime tail whose general "g"
 * constraint permits either a register or an immediate/symbolic operand.
 * This is distinct from ASM_USE_NV: forcing "r" can materialize an otherwise
 * rematerializable symbol and spend real instructions merely to keep its
 * source pseudo live. Provenance: func_800A2564 (dungeon, true symbol
 * func_800A7CC4, byte-exact @2.7.2-cdk-G0) needs D_8006CD30 live through the
 * second D-call region to preserve the retail global-register allocation,
 * while that call itself reloads the equivalent 0x80070000 page in $t0. The
 * "g" operand keeps the symbol as a zero-byte immediate RTL input; "r" adds
 * a two-word rematerialization in retail nop slots and misses by 2. Port build
 * (-DNON_MATCHING) retains the C reference and compiles the marker away. */
#define ASM_USE_G_NV(var)       __asm__("" : : "g"(var))
/* Output-only pin: materializes var as a register whose value the compiler
 * must treat as freshly produced here (the sanctioned form of the hand-rolled
 * `__asm__("" : "=r"(var))` read-zero/undef pins). */
#define ASM_UNDEF(var)          __asm__ __volatile__("" : "=r"(var))
#endif

#include "include_asm.h"
#include "game.h"
#include "globals.h"

typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;

/* ===========================================================================
 * gte_* -- SANCTIONED GTE (COP2) intrinsic family.
 *
 * WHY THIS IS NOT THE FORBIDDEN "instruction-emitting inline asm". The blanket
 * ban at @31 exists because `__asm__("lhu ...")` TRANSCRIBES the target: it
 * hand-writes the very instruction selection/allocation/scheduling that the
 * decompilation is supposed to derive from C. The GTE is the one place where
 * that reasoning inverts. gcc 2.7.2 has NO C lowering for coprocessor 2 -- no
 * intrinsic, no builtin, no pattern -- so the ORIGINAL psyq source could not
 * have contained C for these words either: retail's COP2 stream comes from
 * psyq's own `inline_c.h`/`gtemac.h`, whose gte_* macros ARE fixed inline-asm
 * templates. Reproducing those macros therefore reproduces the original source
 * construct; it is decompilation, not transcription. Cross-project precedent
 * for the exact spellings: ref/sotn-decomp/include/psxsdk/libgte.h (a
 * byte-matching PSX decomp that ships the same templates).
 *
 * THE RULE that keeps this from becoming a transcription loophole:
 *   1. A gte_* body is a FIXED psyq template -- COP2 transfer/command words
 *      only. No target-derived register allocation (%0 operands are gcc's
 *      choice), no scheduling, no non-COP2 instruction except the load-delay
 *      `nop`s and the `sra`/`sh`/`sw` that are part of a psyq macro's own
 *      published body.
 *   2. Nothing else in a candidate may be written in asm. If a residue outside
 *      the COP2 stream tempts you toward a second template, the answer is still
 *      no -- serve it as a C-shape problem.
 *   3. New ops are added ONLY when a blocked row needs them (this family was
 *      scoped by the exact op inventory of the four blocked rows below), and
 *      each addition must carry BOTH arms.
 *
 * PROVENANCE (the rows this family unblocks; op inventory taken from retail):
 *   func_80044D24  (main,    aligned 112 @2.7.2-cdk) 0x80044FE4-0x800450AC:
 *                  4x { ldv0 ; rtv0tr ; stsv }.
 *   func_800AED64  (town,    served 3x, aligned 389/592/378) 0x800AF1D4 and
 *                  0x800AF400: ldv3/rtpt/avsz3/stotz/stsxy3_g3/nclip/stopz,
 *                  ldv0/rtps/stsxy/stszotz, ldrgb/nccs/strgb.
 *   func_800AF9D8  (town,    served 2x, aligned 202/351) 0x800AFDA0-0x800AFED4:
 *                  the same plus stdp, ldir0 and ncds.
 *   func_800CA184  (dungeon, served 2x, aligned 804/1057) 0x800CA884+:
 *                  the same plus stflg (this row is the only FLAG consumer).
 * These 5 serve-rows are the "GTE/COP2 terminal class" of
 * tools/learnings/residue_taxonomy.md (0 landed; the blocker was policy, not
 * residue). The lint/oracle see gte_* BY NAME only -- no literal asm reaches a
 * candidate .c -- so tools/portability_lint.py and tools/match.py's
 * asm_instruction_fragments() stay clean exactly as for the ASM_* families.
 *
 * MATCHING ARM. Every template is __volatile__ SPELLED OUT: gcc 2.7.2 does NOT
 * treat an output-less asm as implicitly volatile (measured, ASM_USE_NV @214),
 * and every GTE op has side effects on the COP2 register file that gcc cannot
 * see. Stores also carry a "memory" clobber, loads/commands deliberately do NOT
 * (that is psyq's own shape; a memory clobber on the loads over-fences the
 * block and moves the surrounding schedule). Command words are written as the
 * `cop2 <imm25>` mnemonic -- verified to assemble to the exact retail word by
 * mipsel-linux-gnu-as -march=r3000 through BOTH tools/cc.sh (maspsx) and
 * tools/cc_psyq.sh (genuine CC1PSX); `.word 0x4Axxxxxx` is the equivalent
 * fallback if a future binutils drops the r3000 cop2 mnemonic. No "+r"
 * constraint anywhere (gcc 2.7.x rejects `+`, see @43).
 *
 * PORT ARM (-DNON_MATCHING) is a REAL GTE, not a no-op: these ops COMPUTE
 * values that the surrounding C then stores and branches on, so a stub would
 * silently corrupt the port. gte_port_* below implements the psx-spx GTE
 * semantics (1/4096 fixed point, saturation, FIFOs, the UNR division) over one
 * shared register file, `g_gte`; exactly one port TU defines the storage with
 *     #define GTE_PORT_STATE_OWNER
 *     #include "common.h"
 * and the ported libgte (SetRotMatrix/SetTransMatrix/SetGeomOffset/...) must
 * write g_gte's control registers -- the ops here only READ them.
 * MODELLED: MAC0-3 and IR0-3 saturation+flags, SZ/SXY/RGB FIFOs, OTZ, and the
 * FLAG register (bit 31 error summary over the documented lanes) because
 * func_800CA184 reads FLAG via gte_stflg. NOT modelled (documented, not
 * accidental): the 44-bit MAC accumulator's wrap-on-overflow (we flag and keep
 * the wide value), per-term overflow detection (we check the accumulated sum),
 * and the RTPS/RTPT lm=1 IR3-flag quirk (every row here uses lm=0 there).
 * =========================================================================== */
#ifdef NON_MATCHING

typedef struct {
    /* control registers -- written by the ported libgte, read-only here */
    s16 rt[9];                  /* cop2c0-4    rotation matrix, row major     */
    s32 tr[3];                  /* cop2c5-7    translation vector             */
    s16 llm[9];                 /* cop2c8-12   light matrix                   */
    s32 bk[3];                  /* cop2c13-15  background colour              */
    s16 lcm[9];                 /* cop2c16-20  light colour matrix            */
    s32 fc[3];                  /* cop2c21-23  far colour                     */
    s32 ofx, ofy;               /* cop2c24-25  screen offset, 1/65536         */
    u16 h;                      /* cop2c26     projection distance            */
    s16 dqa;                    /* cop2c27     depth-cue scale                */
    s32 dqb;                    /* cop2c28     depth-cue offset               */
    s16 zsf3, zsf4;             /* cop2c29-30  average-Z scale factors        */
    u32 flag;                   /* cop2c31     error flags                    */
    /* data registers */
    s16 v[3][3];                /* cop2d0-5    V0/V1/V2                       */
    u8 rgbc[4];                 /* cop2d6      R,G,B,CODE                     */
    u16 otz;                    /* cop2d7                                     */
    s16 ir[4];                  /* cop2d8-11   IR0..IR3                       */
    s16 sx[3], sy[3];           /* cop2d12-14  SXY0..SXY2 FIFO                */
    u16 sz[4];                  /* cop2d16-19  SZ0..SZ3 FIFO                  */
    u8 rgb[3][4];               /* cop2d20-22  RGB0..RGB2 FIFO                */
    s32 mac[4];                 /* cop2d24-27  MAC0..MAC3                     */
} GteState;

#ifdef GTE_PORT_STATE_OWNER
GteState g_gte;
#else
extern GteState g_gte;
#endif

/* FLAG lanes that feed the bit-31 error summary (psx-spx: bits 30..23, 18..13). */
#define GTE_FLAG_ERROR_MASK 0x7F87E000u

/* MAC1..3 <- 44-bit accumulator, flagged, then arithmetic-shifted by `sh`. */
static __inline__ s32 gte_port_setmac(int i, long long v, int sh)
{
    if (v > 0x7FFFFFFFFFFLL) {
        g_gte.flag |= 1u << (31 - i);           /* bits 30/29/28: MAC1/2/3 pos */
    } else if (v < -0x80000000000LL) {
        g_gte.flag |= 1u << (28 - i);           /* bits 27/26/25: MAC1/2/3 neg */
    }
    g_gte.mac[i] = (s32)(v >> sh);
    return g_gte.mac[i];
}

static __inline__ s32 gte_port_setmac0(long long v)
{
    if (v > 2147483647LL) {
        g_gte.flag |= 1u << 16;
    } else if (v < -2147483647LL - 1LL) {
        g_gte.flag |= 1u << 15;
    }
    g_gte.mac[0] = (s32)v;
    return g_gte.mac[0];
}

/* IR1..3 <- MAC, saturated to [lm ? 0 : -8000h, 7FFFh]; flags 24/23/22. */
static __inline__ void gte_port_setir(int i, s32 v, int lm)
{
    s32 lo = lm ? 0 : -32768;
    if (v > 32767) {
        g_gte.flag |= 1u << (25 - i);
        v = 32767;
    } else if (v < lo) {
        g_gte.flag |= 1u << (25 - i);
        v = lo;
    }
    g_gte.ir[i] = (s16)v;
}

static __inline__ void gte_port_begin(void)
{
    g_gte.flag = 0;                             /* hardware clears FLAG per op */
}

static __inline__ void gte_port_end(void)
{
    if (g_gte.flag & GTE_FLAG_ERROR_MASK) {
        g_gte.flag |= 0x80000000u;
    }
}

/* [MAC1..3] = ((cv << 12) + M * V) >> sh ; [IR1..3] = saturate(MAC, lm).
 * `cv` may be a null pointer for the no-translation forms. */
static __inline__ void gte_port_matvec(const s16 *m, const s16 *v,
                                       const s32 *cv, int sh, int lm)
{
    int i;
    for (i = 0; i < 3; i++) {
        long long acc = cv ? ((long long)cv[i] << 12) : 0LL;
        acc += (long long)(m[i * 3 + 0] * v[0]);
        acc += (long long)(m[i * 3 + 1] * v[1]);
        acc += (long long)(m[i * 3 + 2] * v[2]);
        gte_port_setmac(i + 1, acc, sh);
        gte_port_setir(i + 1, g_gte.mac[i + 1], lm);
    }
}

/* GTE unsigned Newton-Raphson divide: (H*20000h/SZ3 + 1)/2, clamped to 1FFFFh.
 * The UNR seed table is the documented closed form, evaluated on the fly so the
 * header carries no 257-byte blob. */
static __inline__ u32 gte_port_divide(u32 h, u32 sz3)
{
    u32 n, d, u;
    s32 seed, idx;
    if (sz3 == 0 || h >= sz3 * 2) {
        g_gte.flag |= 1u << 17;                 /* divide overflow */
        return 0x1FFFFu;
    }
    n = h;
    d = sz3;
    while (!(d & 0x8000u)) {                    /* normalise: bit15 of d set */
        d <<= 1;
        n <<= 1;
    }
    idx = (s32)((d - 0x7FC0u) >> 7);            /* 0..100h */
    seed = (0x40000 / (idx + 0x100) + 1) / 2 - 0x101;
    if (seed < 0) {
        seed = 0;
    } else if (seed > 0xFF) {
        seed = 0xFF;
    }
    u = (u32)seed + 0x101u;
    d = (u32)((s32)(0x2000080 - (s32)(d * u)) >> 8);
    d = (u32)((s32)(0x0000080 + (s32)(d * u)) >> 8);
    n = (u32)(((unsigned long long)n * d + 0x8000ULL) >> 16);
    return n > 0x1FFFFu ? 0x1FFFFu : n;
}

/* One RTPS pass over V[vi]: rotate+translate, push SZ and SXY, depth-cue IR0. */
static __inline__ void gte_port_rtps_one(int vi)
{
    s32 sz3, sx, sy;
    u32 q;
    gte_port_matvec(g_gte.rt, g_gte.v[vi], g_gte.tr, 12, 0);
    sz3 = g_gte.mac[3];
    g_gte.sz[0] = g_gte.sz[1];
    g_gte.sz[1] = g_gte.sz[2];
    g_gte.sz[2] = g_gte.sz[3];
    if (sz3 < 0) {
        g_gte.flag |= 1u << 18;
        sz3 = 0;
    } else if (sz3 > 0xFFFF) {
        g_gte.flag |= 1u << 18;
        sz3 = 0xFFFF;
    }
    g_gte.sz[3] = (u16)sz3;
    q = gte_port_divide(g_gte.h, (u32)sz3);
    sx = (s32)(gte_port_setmac0((long long)q * g_gte.ir[1] + g_gte.ofx) >> 16);
    sy = (s32)(gte_port_setmac0((long long)q * g_gte.ir[2] + g_gte.ofy) >> 16);
    if (sx < -1024) {
        g_gte.flag |= 1u << 14;
        sx = -1024;
    } else if (sx > 1023) {
        g_gte.flag |= 1u << 14;
        sx = 1023;
    }
    if (sy < -1024) {
        g_gte.flag |= 1u << 13;
        sy = -1024;
    } else if (sy > 1023) {
        g_gte.flag |= 1u << 13;
        sy = 1023;
    }
    g_gte.sx[0] = g_gte.sx[1];
    g_gte.sy[0] = g_gte.sy[1];
    g_gte.sx[1] = g_gte.sx[2];
    g_gte.sy[1] = g_gte.sy[2];
    g_gte.sx[2] = (s16)sx;
    g_gte.sy[2] = (s16)sy;
    {
        s32 ir0 = (s32)(gte_port_setmac0((long long)q * g_gte.dqa + g_gte.dqb) >> 12);
        if (ir0 < 0) {
            g_gte.flag |= 1u << 12;
            ir0 = 0;
        } else if (ir0 > 4096) {
            g_gte.flag |= 1u << 12;
            ir0 = 4096;
        }
        g_gte.ir[0] = (s16)ir0;
    }
}

/* RGB FIFO push from MAC1..3 >> 4 (flags 21/20/19) + IR writeback. */
static __inline__ void gte_port_push_rgb(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        g_gte.rgb[0][i] = g_gte.rgb[1][i];
        g_gte.rgb[1][i] = g_gte.rgb[2][i];
    }
    for (i = 0; i < 3; i++) {
        s32 c = g_gte.mac[i + 1] >> 4;
        if (c < 0) {
            g_gte.flag |= 1u << (21 - i);
            c = 0;
        } else if (c > 255) {
            g_gte.flag |= 1u << (21 - i);
            c = 255;
        }
        g_gte.rgb[2][i] = (u8)c;
        gte_port_setir(i + 1, g_gte.mac[i + 1], 1);
    }
    g_gte.rgb[2][3] = g_gte.rgbc[3];
}

/* NCCS (depth_cue=0) / NCDS (depth_cue=1), both sf=1 lm=1. */
static __inline__ void gte_port_ncs(int depth_cue)
{
    int i;
    gte_port_begin();
    gte_port_matvec(g_gte.llm, g_gte.v[0], (const s32 *)0, 12, 1);
    gte_port_matvec(g_gte.lcm, &g_gte.ir[1], g_gte.bk, 12, 1);
    for (i = 0; i < 3; i++) {
        gte_port_setmac(i + 1,
                        ((long long)g_gte.rgbc[i] * g_gte.ir[i + 1]) << 4, 0);
    }
    if (depth_cue) {
        /* IR = ((FC << 12) - MAC) >> 12, saturated with lm=0 (hardware forces
         * lm=0 for this step even when the command's lm=1); MAC += IR * IR0. */
        for (i = 0; i < 3; i++) {
            long long d = ((long long)g_gte.fc[i] << 12) - g_gte.mac[i + 1];
            gte_port_setir(i + 1, (s32)(d >> 12), 0);
        }
        for (i = 0; i < 3; i++) {
            gte_port_setmac(i + 1,
                            (long long)g_gte.ir[i + 1] * g_gte.ir[0]
                                + g_gte.mac[i + 1], 0);
        }
    }
    for (i = 0; i < 3; i++) {
        gte_port_setmac(i + 1, (long long)g_gte.mac[i + 1], 12);
    }
    gte_port_push_rgb();
    gte_port_end();
}

static __inline__ void gte_port_avsz3(void)
{
    s32 otz = (s32)(gte_port_setmac0((long long)g_gte.zsf3
                                     * ((s32)g_gte.sz[1] + (s32)g_gte.sz[2]
                                        + (s32)g_gte.sz[3])) >> 12);
    if (otz < 0) {
        g_gte.flag |= 1u << 18;
        otz = 0;
    } else if (otz > 0xFFFF) {
        g_gte.flag |= 1u << 18;
        otz = 0xFFFF;
    }
    g_gte.otz = (u16)otz;
}

static __inline__ void gte_port_ldv(int vi, const void *p)
{
    const s16 *s = (const s16 *)p;
    g_gte.v[vi][0] = s[0];
    g_gte.v[vi][1] = s[1];
    g_gte.v[vi][2] = s[2];
}

static __inline__ void gte_port_ldrgb(const void *p)
{
    const u8 *s = (const u8 *)p;
    g_gte.rgbc[0] = s[0];
    g_gte.rgbc[1] = s[1];
    g_gte.rgbc[2] = s[2];
    g_gte.rgbc[3] = s[3];
}

static __inline__ u32 gte_port_sxy(int i)
{
    return ((u32)(u16)g_gte.sy[i] << 16) | (u32)(u16)g_gte.sx[i];
}

static __inline__ u32 gte_port_rgb2(void)
{
    return (u32)g_gte.rgb[2][0] | ((u32)g_gte.rgb[2][1] << 8)
         | ((u32)g_gte.rgb[2][2] << 16) | ((u32)g_gte.rgb[2][3] << 24);
}

static __inline__ void gte_port_stsv(void *p)
{
    s16 *d = (s16 *)p;
    d[0] = g_gte.ir[1];
    d[1] = g_gte.ir[2];
    d[2] = g_gte.ir[3];
}

/* -- transfers ---------------------------------------------------------- */
#define gte_ldv0(r0)            gte_port_ldv(0, (const void *)(r0))
#define gte_ldv3(r0, r1, r2)    (gte_port_ldv(0, (const void *)(r0)), \
                                 gte_port_ldv(1, (const void *)(r1)), \
                                 gte_port_ldv(2, (const void *)(r2)))
#define gte_ldrgb(r0)           gte_port_ldrgb((const void *)(r0))
#define gte_ldir0(r0)           (g_gte.ir[0] = (s16)(r0))

/* -- commands ----------------------------------------------------------- */
#define gte_rtv0tr()            (gte_port_begin(), \
                                 gte_port_matvec(g_gte.rt, g_gte.v[0], g_gte.tr, 12, 0), \
                                 gte_port_end())
#define gte_rtps()              (gte_port_begin(), gte_port_rtps_one(0), gte_port_end())
#define gte_rtpt()              (gte_port_begin(), gte_port_rtps_one(0), \
                                 gte_port_rtps_one(1), gte_port_rtps_one(2), \
                                 gte_port_end())
/* _nn ("no nops") variants -- see the MIPS arm for when these are correct. The
 * nops are a hardware hazard cover with no portable meaning, so on this arm the
 * _nn forms are exact aliases of the plain ones. */
#define gte_rtps_nn()           gte_rtps()
#define gte_rtpt_nn()           gte_rtpt()
#define gte_ncds_nn()           gte_ncds()
#define gte_nclip()             (gte_port_begin(), \
                                 gte_port_setmac0( \
                                     (long long)g_gte.sx[0] * g_gte.sy[1] \
                                   + (long long)g_gte.sx[1] * g_gte.sy[2] \
                                   + (long long)g_gte.sx[2] * g_gte.sy[0] \
                                   - (long long)g_gte.sx[0] * g_gte.sy[2] \
                                   - (long long)g_gte.sx[1] * g_gte.sy[0] \
                                   - (long long)g_gte.sx[2] * g_gte.sy[1]), \
                                 gte_port_end())
#define gte_avsz3()             (gte_port_begin(), \
                                 gte_port_avsz3(), \
                                 gte_port_end())
#define gte_nccs()              gte_port_ncs(0)
#define gte_ncds()              gte_port_ncs(1)

/* -- stores ------------------------------------------------------------- */
#define gte_stsv(r0)            gte_port_stsv((void *)(r0))
#define gte_stsxy(r0)           (*(u32 *)(void *)(r0) = gte_port_sxy(2))
#define gte_stsxy3_g3(r0)       (*(u32 *)(void *)((char *)(void *)(r0) + 8) = gte_port_sxy(0), \
                                 *(u32 *)(void *)((char *)(void *)(r0) + 16) = gte_port_sxy(1), \
                                 *(u32 *)(void *)((char *)(void *)(r0) + 24) = gte_port_sxy(2))
#define gte_stsxy3(r0, r1, r2)  (*(u32 *)(void *)(r0) = gte_port_sxy(0), \
                                 *(u32 *)(void *)(r1) = gte_port_sxy(1), \
                                 *(u32 *)(void *)(r2) = gte_port_sxy(2))
#define gte_stotz(r0)           (*(u32 *)(void *)(r0) = (u32)g_gte.otz)
#define gte_stopz(r0)           (*(s32 *)(void *)(r0) = g_gte.mac[0])
#define gte_stszotz(r0)         (*(s32 *)(void *)(r0) = (s32)g_gte.sz[3] >> 2)
#define gte_stdp(r0)            (*(s32 *)(void *)(r0) = (s32)g_gte.ir[0])
#define gte_stflg(r0)           (*(u32 *)(void *)(r0) = g_gte.flag)
#define gte_strgb(r0)           (*(u32 *)(void *)(r0) = gte_port_rgb2())

#else /* !NON_MATCHING -- byte-matching arm: psyq's own COP2 templates */

/* -- transfers ---------------------------------------------------------- */
#define gte_ldv0(r0) \
    __asm__ __volatile__("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(r0))
#define gte_ldv3(r0, r1, r2) \
    __asm__ __volatile__("lwc2 $0, 0(%0);lwc2 $1, 4(%0);" \
                         "lwc2 $2, 0(%1);lwc2 $3, 4(%1);" \
                         "lwc2 $4, 0(%2);lwc2 $5, 4(%2)" \
                         : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldrgb(r0) \
    __asm__ __volatile__("lwc2 $6, 0(%0)" : : "r"(r0))
/* IR0 from a REGISTER value (not memory) -- retail 0x800AFEC4 `mtc2 $v1,$8`. */
#define gte_ldir0(r0) \
    __asm__ __volatile__("mtc2 %0, $8" : : "r"(r0))

/* -- commands ----------------------------------------------------------- */
/* The two leading nops are part of psyq's command macros: they cover the GTE's
 * load-use latency after the lwc2/mtc2 transfer that precedes the command. */
#define gte_rtv0tr()    __asm__ __volatile__("nop;nop;cop2 0x0480012")
#define gte_rtps()      __asm__ __volatile__("nop;nop;cop2 0x0180001")
#define gte_rtpt()      __asm__ __volatile__("nop;nop;cop2 0x0280030")
/* _nn ("no nops"): the SAME command with psyq's two leading hazard nops omitted.
 * Retail omits them wherever the load-use latency after the preceding lwc2/mtc2
 * is ALREADY covered -- by the scheduled instructions that separate the transfer
 * from the command, or by a preceding command's own latency. Those sites are
 * two words shorter than the plain macro can express, and no source-level or
 * scheduling change can delete literal nop text embedded in a fixed asm template.
 *
 * USE ONLY where the retail bytes show no leading nops. These are NOT a general
 * optimisation: dropping the cover where the hazard is real changes GTE results
 * on hardware. Within a single function some sites need the nops and others do
 * not (func_800AED64 carries both forms -- its second gte_rtpt() keeps them, and
 * blanket removal there measured aligned 8 with two words missing). */
#define gte_rtps_nn()   __asm__ __volatile__("cop2 0x0180001")
#define gte_rtpt_nn()   __asm__ __volatile__("cop2 0x0280030")
#define gte_ncds_nn()   __asm__ __volatile__("cop2 0x0E80413")
#define gte_nclip()     __asm__ __volatile__("nop;nop;cop2 0x1400006")
#define gte_avsz3()     __asm__ __volatile__("nop;nop;cop2 0x158002D")
#define gte_nccs()      __asm__ __volatile__("nop;nop;cop2 0x108041B")
#define gte_ncds()      __asm__ __volatile__("nop;nop;cop2 0x0E80413")

/* -- stores ------------------------------------------------------------- */
#define gte_stsv(r0) \
    __asm__ __volatile__("mfc2 $12, $9;mfc2 $13, $10;mfc2 $14, $11;" \
                         "sh $12, 0(%0);sh $13, 2(%0);sh $14, 4(%0)" \
                         : : "r"(r0) : "$12", "$13", "$14", "memory")
#define gte_stsxy(r0) \
    __asm__ __volatile__("swc2 $14, 0(%0)" : : "r"(r0) : "memory")
/* SXY0/1/2 into ONE base at the POLY_G3 vertex offsets 8/16/24 (retail
 * 0x800AF210, 0x800AFDE8, 0x800CA904) -- a 3-address gte_stsxy3 would emit
 * three separate address computations. */
#define gte_stsxy3_g3(r0) \
    __asm__ __volatile__("swc2 $12, 8(%0);swc2 $13, 16(%0);swc2 $14, 24(%0)" \
                         : : "r"(r0) : "memory")
/* SXY0/1/2 into three DISTINCT addresses (retail func_8004C36C) -- not the
 * one-base POLY_G3 form above; each vertex earns its own address register. */
#define gte_stsxy3(r0, r1, r2) \
    __asm__ __volatile__("swc2 $12, 0(%0);swc2 $13, 0(%1);swc2 $14, 0(%2)" \
                         : : "r"(r0), "r"(r1), "r"(r2) : "memory")
#define gte_stotz(r0) \
    __asm__ __volatile__("swc2 $7, 0(%0)" : : "r"(r0) : "memory")
#define gte_stopz(r0) \
    __asm__ __volatile__("swc2 $24, 0(%0)" : : "r"(r0) : "memory")
#define gte_stszotz(r0) \
    __asm__ __volatile__("mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0(%0)" \
                         : : "r"(r0) : "$12", "memory")
#define gte_stdp(r0) \
    __asm__ __volatile__("swc2 $8, 0(%0)" : : "r"(r0) : "memory")
#define gte_stflg(r0) \
    __asm__ __volatile__("cfc2 $12, $31;nop;sw $12, 0(%0)" \
                         : : "r"(r0) : "$12", "memory")
#define gte_strgb(r0) \
    __asm__ __volatile__("swc2 $22, 0(%0)" : : "r"(r0) : "memory")

#endif /* NON_MATCHING (gte_*) */

#endif /* COMMON_H */
