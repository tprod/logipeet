from flask import Flask, jsonify, request
from config import db
import yaml
import os

class Storage(db.Model):

    __tablename__ = 'storage'
    idStorage = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name_product = db.Column(db.String(45) , nullable=False)
    code_product = db.Column(db.String(45) , nullable=False)
    weight = db.Column(db.String(45) , nullable=False)
    amount = db.Coumn(db.Integer , nullable=False)

def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}
