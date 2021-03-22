from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy 
from flask_marshmallow import Marshmallow
import pymysql

pymysql.install_as_MySQLdb()
#Inicialização do API

api = Flask(__name__)

@api.route('/', methods=['GET'])
def get():
    return jsonify({'msg': 'OK'})

# Criar db com o nome 
# 'logipeet # mysql > CREATE DATABASE logipeet'
# password do root logipeet

#Ligação db
api.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://root:logipeet@localhost/logipeet'
api.config['SQLALCHEMY_TRACK_MODIFICATIOSN'] = True

#Init db

db = SQLAlchemy(api)

#Init ma

ma = Marshmallow(api)


#Modelo de entidades

class User(db.Model):
    idUser = db.Column(db.Integer, primary_key=True , unique=True, index=True)
    name = db.Column(db.String(64), nullable=False)
    email = db.Column(db.String(64), unique=True, nullable=False)
    password = db.Column(db.String(128))
    age = db.Column(db.Integer)
    gender = db.Column(db.Boolean)
    address = db.Column(db.String(64)) 
    phone = db.Column(db.String(9))
    type_user = db.Column(db.Boolean)


def __init__(self, name, email, password, age, gender, address, phone, type_user):

    self.name = name
    self.email = email
    self.password = password
    self.age = age
    self.gender = gender
    self.address = address
    self.phone = phone
    self.type_user


#Schema Users

class UserSchema(ma.Schema):
    class Meta:
        fields = ('idUser','name','email','password','age','gender','address','phone','type_user')


# Init schema
user_schema = UserSchema



#Criar Users

@api.route('/users/', methods=['POST'])
def add_users():
    name = request.json['name']
    email = request.json['email']
    password = request.json['password'] 
    age = request.json['age']
    gender = request.json['gender']
    address = request.json['address']
    phone = request.json['phone']
    type_user = request.json['type_user']

    new_user = User(name, email, password, age ,gender, address, phone, type_user)
    
    db.session.add(new_user)
    db.session.commit()

    return user_schema.jsonify(new_user)

#Obter users

@api.route('/users/<idUser>', methods=['GET'])
def get_users():
    all_users = User.query.all()
    result = UserSchema.dump(all_users)
    return jsonify(result)


# Run Server    

if __name__ == '__main__':
    api.run(debug=True)


