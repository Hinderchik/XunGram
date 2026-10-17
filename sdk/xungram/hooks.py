INCOMING_MESSAGE = "incoming_message"
OUTGOING_MESSAGE = "outgoing_message"
MESSAGE_SENT = "message_sent"
UPDATE = "update"
REQUEST = "request"

_current = None


def _hook(name):
    def decorator(func):
        setattr(func, "__xungram_hook__", name)
        return func
    return decorator


on_incoming_message = _hook(INCOMING_MESSAGE)
on_outgoing_message = _hook(OUTGOING_MESSAGE)
on_message_sent = _hook(MESSAGE_SENT)
on_update = _hook(UPDATE)
on_request = _hook(REQUEST)


def _set_current(context):
    global _current
    _current = context


def replace_text(text):
    if _current is not None:
        _current.replace_text(text)


def cancel_read():
    if _current is not None:
        _current.cancel_read()
