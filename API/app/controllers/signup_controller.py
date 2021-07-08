#!/usr/bin/env python
import json
import services.user_service as user_service
from datetime import timedelta
from flask import Blueprint, jsonify, request
from models.user import User
from werkzeug.exceptions import HTTPException
from flask import abort
from flask import jsonify

bp_signup = Blueprint('signup', 'signup')

@bp_signup.route('/signup', methods=['POST'])
def api_sign():
    
    name = request.form['name']
    username = request.form['email']
    password = request.form['password']
    
    res = user_service.sign_up(name,username,password)
    if res == None:
        return abort(400)
    else:
        resp = jsonify(success=True)
        return resp
        