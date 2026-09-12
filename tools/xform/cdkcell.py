"""Run another transform at the CDK cell: the cell lever for every generator.

2026-09-12: pins that emulate FSF 2.7.2 / 2.6.3 / 2.8.1 code often turn out dead at 2.7.2-cdk, the
build whose address splitting and scheduling retail shows (t29_addrsym, the admissible-cell scan).
A row whose pinned text is exact at a CDK cell (tools/pin_cells_land.py rule 2) is handed to the
inner transform as if it were recorded there, so the inner plugin's own search - screen, verify,
greedy erasure - runs at that cell. A result also exact at the recorded cell lands as usual; one
exact only at the CDK cell lands with the switch (rule 1), through sweep.py's set_row_cfg path.

Bind an inner plugin with a two-line module `t31_cdk_<inner>.py`: `T = wrap("<inner>")`.
"""
import importlib, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from common import parse_cfg

CDK = ("2.7.2-cdk", "2.7.2-cdk-G0")


def wrap(inner_name):
    inner = importlib.import_module(f"xform.{inner_name}").T

    class T:
        name = f"t31_cdk_{inner_name}"
        level = getattr(inner, "level", 1)
        needs_verify = True

        @staticmethod
        def eligible(text, row, census):
            if row["cfg"] in CDK:
                return "already at a CDK cell"
            return inner.eligible(text, row, census)

        @staticmethod
        def apply_verified(text, row, census, vf):
            g0 = "-G0" in row["cfg"]
            for cell in sorted(CDK, key=lambda c: ("-G0" in c) != g0):
                if not vf(text, cell).get("exact"):
                    continue                                   # rule 2: the shipped bytes must not depend on it
                cell_row = dict(row, cfg=cell, cell=parse_cfg(cell)[0], flags=" ".join(parse_cfg(cell)[1]))
                vf_cell = lambda cand, cfg=None, _c=cell: vf(cand, cfg or _c)
                if getattr(inner, "needs_verify", False):
                    new, info = inner.apply_verified(text, cell_row, census, vf_cell)
                else:
                    new, info = inner.apply(text, cell_row, census), {}
                    if new is not None and new != text and not vf_cell(new).get("exact"):
                        new = None
                info = dict(info or {}, cdk_cell=cell)
                if new is None or new == text:
                    return None, info
                if info.get("cfg") and info["cfg"] != cell:
                    return None, {"refused": [f"inner transform moved the cell to {info['cfg']}"]}
                info.pop("cfg", None)
                if not vf(new).get("exact"):
                    info["cfg"] = cell                         # rule 1: exact at the CDK cell and not at the recorded one
                return new, info
            return None, {"refused": ["pinned text not exact at a CDK cell"]}

    return T
