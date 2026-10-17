from xungram import BasePlugin, hooks


class HelloPlugin(BasePlugin):
    @hooks.on_incoming_message
    def greet(self, message):
        if message.text and "hi" in message.text.lower():
            hooks.replace_text(message.text + " 👋")
