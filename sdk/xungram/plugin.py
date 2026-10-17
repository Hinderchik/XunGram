from types import SimpleNamespace

from . import hooks


class Message:
    def __init__(self, payload):
        self._payload = payload
        self.id = payload.get("id")
        self.text = payload.get("text", "")
        self.outgoing = bool(payload.get("outgoing"))
        self.chat = SimpleNamespace(id=payload.get("chat_id"))


class MessageContext:
    def __init__(self, message):
        self.message = message
        self.text = message.text
        self.cancelled = False
        self.read_cancelled = False

    def replace_text(self, text):
        self.text = text

    def cancel_read(self):
        self.read_cancelled = True

    def cancel(self):
        self.cancelled = True

    def result(self):
        return {
            "text": self.text,
            "cancelled": self.cancelled,
            "cancel_read": self.read_cancelled,
        }


class BasePlugin:
    def __init__(self):
        self._settings = {}
        self._handlers = {}
        self._collect_handlers()

    def _collect_handlers(self):
        for name in dir(type(self)):
            hook = getattr(getattr(type(self), name), "__xungram_hook__", None)
            if hook:
                self._handlers.setdefault(hook, []).append(getattr(self, name))

    def _dispatch_message(self, event, payload):
        context = MessageContext(Message(payload))
        hooks._set_current(context)
        try:
            for handler in self._handlers.get(event, []):
                handler(context.message)
        finally:
            hooks._set_current(None)
        return context.result()

    def handle_incoming_message(self, payload):
        return self._dispatch_message(hooks.INCOMING_MESSAGE, payload)

    def handle_outgoing_message(self, payload):
        return self._dispatch_message(hooks.OUTGOING_MESSAGE, payload)

    def on_load(self):
        pass

    def on_enable(self):
        pass

    def on_disable(self):
        pass

    def on_unload(self):
        pass

    def on_settings_changed(self):
        pass

    def get_setting(self, key, default=None):
        return self._settings.get(key, default)

    def set_setting(self, key, value, reload_settings=False):
        self._settings[key] = value
        if reload_settings:
            self.on_settings_changed()
