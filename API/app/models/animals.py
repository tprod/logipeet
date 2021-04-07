#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os



class User(db.Model):
    __tablename__ = 'animals'
    idAnimals = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name_animal = db.Column(db.String(45))
    histoy_animal = db.Column(db.String(45))
    photo_animal = db.Column(db.String(45))
    race_animal = db.Column(db.String(45))
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}