#!/usr/bin/env python
from models.animals import Animals
from config import db
from werkzeug.exceptions import NotFound

def get():

    return Animals.query.all()

def post(body):

    animals = Animals(**body)
    db.session.add(animals)
    db.session.commit()
    return animals

def put(body):

    animals = Animals.query.get(body['id'])
    if animals:
        animals = Animals(**body)
        db.session.merge(animals)
        db.session.flush()
        db.session.commit()
        return animals
    raise NotFound('no such event found with id=' + str(body['id']))

def delete(id):

    animals = Animals.query.get(id)
    if animals:
        db.session.delete(animals)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such event found with id=' + str(id))