# Access agreement from retail instructions

`tools/typing/access_census.py` joins source accesses from the existing Clang
field census to MIPS loads and stores. It compiles each requested physical TU
through its pinned recipe with `-g` and admits a function only when the debug
object's executable section is byte-identical to the gate-checked cached object.
For compound SLUS recipes, the probe uses the compiler step before the rodata
trim and still requires exact executable bytes.
If an `src/slus/` wrapper cannot be parsed because its generated partition
include is absent at that path, the probe parses the exact `build_slus/src/`
compiled source. `physical_tu` names the wrapper used for compilation and
merge replacement; `file:line` retains the generated source origin.
The source access must have a parameter base held in a saved register from one
`move sN,aN` or an unmodified incoming argument register, plus a unique debug
line, register offset, width and read/write direction. Compound read/write
expressions become two rows. Ambiguous accesses and values optimized away remain `unmapped` or
`ambiguous` in `access_sites.tsv`; they are never assigned an opcode by order.
The second pass admits a cross-line scheduler move only when the entire
function has exactly one source access and one retail instruction for the
proven register, offset, width and direction. A local pointer can use that
parameter proof only when the source facts show one known assignment from a
parameter or another such local, no later write, and no address escape. Its
constant rebase is included in the instruction offset comparison.
For a named local kept in a register, the census recompiles the pinned GCC
stage to retain its raw `.def` register location. It requires one source
local with that name, one compiler register record inside the function, and
an instruction on the same debug line using that register and offset. Local
register joins have no cross-line fallback.
The debug and cached section names may differ under `-g`; a changed name is
accepted only when the executable bytes are unique on both sides and equal.
Accesses from inlined functions with no separate executable section remain in
the table as `unmapped`. For a physical TU with multiple pinned recipes, the
census measures every placement separately; `recipe_output` identifies the
placement in each site row and is part of the merge key.
Multi-function TUs use a unique `config/names.tsv` source-to-build symbol
alias to select their exact executable section.

Example:

```sh
python3 tools/typing/access_census.py --out out \
  --source src/dungeon/effect/advance_effect_fade_and_remove.c
python3 tools/lint/debt_check.py --summary --access-summary out/access_summary.json
```

For a batch, use:

```sh
python3 tools/typing/access_census.py --out out/batch_001 --source-file out/remaining/batch_001.txt
python3 tools/typing/access_census.py --out out --from-sites out/access_sites.tsv \
  --merge-sites out/batch_001/access_sites.tsv
```

A later measurement replaces all rows for the physical source files listed in
its `source_files.txt`, including files that yielded no access rows.

`agreement_pct` is the share of **mapped accesses** that are plain member
accesses through a named record with matching width and load sign. Stores
compare width only. Word loads have no opcode sign; direct consumer opcodes
provide a separate sign vote when present. The separate `mapped/source_sites` ratio
must accompany every percentage. `access_folders.tsv` contains the same
measure for each measured folder, and `access_disagreements.tsv` lists declared
signs that differ from the majority mapped load sign for the field.
`access_summary.json` and the report-only debt lines also show exact-join
coverage by base kind.
Anonymous nested structs inherit their named object's base kind; accesses
through signedness or width union members remain union puns.

`shared_field_signs.tsv` counts `lb`, `lbu`, `lh`, `lhu` and `lw` for proven
ActorRecord, TownObjectRecord and ObjectNodeHeader bases. Its recommendations
are marked `sample_only` while access joins remain incomplete; unknown
word-load signs and stores do not vote. Views at matching offsets need
creator or installer evidence before they can be joined to a shared record.
The table now admits only actual top-level fields with the declared offset and
width. `NODE_HEADER(body)->field` accesses use the header offset after adding
the 32-byte header size; a body cast by itself cannot identify a header field.
`mapped_loads` and `at_least_five` mark the review threshold. Direct
`slt`/`sltu`, `sra`/`srl`, and `div`/`divu` uses within eight instructions,
before a branch or overwrite, are recorded separately in `consumer_*` columns.
They are a second vote, not replacements for load opcode signs.
`suggested_type` and `minority_value_cast` are review prompts; a source change
still needs the byte-exact gate.

`debt_check.py --summary` caches lexical report rows in
`out/debt_report_cache`. Each source entry is keyed by its content, the tool
implementation and the content of all `src/` and `include/` headers, so a
landing with unchanged inputs reuses the prior analysis. `--no-report-cache`
forces a complete recomputation. The access lines read the already generated
`access_summary.json` and never trigger a census compile.

`view_match.py --access-sites` also writes `shared_view_shadow_candidates.tsv`.
It lists mapped view loads at the same offset and width as a field of one of the
three shared records, when that record ranks among the view's shape candidates.
Every row says `record_identity=unproven`: the load vote belongs to the view,
and cannot be added to the record's sign majority without creator, installer,
callback and allocation evidence identifying the actual object.

`tools/typing/view_match.py` emits shape candidates from the codemap's record
layouts and cast sites. Passing `--kinds-json` from
`tools/typing/object_kinds.py report` adds creator and callback evidence for
views present in that report. Passing `--access-sites` replaces declared signs
at observed view offsets with measured load signs. Evidence attaches the view to an object kind;
it does not prove that the ranked record is that kind's type. A candidate
cannot authorize a retype under R3.
