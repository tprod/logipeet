#!/usr/bin/env python
from flask import Blueprint, jsonify, request
import services.events_service as events_service
from models.events import Events
from werkzeug.exceptions import HTTPException
from flask_jwt_extended import jwt_required
import json

bp_events = Blueprint('events', 'events')


@bp_events.route('/events', methods=['GET'])
@jwt_required()
def api_get():
    events = events_service.get()
    return jsonify([events.as_dict() for events in events])

@bp_events.route('/events', methods=['POST'])
@jwt_required()
def api_post():
    events = events_service.post(request.json)
    return jsonify(events.as_dict())

@bp_events.route('/events/<string:id>', methods=['PUT'])
@jwt_required()
def api_put(id):
    body = request.json
    body['id'] = id
    res = events_service.put(body)
    return jsonify(res.as_dict()) if isinstance(res, Events) else jsonify(res)

@bp_events.route('/events/<string:id>', methods=['DELETE'])
@jwt_required()
def api_delete(id):
    res = events_service.delete(id)
    return jsonify(res)

@bp_events.errorhandler(HTTPException)
def handle_exception(e):
    response = e.get_response()
    response.data = json.dumps({
        'success': False,
        "message": e.description
    })
    response.content_type = "application/json"
    return response