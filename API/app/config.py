#!/usr/bin/env python
import os
import yaml

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

from flask_jwt_extended import create_access_token
from flask_jwt_extended import get_jwt_identity
from flask_jwt_extended import jwt_required
from flask_jwt_extended import JWTManager


app = Flask(__name__)

config_obj = yaml.load(open('config.yaml'), Loader=yaml.Loader)

database_url = os.getenv('SQLALCHEMY_DATABASE_URI')

app.config['SQLALCHEMY_DATABASE_URI'] = config_obj['SQLALCHEMY_DATABASE_URI'] if database_url is None else database_url
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.config['JWT_SECRET_KEY'] = "logipeet_seguro"

db = SQLAlchemy(app)

migrate = Migrate(app, db)

jwt = JWTManager(app)