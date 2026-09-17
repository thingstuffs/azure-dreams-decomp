# Round 51: bounded function workers expose stale compiler evidence

**6,028 pins remain in 1,271 functions; no pin removals this round.**
The retained change removes one incorrect entry from the dungeon `noreturn`
census. Both affected production rows, both covering windows, SLUS and the row
database pass. No C, recipe, compiler or assembler implementation changed.
The [durable receipt](evidence/pin_research_round51_20260917.json) preserves
the candidates, controls, scripts, audit and publication evidence.

## Gemini through agy

The installed `agy` CLI works. A bounded `gemini-3.8-flash-high` worker received
one complete function, its full retail listing, fixed recipe, baseline, and a
six-hypothesis ceiling. It produced two candidates before its five-minute print
timeout; exit status zero did not mean the task completed. It saved no final
report. Treat this as a partial run, not six exhausted hypotheses. Future briefs
should reserve time for a checkpoint report and save each result immediately.

For `819C0C18`, direct barrier removal missed 21 aligned edits. Gemini's ordinary
switch retained the barrier but missed only one instruction in 334 words. Root
reproduction at the proven runtime name found the same difference: retail calls
`func_8002626C` with `jal`, while the pipeline generated `j`.

The raw compiler output already contains the correct `jal`. Maspsx's existing
LEAD 18 pass changes it because the global census falsely lists this returning,
ten-argument helper as a zero-argument non-returning function. Removing just
that stale name makes the ordinary switch **334/334 linked words exact** with
identical raw compiler assembly. The current production helper and caller remain
exact under both censuses. Independent semantic and alias review supports the
[one-name correction](evidence/pin_research_noreturn_review_20260917.md).

The switch still has one barrier. Removing it remains nonexact at 332/334 words;
a positive-guard rewrite does not fix that. The exact switch candidate is saved,
not promoted: it does not reduce pins, and full table/source publication review
remains outstanding. No artificial assembler exception was added.

## A mechanical population worth measuring

Before the correction, the dungeon census contained 1,045 symbols. The existing
declaration parser finds 113 current zero-argument `noreturn` symbols in the
current dungeon C; 110 survive the existing false-member exclusions. **935 census
names have no current declaration.** Of those, 114 have textual references in
132 current source files. These counts include definitions and comments; they
are neither a caller census nor a pin-removal forecast. The one-name fix leaves
1,044 entries and 934 names from that stale inventory.

Do not blindly regenerate the census. Each surviving historical name may affect
an alias, an assembly path or an old pinned source. The next cheap phase is an
alias-aware call index, followed by same-source/current-versus-filtered metadata
controls for a small ranked batch. A full byte comparison separates harmless
stale entries from entries that change code; inspect those changes before any
pruning. A returning definition and returning caller are stronger evidence than
mere absence of a declaration. Candidate-owned local epilogue declarations must
remain available to the pipeline.

This is a shared source of misleading failures, not evidence of 6,000 distinct
patterns. Earlier copy and return transfers remain proven; this wave adds no
verified pin-removal cascade. Cheap workers should continue complete-function
tasks, while root work focuses on their shared residuals and toolchain evidence.

## Points traversal: a measured lifetime tradeoff

For `819A764C`, the real layout is five eight-byte vectors; the adjacent renderer
and updater support it. Two ordinary zero-pin representations were tested.
Indexed access gives 130/130 words, 11 substitutions and two indels; a typed
cursor gives 35 substitutions and eight indels. Neither is exact.

The indexed form gets the input into retail's `s2` naturally. Its address
pseudos occupy `s0` during local allocation, leaving the index in `s1`, but it
recomputes the loop address. Enabling strength reduction recovers the induction
cursor and loses the desired roles: input/index/cursor return to `s0/s1/s2`.
The original two-pin source also fails when that flag changes. These targeted
controls identify a lifetime/allocation question, not a reason to sweep flags.
The saved observations come from pass dumps; they are not a new debugger trace.

The round 50 prose also misnamed `D_80024B20` as a message. The resident helper
registers a node under a 32-bit identifier; the same-bank address corresponds
to the renderer. The exact substitution remains valid. Cross-file callback
typing is still open; no pointer narrowing or interface change was introduced.

## Luna transition: one-word zero reuse

Luna tested six bounded hypotheses for `8195F0BC`. Its best removes the `$zero`
binding and uses a real local return: 224/224 words, one substitution. Root
reproduced that result. The compiler reuses a counter known to be zero
(`move s1,s3`) where retail uses `move s1,zero`.

Two further root hypotheses moved the reset to the row entry and separated the
traversal counters. Each restored the zero opcode but changed the `s1/s2` roles
at 22 sites. The actual three-argument helper contract produces the same role
problem; blindly narrowing its prototype is not a solution. The six worker and
two root probes are bounded negatives. The next useful evidence is the earliest
zero-equivalence and register-web decision, before another source spelling.

## Next bounded phase

1. Build the alias-aware stale-census call index and rank at most eight live
   returning-helper cases. Preserve exact old/new endpoints and affected gates.
2. Give workers complete functions with helper contracts, fixed recipes and
   explicit output checkpoints. Limit hypotheses; preserve incomplete runs.
3. For the switch, inspect the first differing scheduling pass around case-zero
   state stores and the child-flags load before two new source hypotheses.
4. For the transition and points loops, require a predicted lifetime/pass change
   before further probes. No result here establishes impossibility.
