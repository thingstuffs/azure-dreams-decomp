# Independent review: CDK reload-CSE transition trace

## Verdict

The trace supports the narrow causal claim for this exact compile: UID 362
enters `reload_cse_simplify_set` with `SET_SRC = CONST_INT 0`; the routine's
candidate search reaches register 19 as the first candidate for which
`reload_cse_regno_equal_p` returns true; the routine then commits a register-19
replacement through `validate_change`; and UID 362 leaves with
`SET_SRC = REG 19`. The observed `move s1,s3` is therefore created by CDK's
post-allocation reload CSE in this run.

This rules out an earlier pass having already performed this particular
`CONST_INT 0` -> `REG 19` source rewrite. Earlier allocation and value-cache
history still determine why register 19 is available and accepted, so the
trace does not make reload CSE the sole upstream cause of the mismatch.

## Instrumentation audit

The compiler binary is an unstripped 32-bit i386 ELF. Its symbol table and
disassembly independently identify:

- `0x08180ab7` as the entry of `reload_cse_simplify_set`;
- `0x081807a1` as the entry of `reload_cse_regno_equal_p`.

Both breakpoints therefore run before their function prologues, so reading
32-bit cdecl arguments from `esp + 4`, `esp + 8`, and `esp + 12` is consistent
with this binary. The outer hook selects `u32(insn + 4) == 362`, decodes the
SET destination at `set + 4` and source at `set + 8`, and enables the equality
hook only for that invocation. The decoded entry objects are internally
coherent: destination code 52/mode 4/register 17 and source code 47/value zero.

The captured equality calls return false for registers 0 through 16 and 18,
then true for register 19. Register 17 is the destination and is skipped by the
routine before the comparator call. Disassembly confirms the relevant control
flow: on a true comparator result, the routine calls `gen_rtx` with code 52,
the current mode, and candidate register number, then passes `set + 8` to
`validate_change`. The finish breakpoint observes code 52/mode 4/register 19
at `set + 8`, confirming that validation committed the replacement before the
routine returned.

## State-write and perturbation check

`trace.py` contains no `write_memory`, register assignment, inferior function
call, or GDB command that changes compiler RTL/data state. Its explicit actions
are inferior memory/register reads, breakpoint enable/disable, Python record
updates, and writing `trace.json` after the inferior exits. GDB software and
finish breakpoints necessarily install temporary trap instructions in process
text; that debugger mechanism is not a compiler-data mutation.

The ordinary driver output and debugger-run output normalize to the same 221
assembly items. Their raw assembly differs only in the compiler-generated
comment that lists option order (`-G0 -O2 -w` versus `-O2 -G0 -w`); no emitted
instruction or data directive differs. This is strong evidence that the trace
did not perturb code generation. It cannot prove that every transient internal
state bit was identical if such a difference later canceled.

## Limits

- The result covers one source, one `-O2 -G0 -w` invocation, and cc1 SHA-256
  `90db2db7bcfe372244ca4d9785a7bfbf7613d711f69ee3bfe6c91d82a85e611d`.
  Function addresses, RTX layout, code numbers, ABI assumptions, and UID 362
  are not portable to another compiler binary or changed source.
- The equality hook records calls while the selected outer invocation is
  active but does not verify frame ancestry. A nested or concurrent call could
  be misattributed. This cc1 run is single-threaded, yielded one selected event,
  and the observed register sequence matches the enclosing routine's search,
  so there is no sign of that failure here.
- Registers rejected by quantity/class tests before
  `reload_cse_regno_equal_p` are absent from the comparison list. A false result
  records the comparator outcome, not the internal reason for rejection.
- The trace proves where the replacement happens. It does not yet show where
  register 19 acquired or retained the equivalent-zero cache entry, how joins
  invalidate that entry, or what source lifetime would avoid it while
  preserving retail allocation.
- `raw_eax_at_return_untyped = 31` is merely a stale machine-register
  observation at a routine with no interpreted return contract. The main
  report correctly assigns it no semantic meaning.
- `normalize` drops comments and several directives and canonicalizes local
  labels/addresses. In this case the raw diff check removes the usual concern:
  the only discarded difference is option-order commentary.

The reported 15-row, 18-window, and SLUS publication results are compatible
with this attribution but are outside the trace itself and were not rerun in
this read-only review.

## Bound evidence

- `trace.py`: `5238b660223dc2d5c0d5e95fb7a67e295fafeaf513b43fc92628b477c1aee26f`
- `run.py`: `a89b76f8590a44c1e0691de20afc72cef05978ff4ed5937eac30aa6d83a50b27`
- `result.json`: `124a71bf6dafd9ce9bedd631e1c122c7a4f276a04d91ea68209c0b3d7f155732`
- `REPORT.md`: `0a4b4194b456ff596e3192de5d8410a4a2c166494dab065449da001ab10345af`
- captured `trace.json`: `28b56b5a020ea3a4747f85c5668c916c26af79349a0887bc8b4805e24403c55c`
- copied and originating source: `a1b853645c2d1e305798cb704c69c143403e90194f86ad4a2df845eb5cd9fcfd`
- ordinary `normal.s`: `f515c33dc608cb21c031da9435db1d3a1f376b9b9accb2daedfb5b1597611b43`
- debugger-run `traced.s`: `778b4e1142a34653d52e4d2cd6dd6322c49e638a79c5451855e849a98c0af37f`
