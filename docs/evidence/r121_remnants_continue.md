# r121 remnants continuation

Review pending. The original 51 DUNGEON rows / 6,776 bytes are preserved byte for
byte. This continuation adds 298 complete ordinary C rows / 10,440 bytes:
263 DUNGEON / 8,424 bytes, 27 TOWN / 1,316 bytes, 8 MAIN / 700 bytes.
The cumulative lane delivery is 349 C rows / 17,216 bytes. No new span overlaps
a previously registered C row. Every new row has separate actual m2c output,
a readable source and a matching canonical baseline. Baseline equality does
not manufacture a source-edit/fidelity improvement.

The largest forwarded dungeon spans required extent recovery: 0x19BB0DC has a
72-byte preceding tail and a complete 320-byte constructor at 0x19BB124;
0x19550E0 has a 72-byte preceding tail and a complete 168-byte callback at
0x1955128; 0x1967240 has a 72-byte preceding tail and a complete 140-byte callback
at 0x1967288. Those three complete functions are now exact C. The tails remain
unported and are never registered as new function entries.

MAIN's 224-byte constructor at 0x2713FC follows the actual branch structure:
an existing object enters initialization; a newly allocated non-null object
skips that block; allocation failure diagnoses and continues through the
initialization path if the error routine returns. The 128-byte destructor and
six further wrappers are exact C. Sony LIBCARD INIT/SCGNCK-shaped ordinary
wrappers are not called assembly merely because a catalogue member matches.
Six additional MAIN BIOS-vector trampolines are sdk_asm (96 bytes): each is
16/16 bytes equal to its existing fully catalogued TOWN twin. No new assembly
integration, GCC recipe, or C coverage is claimed for these trampolines.
The original MAIN END/PATCH/delay, TOWN BIOS and OVMOVIE VLC classifications
remain intact, including the data words/workspace and internal split aliases.

The TOWN 0x5FF770-0x5FF850 group remains held: its extended caller-bank
boundary is not independently proven, and its wrapper import ABI is unresolved.
The 0x68F718-0x68F7B8 group is four exact 40-byte counter helpers. The devkit 168-byte initializer at
0x26E624 and 180-byte indexed initializer at 0x26E6F4 are exact ordinary C;
individual default-word/field assignments reproduce the observed alias and
scheduling behavior. Typed, bounded single-word global views are used where
scalar declarations produced different load motion. There are no
unchanged write-backs, volatile fields, register pins, inline asm, or fake
arithmetic dependencies in the continuation sources.

Static per-floor bank proofs use 11-32 independent local-jump witness
functions in each selected image. Only newly compiled exact sub-extents are
promoted from solved to proven; other intervals retain their original status.
This is linked placement, not observed runtime selector execution. MAIN/TOWN
devkit placement similarly uses existing internal-j references, without a
retail-loading claim. C-byte equality alone never establishes a bank base.

An ABI audit corrected 231 wrapper sources and freshly rescored all 231 exact:
225 explicitly forward all four known engine arguments and its return value;
six explicitly forward one known local argument. The actual canonical engine
callee and local callees supply these contracts. All known fixed-resident
calls have consistent arity. The genuine SDK header declares SsGetNck(void).
28 provisional rows were withdrawn: 21 callback-group functions with unresolved
active-engine import contracts, one dungeon import wrapper, and the six TOWN
counter helpers above. Their byte scores do not prove C call semantics. Their
sources and reasons remain under holds/ and ABI evidence; they install no C.
The pre-ABI journals are archived, and current official new-row records contain
only these 298 admitted rows. The original journal prefix remains unchanged.

The unchanged kit scores all 298 complete bodies exactly at their cohort
recipes (cdk-G0, with seven MAIN and five devkit TOWN bodies at 2.6.3-G0).
The receipt binds every source, frozen first pass, recipe, retail span and
full compiler-derived rowbase binary. It also records every production window
covering these new rows: 231 were freshly regated after the ABI corrections;
27 retained their exact prior proofs after the production loader confirmed
unchanged sources, recipes, extents, bases and backend/header inputs.
Independent nm symbol sizes also equal every full retail function extent.
Final gate_verified annotations were then added;
the unchanged production loader rechecked all current source/recipe/extent/base
projections without a semantic change. Bytes outside compiler C projections may still come
from the production gate's existing retail-fill path; full-window equality is
not a claim that those other bytes have become C-owned.

All 682 forwarded spans have per-item statuses in the lane's
`evidence/continue_handoff_status.tsv` and `.json`: 294 resolved, 4 partial,
384 open. Handoff bytes partition into 10,620 matched C, 1,300 SDK assembly,
1,344 data and 10,412 unresolved bytes. These are physical handoff bytes;
complete newly recovered function extents can include return/delay words
beyond a heuristic span. `ledger/coverage_residue.jsonl` is appended only;
superseded unported events are explicitly deactivated when a complete new C
extent replaces them. The original 310 data classifications remain retained.

## Hold and continuation

`dungeon/func_800B7914` is not finished and is not counted as C. Best remains
aligned 5 (3 substitutions, 2 indels) with the bounded two-field MenuState.
Further bounded literal-object, union and bitfield views did not improve it.
An independent full-section link produces 180 bytes against 176 retail bytes;
the reported kit distance is capped and is not full-body equality.
The stock compiler RTL now identifies the concrete distinction: HIGH is held
correctly, but the nonzero active member is legalized through a low-base add;
the later pending read/store already use LO_SUM directly. Preserve the
candidate and inspect imported storage/declaration evidence or use the RTL
in a compiler-pass diagnostic. No page literal, flag fitting, assembler
change, byte patch, or compiler-impossibility verdict is admitted.

Original TU membership, storage ownership and prototype review remain module
review work. No new native certificate is claimed. The original certificate
renewal item dungeon_cd_control_d79c4 is retained. Rejected setup attempts
(duplicate rowbase refinement, decimal-window discovery/name-family mismatch,
and overly long new remainder-region ids) were corrected in metadata and
rerun through the unchanged tools. No rejection was bypassed.
