#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.animals_service as animals_service
from models.animals import Animals
from werkzeug.exceptions import HTTPException
import json

bp_animals = Blueprint('animals', 'animals')


@bp_animals.route('/animals', methods=['GET'])
#@jwt_required()
def api_get():
    animals = animals_service.get()
    return jsonify([animals.as_dict() for animals in animals])

@bp_animals.route('/animals', methods=['POST'])
#@jwt_required()
def api_post():
    animals = animals_service.post(request.json)
    return jsonify(animals.as_dict())

@bp_animals.route('/animals/<string:id>', methods=['PUT'])
#@jwt_required()
def api_put(id):
    body = request.json
    body['id'] = id
    res = animals_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, Animals) else jsonify(res)

@bp_animals.route('/animals/<string:id>', methods=['DELETE'])
#@jwt_required()
def api_delete(id):
    res = animals_service.delete(id)
    return jsonify(res)

@bp_animals.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response