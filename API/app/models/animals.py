#!/usr/bin/env python
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from config import db
import yaml
import os

class Animals(db.Model):
    __tablename__ = 'animals'
    id = db.Column(db.Integer(), primary_key=True , unique=True, index=True)
    name_animal = db.Column(db.String(45))
    history_animal = db.Column(db.String(45))
    photo_animal = db.Column(db.String(45))
    race_animal = db.Column(db.String(45))
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}