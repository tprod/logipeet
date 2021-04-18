#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.sensors_service as sensors_service
from models.sensors import Sensors
from werkzeug.exceptions import HTTPException
from flask_jwt_extended import jwt_required
import json

bp_sensors = Blueprint('sensors', 'sensors')

@bp_sensors.route('/sensors', methods=['GET'])
@jwt_required()
def api_get():
    sensors = sensors_service.get()
    return jsonify([sensors.as_dict() for sensors in sensors])

@bp_sensors.route('/sensors', methods=['POST'])
@jwt_required()
def api_post():
    sensors = sensors_service.post(request.json)
    return jsonify(sensors.as_dict())

@bp_sensors.route('/sensors/<string:id>', methods=['PUT'])
@jwt_required()
def api_put(id):
    body = request.json
    body['id'] = id
    res = sensors_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, Sensors) else jsonify(res)

@bp_sensors.route('/sensors/<string:id>', methods=['DELETE'])
@jwt_required()
def api_delete(id):
    res = sensors_service.delete(id)
    return jsonify(res)

@bp_sensors.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response