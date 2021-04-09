#!/usr/bin/env python
from models.storage import Storage
from config import db
from werkzeug.exceptions import NotFound

def get():

    return Storage.query.all()

def post(body):

    storage = Storage(**body)
    db.session.add(storage)
    db.session.commit()
    return storage

def put(body):

    storage = Storage.query.get(body['id'])
    if storage:
        storage = Storage(**body)
        db.session.merge(storage)
        db.session.flush()
        db.session.commit()
        return storage
    raise NotFound('no such product found with id=' + str(body['id']))

def delete(id):

    storage = Storage.query.get(id)
    if storage:
        db.session.delete(storage)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such product found with id=' + str(id))