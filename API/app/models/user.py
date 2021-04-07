#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os



class User(db.Model):
    __tablename__ = 'users'
    idUser = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name = db.Column(db.String(64), nullable=False)
    email = db.Column(db.String(64), unique=True, nullable=False)
    password = db.Column(db.String(128))
    age = db.Column(db.Integer)
    gender = db.Column(db.Boolean)
    address = db.Column(db.String(64)) 
    phone = db.Column(db.String(9))
    type_user = db.Column(db.Boolean)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}