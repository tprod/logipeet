#!/usr/bin/env python
from config import app
from controllers.user_controller import bp_user
from controllers.storage_controller import bp_storage
from controllers.events_controller import bp_events
from controllers.sensors_controller import bp_sensors
from controllers.cannil_controller import bp_cannil
from controllers.animals_controller import bp_animals

app.register_blueprint(bp_user)
app.register_blueprint(bp_storage)
app.register_blueprint(bp_events)
app.register_blueprint(bp_sensors)
app.register_blueprint(bp_cannil)
app.register_blueprint(bp_animals)

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=True)

