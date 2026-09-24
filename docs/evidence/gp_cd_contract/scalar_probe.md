# E34C/E4FC scalar declaration probe

This private probe changed only five `extern` declarations in copied sources.
E34C now declares `D_80080AD0` and `D_800814D0` as `u8`, `D_80080AD4`
as `u16`, and `D_80080ADC` as `void *`. E4FC now declares `D_80080AD4`
as `u16`. The function bodies and other type definitions are byte-identical
to their baseline sources at `193c2e1c`. E758 already uses the `u8`/`u16` scalar views;
F5AC declares AD4 as `u16`. E4FC stores pointers to ADC, while E34C only
stores zero there. These facts support declaration reconciliation; they do
not establish storage ownership.

`probe.py` compiles each original and edited source through
`verify._compile_slus_source` at its registered `2.7.2-cdk` recipe with
empty compiler and assembler flags. Its source and result artifacts are in
`candidate/`, `raw/`, and `receipt.json` under the private scalar probe directory.
The durable receipt is [scalar_probe_receipt.json](scalar_probe_receipt.json). Reproduce with:

```
<reference-repo>/.venv/bin/python work/native_lane/gp_cd_contract/scalars/probe.py
```

| Row | Fresh edited vs original object | Full emitted function vs pinned | Stock vs retail, no masks |
|---|---|---|---|
| E34C | byte-identical | 20/20 words exact | 20/20 exact |
| E4FC | byte-identical | 132/132 words exact | 132/132 exact |

The fresh objects have different whole-file hashes from the cached build
objects, but their parsed sections and symbols match those cached objects
exactly; all emitted function tokens also match. The candidate and original
fresh whole-object hashes are identical for each row. The private generic
assembler and genuine ASPSX 2.79 `-q` agree with each other on each candidate,
but both emit longer code than retail: 24 versus 20 words for E34C and 134
versus 132 for E4FC. The unchanged baseline has the same generic/genuine
lengths, so this is not a regression from the declaration changes. No
position-based closeness score is inferred for those unequal extents.

The production source, ledger, manifest, active object and retail image hashes
are unchanged. The ASPSX temporary path is the separate
`work/native_lane/cdscalar_aspsx/` directory. No production file or body was
edited, and no link or ownership claim follows from this direct compile.
