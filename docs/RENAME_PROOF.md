# D0 rename proof

`tools/rename_proof.py` and `tools/lanes/lanekit/rename_proof.py` are the same
command. Run from a lane under the private checkout's `work/native_lane/`.

```sh
python3 "$REPO/tools/rename_proof.py" town/func_8008D588 after.c --stage
python3 "$REPO/tools/rename_proof.py" --check-only before.c after.c
python3 "$REPO/tools/rename_proof.py" town/func_8008D588 after.c --renames map.json
python3 "$REPO/tools/rename_proof.py" town/func_8008D588 after.c \
  --receipt tmp/rename_proof_ID/proof.json
```

The default before file is the lane's `base/<container>/<filename>.c`, falling
back to the current tree for a scratch lane. `--before FILE` overrides it. Its
bytes must still equal the current landed source. A stale lane must rebase and
re-prove. An optional `map.json` is a JSON object such as
`{"entry_count":"count","unk_04":"flags"}`; all entries must be used exactly.
Without it the checker infers and reports the same map.

The command performs these checks in order:

1. Tokenize C after line splicing, treating comments as whitespace. Only
   identifier spelling may differ. Replacements must be consistent, injective,
   and use fresh names in each changed file. Literal spellings (including asm
   strings), numbers, keywords, punctuation, token counts, and preprocessor
   directives stay fixed. Macro function-like adjacency and header-name tokens
   are checked. Whitespace and explanatory comments may change.
2. Compile both texts at the row's registered recipe. Ordinary overlays use
   the production segment compiler with its bank-qualified assembler evidence.
   Native overlay members compile their full physical TU through the existing
   adapter; the proof inspects the **untrimmed** object. SLUS rows compile every
   declared physical stream through `verify.compile_slus_units`.
3. Compare actual allocated section bytes and their order, names, types,
   flags, addresses, sizes, alignments and entry sizes. NOBITS/BSS sizes count.
   Compare ELF ABI/flags, all non-FILE symbols (including undefined, static,
   COMMON and exported definitions), and each relocation targeting allocated
   storage. Symbol indexes become complete symbol identities. Relocation
   offsets, types, ordering and explicit RELA addends must agree; REL addends
   remain in the unchanged raw bytes. No instruction or relocation bits are
   masked. A changed call target refuses even when instruction bytes match.
4. Run the existing per-row byte verifier on **both** sides. Object neutrality
   alone does not establish retail equality. Missing cache entries, unsupported
   contexts, build errors and a non-exact baseline all refuse `exact=true`.
5. Recheck source, header, recipe and physical-context hashes. Only then may
   `--stage` publish `out/<container>/<filename>.c`, `.base_sha` and
   `.rename_proof.json`. A different staged candidate is preserved.

The registered preprocessor also emits its actual `-M` dependency closure for
every physical unit. Those consumed files are hashed and rechecked, including
includes through macros and nested headers. Dependencies outside the private
checkout refuse. Retained receipt checks cover these files as well.

Each compiler run and its `proof.json` remain under a fresh lane-local
`tmp/rename_proof_*` directory. The terminal prints a short result with the
artifact path; the full receipt records hashes, input state, section summaries,
both verifier results and object paths. `lab_log.jsonl` records the measurement,
and `lab.py report` includes it at the registered recipe. No ledger, source,
name table or recipe is modified. Exit 0 means exact proof (or, with
`--check-only`, token check only); exit 1 means refusal.

`--receipt` checks a retained exact proof's source/recipe/context hashes,
token evidence, actual saved objects and exact verifier verdicts without
compiling. Artifacts must still be available inside the lane. This is a
freshness check for trusted lane evidence, not authentication of an untrusted
JSON document. Missing or changed evidence requires a fresh proof.

## Field/header lanes

File-local struct member renames need no extra options. For an ordinary row
using a shared header, prepare the before and after header files in the lane
and pass `--headers headers.json`:

```json
{
  "shared/state.h": {
    "before": "base/include/shared/state.h",
    "after": "headers/shared/state.h"
  }
}
```

Keys are relative to `include/`, must end in `.h`, and cannot escape that tree.
The before header must equal the landed file. Every changed header receives the
same token check, and separate copies of the include tree supply before/after
compilation and verification. Headers omitted from the map stay identical.
This mode is proof-only: package the header and all affected source rows with
their before/after guards, and prove **every dependent row**, including rows
whose own source text did not change. One row's receipt does not establish
population coverage. Header overlays in physical native/SLUS module contexts
are deliberately refused by those adapters; complete TU/partition header
batches require their existing module workflow. No isolated-header waiver is
inferred from a single member's unchanged text.

Header verification uses a private exported scorer view with `include/`
pointing directly at the selected snapshot. This avoids older CDK preprocessors
selecting an earlier live `-I` despite a later `-isystem`/`-iquote` override.
The standing view and landed header files are unchanged.

## Acceptance and limits

A D lane needs this proof plus the included per-row verification; it does not
run a full window gate for each rename. The lander runs the affected windows
once at batch time, the SLUS SHA-1 gate where required, status/levels checks,
and certificate renewal for changed certified inputs. Receipts do not waive
those batch obligations. Existing SLUS per-row verifiers may themselves use a
whole-image/module check; this command preserves their authority.

The tool proves neutrality at the recorded recipe and preprocessing conditions.
It is not a C binding resolver, a source-semantics theorem, or proof of a name's
meaning. Review evidence-backed spelling choices separately. A reused member
name which must change differently in two structs, a name swap, or a partially
renamed local scope is conservatively refused; split the task or use the normal
content proof workflow. Fresh targets, consistent names and unchanged token
shape make a useful strict subset for automated D lanes.

The lexer refuses non-ASCII source, universal-character identifiers,
trigraphs, malformed literals/comments, and multiline comments within directives.
Unsupported ELF formats, section groups, TLS/link-order allocations, duplicate
section names and unknown non-debug sections refuse. FILE symbols and
non-allocated debug/comment metadata are excluded; runtime strings, allocated
notes and all loadable storage remain compared. Source-position macros such as
`__LINE__` can make a comment change non-neutral; object equality catches it.

Function/global renames still use `config/names.tsv`, `tools/apply_names.py`
and `ledger/names.jsonl`. This local/member tool does not replace that alias
and naming-evidence workflow.

Tests: `python3 -m unittest discover -s tools/tests -p test_rename_proof.py`.
