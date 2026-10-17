import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

from xungram import BasePlugin, hooks, load_manifest, load_plugin, ManifestError


def test_dispatch_replaces_text_and_cancels_read():
    class P(BasePlugin):
        @hooks.on_incoming_message
        def handle(self, message):
            if message.text == "hi":
                hooks.replace_text("hello")
                hooks.cancel_read()

    result = P().handle_incoming_message({"id": 1, "chat_id": 5, "text": "hi"})
    assert result["text"] == "hello"
    assert result["cancel_read"] is True


def test_dispatch_leaves_untouched_when_no_match():
    class P(BasePlugin):
        @hooks.on_incoming_message
        def handle(self, message):
            return None

    result = P().handle_incoming_message({"id": 1, "chat_id": 5, "text": "hi"})
    assert result["text"] == "hi"
    assert result["cancel_read"] is False


def test_outgoing_cancel():
    class P(BasePlugin):
        @hooks.on_outgoing_message
        def handle(self, message):
            hooks._current.cancel()

    result = P().handle_outgoing_message({"id": 2, "chat_id": 1, "text": "x"})
    assert result["cancelled"] is True


def test_settings_roundtrip():
    plugin = BasePlugin()
    assert plugin.get_setting("missing", "default") == "default"
    plugin.set_setting("key", 42)
    assert plugin.get_setting("key") == 42


def test_example_plugins_validate_and_load():
    for name in ("hello", "translate"):
        directory = os.path.join(REPO, "plugins", name)
        manifest = load_manifest(directory)
        assert manifest.api_version == 1
        plugin_class = load_plugin(manifest.entry_path)
        assert issubclass(plugin_class, BasePlugin)


def test_hello_plugin_behaviour():
    directory = os.path.join(REPO, "plugins", "hello")
    manifest = load_manifest(directory)
    plugin = load_plugin(manifest.entry_path)()
    result = plugin.handle_incoming_message({"id": 1, "chat_id": 1, "text": "Hi there"})
    assert result["text"].endswith("👋")


def test_translate_plugin_behaviour():
    directory = os.path.join(REPO, "plugins", "translate")
    manifest = load_manifest(directory)
    plugin = load_plugin(manifest.entry_path)()
    result = plugin.handle_incoming_message({"id": 1, "chat_id": 1, "text": "Hello"})
    assert result["text"] == "привет"


def test_manifest_rejects_missing_field():
    import tempfile

    with tempfile.TemporaryDirectory() as d:
        with open(os.path.join(d, "manifest.json"), "w", encoding="utf-8") as f:
            f.write('{"id": "x"}')
        with open(os.path.join(d, "main.py"), "w", encoding="utf-8") as f:
            f.write("")
        try:
            load_manifest(d)
        except ManifestError:
            return
        raise AssertionError("expected ManifestError")
