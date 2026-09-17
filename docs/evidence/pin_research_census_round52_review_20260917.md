# Round 52 independent dungeon-census cohort review

## Verdict

The returning-contract and bank-identity evidence supports testing removal of
each of the eight listed census entries individually. Seven have direct caller
evidence that execution or a consumed result follows the call. The eighth,
`func_80025B78`, has weaker caller evidence because the caller returns
immediately, but its proven same-bank definition explicitly returns an object
or `NULL`; it is still an ordinary returning function.

This is eight per-symbol conclusions, not approval to prune the other 926 stale
entries or even the other 21 stale names with indexed calls. Publication should
depend on the isolated same-source, one-entry-filtered controls and normal
gates being run by the root lane. This review ran no compiler or gate and made
no shared metadata/source change.

## Per-symbol findings

| Census name | Returning-contract evidence | Source-contract debt | Bank identity | Verdict |
|---|---|---|---|---|
| `func_800240EC` | The definition falls through after `func_80067014(0)`. Its caller performs color and direction state writes immediately after the call. | Definition is `void(void)` while the caller passes three arguments; those surplus argument registers do not make the callee noreturn. | Definition `func_818B08EC` -> true `func_800240EC`; caller `func_818B1664` -> true `func_80024E64`; both proven at delta `0x7E753800`. The caller rowbase proof independently names the `jal 0x800240EC` endpoint. | **Supports removal.** |
| `func_8002443C` | The definition returns the allocated object or zero. The caller assigns the returned word into `effect_create[11]` and continues its loop. | Definition spells the return `s32`; caller spells it `Effect *`. Both are one-word transport and both require return. | Definition `func_818B0C3C` -> true `func_8002443C`; same `func_818B1664` caller and proven `0x7E753800` bank. Its rowbase proof also names the `jal 0x8002443C` endpoint. | **Supports removal.** |
| `func_800243B8` | The definition returns an object or `NULL`. The caller stores the result in each child slot, decrements the index, and repeats. | Definition has three parameters; the old-style caller passes a fourth value. That prototype debt does not alter the observed return contract. | Definition `func_818AABB8` -> true `func_800243B8`; caller `func_818AAE60` -> true `func_80024660`; both proven at delta `0x7E759800`, in exactly abutting rowbase regions. | **Supports removal.** |
| `func_801744DC` | The definition falls through normally. The caller invokes it in a 16-iteration loop, then executes a second loop and further state changes. | Definition has two parameters; the old-style caller passes three. | Definition `func_81032CDC` -> true `func_801744DC`; caller `func_810332A4` -> true `func_80174AA4`; both lie in proven `sweep_104F83C` at delta `0x7F121800`. | **Supports removal.** |
| `func_800249E4` | The definition returns after its optional allocation block. The caller makes three consecutive calls, then updates timer and state fields. | Caller uses an old-style declaration, but the seven supplied arguments agree with the definition's seven argument groups. | Definition `func_8194D1E4` -> true `func_800249E4`; caller `func_8194D354` -> true `func_80024B54`; both lie in proven `img_196c8f0_800240f0` at delta `0x7E6B7800`. | **Supports removal.** |
| `func_80174BC8` | The definition returns the allocated object or zero. Its caller increments state and continues processing after the call. | Definition returns `s32`; caller declares `void` and ignores the word. That is still a returning contract. | Definition `func_810873C8` -> true `func_80174BC8`; caller `func_810860B4` -> true `func_801738B4`; both lie in proven `sweep_10A3000` at delta `0x7F0CD800`. | **Supports removal.** |
| `func_80172050` | The definition returns `-1`, zero, or one. The caller casts and branches on the returned value, which is decisive call-return evidence. | Caller uses an old-style declaration; return width and use agree. | Definition `func_81084850` -> true `func_80172050`; caller `func_81083694` -> true `func_80170E94`; both lie in proven `sweep_10A3000` at delta `0x7F0CD800`. | **Supports removal.** |
| `func_80025B78` | The definition returns the allocated object or `NULL` on every path. | The old-style caller ignores the returned pointer and immediately returns, so the call site alone cannot distinguish an ordinary tail-position call from noreturn. The callee definition supplies the positive returning evidence. | Definition `func_819AE378` -> true `func_80025B78`; caller `func_819AD81C` -> true `func_8002501C`; both are proven at delta `0x7E657800`. | **Supports removal, with definition-led rather than caller-led evidence.** |

Each definition is argument-taking or otherwise lacks a current zero-argument
noreturn declaration. None fits the global zero-argument noreturn census
contract.

## Alias and index audit

