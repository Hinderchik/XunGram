import importlib.util

from .plugin import BasePlugin


def load_plugin(entry_path, name="xungram_user_plugin"):
    spec = importlib.util.spec_from_file_location(name, entry_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    for value in vars(module).values():
        if (
            isinstance(value, type)
            and issubclass(value, BasePlugin)
            and value is not BasePlugin
        ):
            return value
    raise RuntimeError(f"no BasePlugin subclass found in {entry_path}")
