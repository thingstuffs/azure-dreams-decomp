# Pin-campaign tools

Run these from a lane beneath the checkout's `work/native_lane/`. Compiler cwd,
TMPDIR and retained evidence belong to that lane. See [README](README.md).

| Question | Command |
|---|---|
| Does the genuine SN compiler emit the same assembly? | `sncheck.py ROW erased` (or `pinned`, or a C file); optional `--cfg`, `--keep DIR`, `--json FILE` |
| Would one allocator input produce retail colours? | `alloc_oracle.py ROW FILE --pseudo NAME --qty-refs 5` |
| Does making a local global fix allocation? | `alloc_oracle.py ROW erased --pseudo NAME --force-global` |
| Would one depth-2 mention fix a walker? | `alloc_oracle.py ROW erased --pseudo 369 --refs-add 2 --retail-set 369=s4` |
| Would shorter local life change the decision? | `alloc_oracle.py ROW FILE --pseudo 94 --qty-life 2` |
| Would a different qty order help? | `alloc_oracle.py ROW FILE --pseudo NAME --qty-rank 20` (zero-based priority rank) |
| Which statement defined the call argument? | `why.py ROW --value-luid a0 --call FUNCTION --variant erased --json evidence.json` |
| Track any named pseudo's definitions | `why.py ROW --value-luid NAME --variant FILE` |
| Trace a call's block by UID | `why.py ROW --pass sched --block 121 --trace` (`u121` explicit UID, `b11` block) |
| Stage a byte-exact fidelity tidy at unchanged pins | `lab.py stage-tidy ROW tidy.c --note "typed field reads"` |

`sncheck` uses the same cpp recipe as the kit: the row's compiler driver, `-E -O2`,
registered flags, project include, `-w`. Both cc1s consume that exact `.i` in a
private directory. Normalisation removes comments, CRLF and formatting whitespace,
and compares `.ent` through `.end` bodies. It retains registers, labels and semantic
assembler directives. It deliberately ignores differently placed extern/text blocks
outside function bodies. `IDENTICAL` means compiler identity on this input; retail
identity still needs the byte scorer. Unknown generations are refused.

The binaries in `toolchain/genuine/psyq/` contain these verified version strings:

| Cell | Genuine binary | Version string |
|---|---|---|
| 2.7.2-cdk | psyq4.1/CC1PSX.EXE | cygnus-2.7.2-970404 SN32.3.7.0004 |
| 2.8.0 / 2.8.1 | psyq4.4/CC1PSX.EXE | 2.8.1 SN32 BUILD 4.0.0010 |
| 2.95.2 | psyq4.6/CC1PSX.EXE | 2.95.2 19991024 BUILD 4.0.0030 |

`2.8.0` is a generation cross-check with the 2.8.1 SN binary, not a claim that it
is an exact version twin. The tool verifies the string and records the binary SHA.
The SN runner uses the short filenames and private cwd of the genuine wrapper in
`tools/fidelity/epilogue_model.py`; the driver is unnecessary because cpp already ran.

The allocator oracle supports the verified symbol-only i386 CDK/2.8.x cc1 ABI.
`--refs`, `--refs-add`, `--live`, `--force-global` and `--force-local BLOCK` alter ONE
pseudo slot after `update_equiv_regs`, before local allocation. Local eligibility
still requires one death; forcing local cannot alter death count. `--qty-refs` changes
ONE quantity slot before sorting. `--qty-life` changes its death to birth+length,
which changes both priority and allocation geometry. `--qty-rank` moves the target
qty to one zero-based position in the priority order after qsort, retaining the order
of every other qty; it refuses blocks on the <=3-quantity inline-sort path.
The suggestion pass has already happened, so an existing suggestion winner stays one.

Each run byte-calibrates the pinned reference, compares a GDB baseline with the
plain compiler, retains the exact applied input, and reports baseline/forced colours
before reload plus distances to the calibrated pinned listing. Named targets and reference
colours use observed `DECL_RTL` from cc1, including register-held aggregates and
explicit hard-register bindings; shadowed names require a numeric target. `--retail-set` provides an explicit target for a
compiler-created pseudo. Unmapped colours remain unknown. Numeric pseudos are
compile-specific: inspect current dumps before reusing one. No intervention is a
stageable candidate, and no C spelling or routing verdict follows automatically.
Unsupported ABI, missing target, failed compiler and unapplied input fail closed.

The value-LUID view selects each side's call independently by symbol/occurrence
(or an explicit side-specific UID), finds the nearest non-self SET in its straight
line block, and follows that UID's patterns through the same compile's pass dumps.
A named pseudo without `--call` lists all its surviving definitions. If it was
eliminated, the view shows its initial RTL definitions and removal history. A control-flow
boundary gives an unresolved result rather than an invented reaching definition.
For CDK/2.8.x, GDB records actual `DECL_RTL` bindings at declaration expansion
and reads actual `INSN_LUID` numbers immediately after `sched_analyze`.
Source statements come from an instruction-identical `-g` twin and are assigned
only when both UID and RTL pattern match; unmatched source or LUID is shown as unknown.
Pass names describe observed transitions: CSE substitution, combine merge/rewrite,
loop.c rewrite/movement, scheduler movement. A ready-list LAUNCH priority records
an observed birthing boost. Dumps cannot prove which internal optimizer subroutine
caused a transition. UIDs are never equated between pinned and candidate compiles.

`stage-tidy` uses the registered cfg and the real byte scorer, including jump tables.
It requires the same live pin count, keeps the pin multiset a subset of the base,
and applies every normal admission guard. An identical text is refused. An exact,
admissible changed text goes to `out/<container>/<file>.c` plus `.base_sha`; its
measurement is journalled with `kind=stage-tidy`. It creates no recipe-trade entry
in `cells.jsonl`. It refuses `--cfg`, `--no-jtbl`, `--no-stage`, `--equal-pins` and
`--no-rule2`. The orchestrator can consume the normal `out/` through the ordinary
lane landing route and recheck its fidelity improvement; no lander runs in this tool.
