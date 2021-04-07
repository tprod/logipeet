#!/usr/bin/env python
from flask import Flask, jsonify, request
from config import db
import yaml
import os


class User(db.Model):
    __tablename__ = 'login'
    idLogin = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    time_in = db.Column(db.datetime)
    time_out = db.Column(db.datetime)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}