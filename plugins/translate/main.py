from xungram import BasePlugin, hooks

DICTIONARY = {
    "hello": "привет",
    "world": "мир",
    "good morning": "доброе утро",
}


class TranslatePlugin(BasePlugin):
    @hooks.on_incoming_message
    def translate(self, message):
        text = message.text or ""
        key = text.strip().lower()
        if key in DICTIONARY:
            hooks.replace_text(DICTIONARY[key])
