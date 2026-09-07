"""Transform plugins. Each plugin: name, level, eligible(text,row,census)->refusal|None, apply(text,row,census)->text."""
import importlib
def load(name):
    return importlib.import_module(f"xform.{name}").T
