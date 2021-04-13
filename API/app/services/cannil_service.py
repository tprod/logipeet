#!/usr/bin/env python
from models.cannil import Cannil
from config import db
from werkzeug.exceptions import NotFound

def get():

    return Cannil.query.all()

def post(body):

    cannil = Cannil(**body)
    db.session.add(cannil)
    db.session.commit()
    return cannil

def put(body):

    cannil = Cannil.query.get(body['id'])
    if cannil:
        cannil = Cannil(**body)
        db.session.merge(cannil)
        db.session.flush()
        db.session.commit()
        return cannil
    raise NotFound('no such event found with id=' + str(body['id']))

def delete(id):

    cannil = Cannil.query.get(id)
    if cannil:
        db.session.delete(cannil)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such event found with id=' + str(id))