#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os



class User(db.Model):
    __tablename__ = 'cannil'
    idCannil = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name_cannil = db.Column(db.String(45))
    adress_cannil = db.Column(db.String(45))
    coordinates_cannil = db.Column(db.String(45))
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}