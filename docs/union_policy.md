# Union inventory and proof policy

The November 4 owner ruling makes unions default-deny.  A distinct member
access proves a union only when the accesses refer to the **same object** and
the creator, allocation path, or installed callback establishes that identity.
The proof belongs in the source as `/* UNION: <sites> - <evidence> */` and in
`ledger/unions.jsonl`.  A width or signedness spelling that happens to preserve
bytes is not proof.  Such fields should usually have one declared type with a
value cast, a pointer cast at a minority site, or separate action body structs.

`python3 tools/typing/union_census.py --root . --out ledger/unions.jsonl`
records every physical `union {}` definition in `src/` and `include/`,
including typedefs, anonymous members, and nested aggregates.  IDs use a file,
owner and member path; source line is informational.  Each row has member names
and types, spelled access counts split between `src` and `include`, a kind,
status, and evidence.  The counts are lexical leads only.  In particular,
identically named fields in different types can contribute to a count, and
pointer arithmetic, macro expansion, and aliases can hide access.  Never turn
a count into a same-object claim by itself.  Regenerating the census preserves
review statuses, cast evidence and retired rows already in the ledger.
`count_basis` distinguishes field-path counts from standalone typedef or named
union member-suffix counts.  The latter are global upper bounds because the
union's instance names vary; a zero count is still a useful retirement lead.
The lexical index includes the root of `local_union.member` accesses as well
as `object->field.member` chains.

Kinds: `sign_pun` is equal-width integer signedness; `width_view` is differing
integer widths; `ptr_int` mixes pointers and integers; `ptr_ptr` mixes pointee
types; `packed` overlays bytes/halves/whole or array data; `per_action` is an
action scratch layout; `zero_init_idiom` is the round 118 compiler lever; and
`other` covers remaining shapes.  Kinds describe shapes and are not proof.
The round 118 zero-init source rows were merged into larger files in this
root.  The current inventory identifies their surviving sites by the merged
file and local name, and preserves their accepted compiler-lever status.  Do
not retire that class as part of overlay cleanup.

`python3 tools/typing/union_verify.py` marks a row `retire` when at least one
member has no spelled access.  All other overlay rows remain `unproven` until
manual source and creator/callback review.  A `retire` row is a candidate for
an edit, not a claim that its bytes will remain unchanged.  The review writes a TSV report to `--report` (default `build/union_verify.tsv`).  Retired definitions
remain in the ledger with status `retire`, evidence, and any actual cast sites
in `retired_to_cast`.  A failed byte proof gets `proven-by-bytes` and a diff
location instead.  Regenerating the verification report preserves reviewed
same-object proofs, retired rows, and failed byte proofs.

`python3 tools/lint/debt_check.py --unions --root .` fails for any current
definition without a ledger row or for a count above
`tools/lint/union_baseline.json`.  It is not part of `make check`; run it before
landing (the batch checks do).  The baseline (`count` and `ids` in
`tools/lint/union_baseline.json`) records the current definitions and is
rewritten downward as definitions are retired.  Adding a union requires a proven ledger row with `UNION:` evidence
while still keeping the total at or below the baseline.  The check also catches
stale member lists and a retired union reintroduced at its old ID.  This checker detects physical source
definitions; it does not parse union-producing macros.
