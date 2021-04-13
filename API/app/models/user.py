#!/usr/bin/env python
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from passlib.hash import pbkdf2_sha256
from config import db
import os

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name = db.Column(db.String(64), nullable=False)
    email = db.Column(db.String(64), nullable=False)
    password = db.Column(db.String(128), nullable=False)
    age = db.Column(db.Integer)
    gender = db.Column(db.Boolean)
    address = db.Column(db.String(64)) 
    phone = db.Column(db.String(9))
    type_user = db.Column(db.Boolean)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}
       
  