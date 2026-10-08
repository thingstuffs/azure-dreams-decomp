## Call dependences, loop-depth refs and cse quantity heads (r103_fable_p2, 2026-10-08)

Read work/native_lane/r103_fable_p2/MECHANISM.md and APPROACH.md. Fable read the cdk source (toolchain/gcc-src/
2.7.2-cdk) at each residue's deciding rule instead of sweeping shapes; four rules every lane should know:
1. **The only pure-C source of a call -> step dependence is a register-passed PARAMETER.** sched1 gives no dependence
   between a call and a later set of a call-crossing pseudo, so a local walker's `p += K` hoists above the call. A
   parameter pseudo carries `REG_EQUIV (mem (plus argp N))` (function.c 3985-4014); sched.c (1738-1766, 1900-1925)
   analyses that address for every SET/USE, and the fixed hard register in it is "call-used", so the insn gets an
   anti-dependence on last_function_call. APPEARS: `p = param;` walker whose step hoists above a call. RESOLVES:
   walk the parameter itself (800AA854: the hoist r96/r98/r103 Opus could not fix is gone pin-free).
2. **flow weights refs by loop depth**: a real loop (do/while/for) multiplies the body's refs; a goto loop is depth 1.
   A real inner loop is the natural lever when alloc_need says an allocno needs more refs. loop.c combines address
   givs into one register whose base is the LAST access in insn order, and emits its init at loop_start (LUID-last
   in its block: rank_for_schedule ties by LUID). `volatile` MEMs are not givs - drop scaffolding volatiles first.
3. **sched.c keeps flow's calls-crossed for a pseudo live in more than one block** (5120-5133) even after sched1
   moves the copy past the call: a variable loaded before a call and copied after it stays callee-saved.
4. **cse make_regs_eqv: the longer-lived pseudo becomes the quantity head** (a hard register is never replaced), and
   canon_reg rewrites later uses to the head - so a copy `x = y` dies when y outlives x. Many callee-saved "dance"
   and argument pins buy exactly this (they make the copy's source a hard register). Ask "which pseudo is the head?"
   before trying shapes; no pure-C spelling makes the shorter-lived pseudo the head.
Instruments: `diff.py --scorer --norm-regs` (raw listing distance is dominated by renames on allocation rows - it swung
250 -> 8 for one structural change); alloc_need.py; prio.py --all; why.py --deps-table / --pass sched.
Negative (do not re-run): the `$0` addend pin on 800971DC - combine's PARALLEL-into-copy special case merges any copy;
a cast is refused but leaves `andi` (no regmove pass in cdk); reload_cse cannot record a divmod PARALLEL output.
