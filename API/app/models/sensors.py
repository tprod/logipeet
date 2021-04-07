#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os



class User(db.Model):
    __tablename__ = 'sensors'
    idSensors = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    type_sensor = db.Column(db.Integer)
    serial_number = db.Column(db.Integer)
    status_sen = db.Column(db.String(64))
    log_sens = db.Column(db.String(64))
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}