#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os



class User(db.Model):
    __tablename__ = 'events'
    idEvents = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    event_init = db.Column(db.String(64))
    event_out = db.Column(db.String(64))
    event_type = db.Column(db.Integer)
    event_name = db.Column(db.String(45))
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}