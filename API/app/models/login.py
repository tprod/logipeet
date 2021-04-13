#!/usr/bin/env python
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from config import db
import yaml
import os


class Login(db.Model):
    __tablename__ = 'login'
    id = db.Column(db.Integer(), primary_key=True , unique=True, index=True)
    email = db.Column(db.String(64))
    time_in = db.Column(db.DateTime)
    time_out = db.Column(db.DateTime)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}