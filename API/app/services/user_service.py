#!/usr/bin/env python
from models.user import User
from config import db
from werkzeug.exceptions import NotFound

def get():

    return User.query.all()

def get_auth(email,password):

    auth = User.query.filter((User.email == email) & (User.password == password) & User.active_user == 1).first()
    return auth

def get_auth_admin(email,password):

    auth = User.query.filter((User.email == email) & (User.password == password) & (User.active_user == 1) & (User.type_user == 1)).first()
    return auth


def sign_up(name,email,password):
    
    sign = User(name,email,password)
    db.session.add(sign)
    db.session.commit()
    return sign
    

def post(body):

    user = User(**body)
    db.session.add(user)
    db.session.commit()
    return user

def put(body):

    user = User.query.get(body['id'])
    if user:
        user = User(**body)
        db.session.merge(user)
        db.session.flush()
        db.session.commit()
        return user
    raise NotFound('no such entity found with id=' + str(body['id']))

def delete(id):

    user = User.query.get(id)
    if user:
        db.session.delete(user)
        db.session.commit()
        return {'success': True}
    raise NotFound('no such entity found with id=' + str(id))


