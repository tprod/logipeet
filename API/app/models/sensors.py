#!/usr/bin/env python
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from config import db
import yaml
import os



class Sensors(db.Model):
    __tablename__ = 'sensors'
    id = db.Column(db.Integer(), primary_key=True , unique=True, index=True)
    serial_number = db.Column(db.Integer)
    inst_time = db.Column(db.DateTime)
    amount_food = db.Column(db.Integer)
    amount_water = db.Column(db.Integer)
    battery = db.Column(db.Integer)
    last_sup = db.Column(db.DateTime)
    status_sens = db.Column(db.Boolean)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}