The row ledger's synthetic filenames cannot be treated as runtime identity.
For all eight names, the current row's `true_name` equals the proposed census
name, and its caller resolves under the same proven rowbase delta. This rules
out the immediate cross-bank collision risk for these specific calls. The
`func_800240EC` and `func_8002443C` caller proof is especially strong: it
records both call endpoints as in-image function starts at the unique solved
delta. The `func_800243B8` definition and caller records abut exactly and share
their delta; the remaining pairs share a single proven sweep/image record or
the same proven bank delta.

`config/names.tsv` has no row whose canonical or alias column is any of these
eight names. A bounded exact-name scan over current `src/dungeon` C, headers,
and assembly found no additional direct occurrence beyond the indexed
definitions, declarations, and calls (plus comments/type names). It also found
no direct use of the eight synthetic definition filenames as callable symbols.

The index remains lexical. It recognizes direct `func_XXXXXXXX(...)` tokens
after stripping comments and strings, canonicalizes only `names.tsv`, and
does not prove function-pointer targets, macro token-pasting, binary/assembly
references outside `src/dungeon`, or semantic aliases absent from that table.
The bounded checks above reduce those risks for the eight selected current C
callers; they do not prove that no hidden reference exists anywhere in the
container. That limitation is another reason not to extrapolate this cohort to
the full stale set.

## Bound evidence

- `index.json`: `2cd54a84b4b494f83f2fb2d53cee8309c62595b7fdd8a3fac92b1113eea05be2`
- `index.py`: `b73be6b6deaa74338dfdef6d07b09d86709208ea8c420fc51da4a49ba278d11d`
- `config/noreturn_syms.dungeon.txt`: `36cffe62a29172e8852a73b155392b3cf729f59a63efb660254f152b891cf527`
- `config/overlays/dungeon.rowbase.jsonl`: `d54e8b55cacf46a4ffec3cfb637334bfe47c2d486a1fe61f9cf7254973590dc8`
- `config/names.tsv`: `3576763c6538e26aa9953194283f427be22893cbafba88ab734b748d30de0a22`

| Symbol | Definition source SHA-256 | Caller source SHA-256 |
|---|---|---|
| `func_800240EC` | `ea16f6eb4339848d036531779ee808315d6fa49bc86bb1d978da5c3f0b318dee` | `9be2b3ea87698ab5859dc14707985f18b54ef2cc8724973748f9b7a53e0979e9` |
| `func_8002443C` | `715e5e8e2ab6d0135c0d783f90b524e5c686713dd3bc99c612652fed9c7ca699` | `9be2b3ea87698ab5859dc14707985f18b54ef2cc8724973748f9b7a53e0979e9` |
| `func_800243B8` | `76b412ebd3246649e439857ed8ab2b2ec5befde15fcc0d2e585a5364933173d4` | `b077be2bd691a3ea3667b5c2de6ab7aa4f5c984fa7fd2815ba489579160b5c17` |
| `func_801744DC` | `ed04a64718fe75a2b4d301e31a03e0d4af368185ce4bdd52215853ea6c414fe3` | `f4f46d2cf6353b0136001a27f063a968410a6b1fee25021b207db252cc8df73d` |
| `func_800249E4` | `585c22b6e6049c9596f9de5b90c2f1942032140bbae0e52d4d196b74703f84b0` | `35d9e3543fae236c4ce5acb69b0281d6854fab260a66db2bacd3ee065af75357` |
| `func_80174BC8` | `7f238452ffff013ce3db462e682ce2e9736d29d377a11113cf415e6fef61f4e2` | `247ed21979adfe297fab87f7d8c7c35f7af8cc9cd17ca52553b82dd4c5027020` |
| `func_80172050` | `a9d22f2d516a59700f687a48560634f483c19744338ea557d0f2107a21a4dc3f` | `a0054622ae016ba3907b93c086ff4a0ac3926b422eb527bd376842364e6237e4` |
| `func_80025B78` | `7c2509593db0fd789417e0b6d060f6904655354060bb649609066594fa0c93ec` | `5cff38ea3ce354c21fe94af0fee20286f2efd75febe0b182aa793bf8acea44b5` |


## Publication addendum

Root controls found all eight isolated removals byte-neutral in the seven live
callers and in seven all-pin-erased diagnostic sources. The combined canonical
edit removes only the reviewed eight lines. Fifteen fresh row checks, all
eighteen covering windows, SLUS and the row database pass. Both build views
link the canonical file; no export was needed. No source or recipe changed.
The index script now caches each file's pin count and accepts a frozen census
path; its frozen-baseline output is byte-identical to the reviewed index.
