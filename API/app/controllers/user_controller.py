#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.user_service as user_service
from models.user import User
from werkzeug.exceptions import HTTPException
import json

bp_user = Blueprint('users', 'users')

@bp_user.route('/users', methods=['GET'])
def api_get():
    users = user_service.get()
    return jsonify([user.as_dict() for user in users])

@bp_user.route('/users', methods=['POST'])
def api_post():
    user = user_service.post(request.json)
    return jsonify(user.as_dict())

@bp_user.route('/users/<string:id>', methods=['PUT'])
def api_put(id):
    body = request.json
    body['id'] = id
    res = user_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, User) else jsonify(res)

@bp_user.route('/users/<string:id>', methods=['DELETE'])
def api_delete(id):
    res = user_service.delete(id)
    return jsonify(res)

@bp_user.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response