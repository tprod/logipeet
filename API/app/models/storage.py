from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from config import db
import yaml
import os

class Storage(db.Model):

    __tablename__ = 'storage'
    id = db.Column(db.Integer(), primary_key=True , unique=True, index=True)
    name_product = db.Column(db.String(45) , nullable=False)
    code_product = db.Column(db.String(45) , nullable=False)
    weight = db.Column(db.String(45) , nullable=False)
    amount = db.Column(db.Integer , nullable=False)
    def as_dict(self):
       return {c.name: getattr(self, c.name) for c in self.__table__.columns}


    def __init__(self,name_product,code_product,weight,amount):

            self.name_product = name_product
            self.code_product = code_product
            self.weight = weight
            self.amount = amount