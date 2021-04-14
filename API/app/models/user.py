#!/usr/bin/env python
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash
from config import db
import os

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name = db.Column(db.String(64), nullable=False)
    email = db.Column(db.String(64), nullable=False, unique=True)
    password = db.Column(db.String(128), nullable=False)
    age = db.Column(db.Integer)
    gender = db.Column(db.Boolean)
    address = db.Column(db.String(64)) 
    phone = db.Column(db.String(9))
    type_user = db.Column(db.Boolean)
    active_user =db.Column(db.Boolean)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}
       
    def set_password(self, password):
        
        self.password = generate_password_hash(
            password,
            method='sha256'
        )

    def check_password(self, password):
        
        return check_password_hash(self.password, password)