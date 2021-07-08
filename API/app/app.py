#!/usr/bin/env python
import time
from config import app
from flask import Flask, jsonify
from controllers.user_controller import bp_user
from controllers.storage_controller import bp_storage
from controllers.events_controller import bp_events
from controllers.sensors_controller import bp_sensors
from controllers.cannil_controller import bp_cannil
from controllers.animals_controller import bp_animals
from controllers.login_controller import bp_login
from controllers.signup_controller import bp_signup
from multiprocessing import Process, Value


app.register_blueprint(bp_user)
app.register_blueprint(bp_storage)
app.register_blueprint(bp_events)
app.register_blueprint(bp_sensors)
app.register_blueprint(bp_cannil)
app.register_blueprint(bp_animals)
app.register_blueprint(bp_login)
app.register_blueprint(bp_signup)

@app.route('/testes', methods=['GET'])
def get_tasks():
   return jsonify({'tasks': 'funca'})



def record_loop(loop_on):
   while True:
      if loop_on.value == True:
         print("loop running")
      time.sleep(1)

if __name__ == '__main__':

    recording_on = Value('b', True)                     
    p = Process(target=record_loop, args=(recording_on,))   #cenas para o arduino com multitasking
    p.start()  
    app.run()
    p.join()

