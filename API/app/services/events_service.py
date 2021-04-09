#!/usr/bin/env python
from models.events import Events
from config import db
from werkzeug.exceptions import NotFound

def get():

    return Events.query.all()

def post(body):

    events = Events(**body)
    db.session.add(events)
    db.session.commit()
    return events

def put(body):

    events = Events.query.get(body['id'])
    if events:
        events = Events(**body)
        db.session.merge(events)
        db.session.flush()
        db.session.commit()
        return events
    raise NotFound('no such event found with id=' + str(body['id']))

def delete(id):

    events = Events.query.get(id)
    if events:
        db.session.delete(events)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such event found with id=' + str(id))