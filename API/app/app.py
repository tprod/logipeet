#!/usr/bin/env python
from config import app
from controllers.user_controller import api

app.register_blueprint(api)

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=True)
