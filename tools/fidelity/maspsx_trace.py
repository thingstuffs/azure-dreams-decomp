#!/usr/bin/env python3
"""Run the project's maspsx (tools/maspsx, unmodified) with its post-passes TRACED and,
optionally, some of them DISABLED - the ablation instrument of tools/fidelity/aspsx_diff.py.

    .venv/bin/python tools/fidelity/maspsx_trace.py --trace OUT.json [--disable P1,P2]
        [--strip-externs] -- <exactly the maspsx.py argv the pipeline uses>   < in.s

Nothing in tools/maspsx is edited: the real `maspsx.py main()` runs, after the MaspsxProcessor
post-pass methods have been wrapped in this process only.

  * every post-pass named in `MaspsxProcessor.process_lines` (`res = self._pass(res)`, parsed from
    the live source, so a new pass is picked up automatically) is wrapped; a pass FIRED when its
    output list differs from its input list;
  * two inline `process_line` helpers that imitate an ASPSX scheduling decision
    (`_maybe_unfill_return_delay`, `_expand_store_to_symbol_in_delay`) and the post-pass helper
    `_backfill_return_delay_store` are wrapped the same way (fired = returned a rewrite);
  * `--disable` makes the listed passes/helpers the identity (the ablation);
  * `--strip-externs` drops every `.extern NAME,SIZE` line from maspsx's input as a metadata
    ablation. A changed object can result from scheduling as well as addressing; inspect the
    emitted relocation types before assigning a `$gp` cause.

The trace JSON: {"passes": [every wrapped pass], "fired": [passes that changed the listing],
"disabled": [...], "strip_externs": bool}. The ablation changes maspsx's input, not its
implementation.
"""
import importlib.util
import inspect
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
MASPSX_DIR = os.path.join(ROOT, "tools", "maspsx")


# process_line helpers that imitate an ASPSX/retail scheduling decision and return replacement lines
# (None = not applicable).  The load-delay nop / mflo hazard handlers are NOT here: genuine ASPSX
# performs those too, they are what makes maspsx an ASPSX model at all.
INLINE_HOOKS = ["_maybe_unfill_return_delay", "_expand_store_to_symbol_in_delay"]
REGION_HOOKS = ["_backfill_return_delay_store"]


def post_passes(cls):
    src = inspect.getsource(cls.process_lines)
    names = re.findall(r"res\s*=\s*self\.(_\w+)\(res\)", src)
    seen, out = set(), []
    for n in names:
        if n not in seen and hasattr(cls, n):
            seen.add(n); out.append(n)
    return out


def main():
    argv = sys.argv[1:]
    if "--" not in argv:
        sys.exit("usage: maspsx_trace.py --trace OUT [--disable a,b] [--strip-externs] -- <maspsx args>")
    k = argv.index("--")
    mine, rest = argv[:k], argv[k + 1:]
    trace_path, disable, strip_externs = None, set(), False
    i = 0
    while i < len(mine):
        if mine[i] == "--trace":
            trace_path = mine[i + 1]; i += 2
        elif mine[i] == "--disable":
            disable |= {x for x in mine[i + 1].split(",") if x}; i += 2
        elif mine[i] == "--strip-externs":
            strip_externs = True; i += 1
        else:
            sys.exit(f"maspsx_trace: unknown option {mine[i]}")

    sys.path.insert(0, MASPSX_DIR)
    import maspsx as pkg                                        # the package tools/maspsx/maspsx/
    cls = pkg.MaspsxProcessor
    passes = post_passes(cls)
    passes_all = passes + [n for n in INLINE_HOOKS + REGION_HOOKS if hasattr(cls, n)]
    unknown = disable - set(passes_all)
    if unknown:
        sys.exit(f"maspsx_trace: not a post-pass: {sorted(unknown)}")
    fired = []

    def wrap(name, orig):
        def w(self, res):
            if name in disable:
                return res
            before = list(res)
            out = orig(self, res)
            if out != before:
                fired.append(name)
            return out
        return w
    for n in passes:
        setattr(cls, n, wrap(n, getattr(cls, n)))

    # inline behaviours called from process_line: "fired" = returned replacement lines
    def wrap_inline(name, orig):
        def w(self, *a, **k):
            if name in disable:
                return None
            out = orig(self, *a, **k)
            if out is not None:
                fired.append(name)
            return out
        return w
    for n in INLINE_HOOKS:
        if hasattr(cls, n):
            setattr(cls, n, wrap_inline(n, getattr(cls, n)))
    # a helper of a post-pass (the LEAD 19/23 return-delay backfill): fired = changed its region
    def wrap_region(name, orig):
        def w(self, region, *a, **k):
            if name in disable:
                return region
            before = list(region)
            out = orig(self, region, *a, **k)
            if out != before:
                fired.append(name)
            return out
        return w
    for n in REGION_HOOKS:
        if hasattr(cls, n):
            setattr(cls, n, wrap_region(n, getattr(cls, n)))

    if strip_externs:
        data = sys.stdin.read()
        data = "\n".join(l for l in data.split("\n") if not re.match(r"\s*\.extern\s", l))
        import io
        sys.stdin = io.StringIO(data)

    spec = importlib.util.spec_from_file_location("maspsx_cli", os.path.join(MASPSX_DIR, "maspsx.py"))
    cli = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(cli)
    sys.argv = ["maspsx.py"] + rest
    code = 0
    try:
        cli.main()
    except SystemExit as e:
        code = e.code if isinstance(e.code, int) else (0 if e.code is None else 1)
    if trace_path:
        with open(trace_path, "w") as fh:
            json.dump({"passes": passes_all, "fired": sorted(set(fired), key=passes_all.index),
                       "disabled": sorted(disable), "strip_externs": strip_externs}, fh)
    sys.exit(code)


if __name__ == "__main__":
    main()
