#!/usr/bin/env python
from models.sensors import Sensors
from config import db
from werkzeug.exceptions import NotFound

def get():

    return Sensors.query.all()

def post(body):

    sensors = Sensors(**body)
    db.session.add(sensors)
    db.session.commit()
    return sensors

def put(body):

    sensors = Sensors.query.get(body['id'])
    if sensors:
        sensors = Sensors(**body)
        db.session.merge(sensors)
        db.session.flush()
        db.session.commit()
        return sensors
    raise NotFound('no such product found with id=' + str(body['id']))

def delete(id):

    sensors = Sensors.query.get(id)
    if sensors:
        db.session.delete(sensors)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such product found with id=' + str(id))