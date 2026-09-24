# D_80081554/58 five-function direct matrix

The bounded matrix is recorded in `direct_candidate.json` and
`direct_candidate_byte.json`; each cell keeps `a.s`, `a.proc.s`,
`genuine_input.s`, `a.o`, `generic.o`, and `genuine_0.lnk` under its
`direct_<candidate>_<cell>/` directory. The first harness attempt failed
because its private include root lacked `common.h`; that was an include-view
setup error, not a recipe result. The final receipts use a private symlink
view of the canonical headers plus the candidate header and contain three
completed compile/assembler trials each. No production files were written.

Retail extents are from address intervals, not ledger row sizes: DCA8..DCE0
14 words, DD2C..DDB4 34, DDB4..DDC4 4 (including `jr ra` delay nop),
DDE4..DE88 41, and E130..E188 22: **115 words total**. Every stock and
private-generic function is the full retail length. Every genuine LNK exposes
all five names before `add_unit`, and every retail comparison has zero masked
words. `genuine_modes` returned only `-q`, with `equ=false`, in each cell; its
`-q -0` mode was not generated because these assemblies have no divide.
Stock and private generic match token-for-token for all five functions in all
three cells.

The table applies identically to the original candidate and to
`candidate_byte`. Each entry is emitted/retail words and exactness; `G` is
private generic, `A` is genuine ASPSX 2.79. Stock equals `G`.

| Function | CDK default G / A | CDK `-fno-schedule-insns` G / A | 2.8.1 default G / A |
|---|---|---|---|
| DCA8 | 14/14 exact / exact | 14/14 miss / miss | 14/14 exact / exact |
| DD2C | 34/34 exact / exact | 34/34 miss / miss | 34/34 exact / 33/34 miss |
| DDB4 | 4/4 exact / exact | 4/4 exact / exact | 4/4 exact / exact |
| DDE4 | 41/41 miss / miss | 41/41 exact / exact | 41/41 miss / 40/41 miss |
| E130 | 22/22 exact / exact | 22/22 exact / exact | 22/22 miss / miss |

There is no five-function exact recipe among these three cells. The equal-length
misses below are literal address/word mismatches, not an aligned score. For
the unequal-length 2.8.1 genuine outputs, only structural aligned regions
are reported; no positional mismatch count is used as closeness.

| Cell and function | Exact residual sites |
|---|---|
| CDK default DDE4 | Seven same-length word differences at `0x8004DE44`, `DE48`, `DE4C`, `DE54`, `DE58`, `DE5C`, `DE60`. At `DE44`, candidate `00501021` precedes retail `00042080`; the following store/index operations are ordered differently through `DE60`. Generic and genuine are identical. |
| CDK no-sched DCA8 | Six sites at `0x8004DCB0`, `DCC0`, `DCC4`, `DCC8`, `DCCC`, `DCD0`. The D83D98 base is in `$3` (`3c038008`, `24633d98`) instead of retail `$2` (`3c028008`, `24423d98`), with dependent shift/add/store order and register changes. |
| CDK no-sched DD2C | Six sites at `0x8004DD74`, `DD80`, `DD84`, `DD88`, `DD8C`, `DD90`. Candidate loads `0x23` into `$3` (`24030023`) versus retail `$2` (`24020023`), then moves index/shift/add/store operations in the command sequence. |
| 2.8.1 generic DDE4 | Seven interior sites at `0x8004DE44`, `DE48`, `DE4C`, `DE54`, `DE58`, `DE5C`, `DE60`; the word at `DE58` is `00a32821` versus retail `24030001`. Genuine retains this interior residue and emits 40 words, one short. |
| 2.8.1 generic E130 | `0x8004E15C`: `00621821` versus retail `24630001`. Genuine retains this site and also moves the stack pop into the `jr ra` delay slot. |

The 2.8.1 genuine DD2C epilogue has 33 words: at indices 31–32 it emits
`jr ra; addiu sp,sp,24` (`03e00008; 27bd0018`), versus retail indices 31–33
`addiu sp,sp,24; jr ra; nop` (`27bd0018; 03e00008; 00000000`). DDE4 has the
same one-word-short epilogue pattern at indices 38–39 versus retail 38–40.
E130 remains 22 words but at indices 19–21 genuine emits
`nop; jr ra; addiu sp,sp,24`, while retail emits
`addiu sp,sp,24; jr ra; nop`. These are exact mode-specific observations;
they do not turn unequal lengths into a near-match ranking.

`candidate_byte` differs from the baseline only in DCA8's evidence-based
fallback declaration and its comment: `extern int D_80080B68[3]` becomes
`extern u8 D_80080B68[1]`. At default CDK the compiler assembly changes
`.extern D_80080B68,12` to size 1 and `lui/addiu` to `la`, but the assembled
private-generic object is byte-identical between variants. The same object
identity holds in the other two cells, and the five genuine function streams
have the same lengths and retail outcomes. The one-byte **used view** is
consistent with the primary's separate decoder audit; neither declaration
asserts a historical allocation size.

## Accepted natural C candidate and RTL capture

The primary's `candidate_v4` removes DCA8's old register pin and spells
DDE4's observed operations directly with the advancing counter. A fresh
default-CDK proof in `final_direct.py` and `final_direct_receipt.json` checks
all five **raw** genuine LNK functions before any scope augmentation. Stock,
private generic, and genuine ASPSX `-q` are token-identical and retail-exact
over the full 14/34/4/41/22 word extents, with zero masks and no stock
negative. The source hashes, assembler hashes, exact modes, and per-function
lengths are in the receipt; `final_direct_v4/` retains the input assembly,
processed assembly, objects, and genuine LNK. A full private link and
ownership gate remain separate checks for the primary.

For the earlier `candidate_byte` diagnosis, `-da` was accepted by the genuine
`gcc-2.7.2-cdk` driver in two isolated compiles. The exact command arrays and
exit codes are in `rtl_default/compile.log` and `rtl_nosched/compile.log`;
their `standalone.c.rtl`, `.sched`, `.sched2`, `.dbr`, and other pass dumps
remain beside `a.s`. Only the second command adds
`-fno-schedule-insns`. These dumps preserve the pre/post scheduling evidence
for the DDE4 residual. No further UID or priority attribution was needed
after the natural source shape removed that residual and passed the complete
direct proof.
