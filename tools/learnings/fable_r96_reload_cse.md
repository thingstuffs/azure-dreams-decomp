# Field re-reads -> retail register copies (r96_fable_6014, dungeon/func_81876014 7 -> 0 at cdk-G0)

**APPEARS:** retail `move rX,rY` beside a store/load of rY's field, while our text copies a LOCAL into several fields
(ASM_REG on the copies, KEEPs, often a `-fno-schedule-insns` crutch cell).
**RESOLVES:** write the copies as FIELD RE-READS (`o->b = o->a; o->c = o->a + k;`), the initialising store separated from
the first re-read by another store, in retail's column order.
**Why (cdk source):** cse.c note_mem_written / invalidate_memory (7035, 7585-7647, 1713) drop every struct MEM equivalence
on any field store, so the re-reads stay loads through cse; the cdk-only post-reload CSE reload1.c:2140 reload_cse_regs
(def 7869; simplify_set 8142, noop_set_p 8049, record_set 8240 - absent from FSF 2.7.2/2.6.3, present in 2.8.0+) turns
loads of a value a register already holds into `move`s. convert.c:269 narrows `+ 0x10` under an s16 store.
**Check:** tools/lanes/lanekit/reload_cse_trace.py <dumps>/<stem> - per load uid, .lreg -> .greg: still a load / copy / deleted.
**Did not work there:** vertex-major order, re-read immediately after its store (cse folds it), re-read from another
re-read, the pinned statement order, shared locals.
**Populations to try:** dossier copy-head rows (800AA854, 8028906C, ...), CELL rows with a -fno-schedule-insns crutch,
dead loads retail keeps (80B467DC) - r96_opus_rcse is measuring them.
