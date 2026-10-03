import sys, json, inspect; sys.path.insert(0, "tools")
import status
from common import rows
out=[]
code = inspect.getsource(status._recipe_tracker).replace("        if n:\n            worst.append", "        ALL.append((r['id'], r['cfg'], best or '?', k))\n        if n:\n            worst.append")
ns = dict(status.__dict__); ns["ALL"] = out
exec(code, ns); ns["_recipe_tracker"](rows(), {})
json.dump(out, open(sys.argv[1], "w"), indent=0)
print(len(out))
