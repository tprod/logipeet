#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.storage_service as storage_service
from models.storage import Storage
from werkzeug.exceptions import HTTPException
import json

bp_storage = Blueprint('storage', 'storage')


@bp_storage.route('/storage', methods=['GET'])
def api_get():
    storage = storage_service.get()
    return jsonify([storage.as_dict() for storage in storage])

@bp_storage.route('/storage', methods=['POST'])
def api_post():
    storage = storage_service.post(request.json)
    return jsonify(storage.as_dict())

@bp_storage.route('/storage/<string:id>', methods=['PUT'])
def api_put(id):
    body = request.json
    body['id'] = id
    res = storage_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, Storage) else jsonify(res)

@bp_storage.route('/storage/<string:id>', methods=['DELETE'])
def api_delete(id):
    res = storage_service.delete(id)
    return jsonify(res)

@bp_storage.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response