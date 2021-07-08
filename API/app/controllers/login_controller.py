#!/usr/bin/env python
import json
import services.user_service as user_service
from datetime import timedelta
from flask import Blueprint, jsonify, request
from models.user import User
from werkzeug.exceptions import HTTPException
from config import jwt
from flask_jwt_extended import create_access_token, create_refresh_token
from flask_jwt_extended import get_jwt_identity
from flask import abort

bp_login = Blueprint('login', 'login')

@bp_login.route('/login', methods=['POST'])
def api_auth():
    
    username = request.form['email']
    password = request.form['password']
    
    res = user_service.get_auth(username,password)
    if res == None:
        
        return abort(400)
    else:
        
        acess_token = create_access_token(identity=username, expires_delta=timedelta(seconds=3600))
        refresh_token = create_refresh_token(identity=username)
        return jsonify({
             'acess_token': acess_token,
             'refresh_token': refresh_token,
         })

@bp_login.route('/admin/login', methods=['POST'])
def api_auth_admin():
    info_auth = request.get_json() 
    username = info_auth['email']
    password = info_auth['password']
    res = user_service.get_auth_admin(username,password)
    if res == None:
        return "Wrong username or password"
    else:
        
        acess_token = create_access_token(identity=username, expires_delta=timedelta(seconds=3600))
        refresh_token = create_refresh_token(identity=username)
        return jsonify({
             'acess_token': acess_token,
             'refresh_token': refresh_token,
         })

@bp_login.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response

