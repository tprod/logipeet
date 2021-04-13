#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.cannil_service as cannil_service
from models.cannil import Cannil
from werkzeug.exceptions import HTTPException
import json

bp_cannil = Blueprint('cannil', 'cannil')


@bp_cannil.route('/cannil', methods=['GET'])
def api_get():
    cannil = cannil_service.get()
    return jsonify([cannil.as_dict() for cannil in cannil])

@bp_cannil.route('/cannil', methods=['POST'])
def api_post():
    cannil = cannil_service.post(request.json)
    return jsonify(cannil.as_dict())

@bp_cannil.route('/cannil/<string:id>', methods=['PUT'])
def api_put(id):
    body = request.json
    body['id'] = id
    res = cannil_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, Cannil) else jsonify(res)

@bp_cannil.route('/cannil/<string:id>', methods=['DELETE'])
def api_delete(id):
    res = cannil_service.delete(id)
    return jsonify(res)

@bp_cannil.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response