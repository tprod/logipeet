#!/usr/bin/env python
from config import app
from controllers.user_controller import bp_user
from controllers.storage_controller import bp_storage
from controllers.events_controller import bp_events


app.register_blueprint(bp_user)
app.register_blueprint(bp_storage)
app.register_blueprint(bp_events)

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=True)

