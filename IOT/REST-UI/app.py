from flask import Flask, request, jsonify, render_template
from flask_jwt_extended import JWTManager, create_access_token, jwt_required, get_jwt_identity
import json
import os
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

app.config['JWT_SECRET_KEY'] = 'your_jwt_secret_key'  # Change this to a random secret key
jwt = JWTManager(app)

DATA_FILE = 'devices.json'
USERS_FILE = 'users.json'

def read_json_file(file_path):
    if not os.path.exists(file_path):
        with open(file_path, 'w') as file:
            json.dump({}, file)
    with open(file_path, 'r') as file:
        return json.load(file)

def write_json_file(file_path, data):
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=4)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/devices', methods=['GET'])
@jwt_required()
def get_all_devices():
    devices = read_json_file(DATA_FILE)
    return jsonify(devices)

@app.route('/device/<device_id>', methods=['GET'])
@jwt_required()
def get_device(device_id):
    devices = read_json_file(DATA_FILE)
    device = devices.get(device_id)
    if device:
        return jsonify(device)
    else:
        return jsonify({'message': 'Device not found'}), 404

@app.route('/device', methods=['POST'])
@jwt_required()
def create_device():
    new_device = request.json
    devices = read_json_file(DATA_FILE)
    device_id = new_device.get('id')
    if device_id in devices:
        return jsonify({'message': 'Device already exists'}), 400
    devices[device_id] = new_device
    write_json_file(DATA_FILE, devices)
    return jsonify({'message': 'Device created successfully'}), 201

@app.route('/device/<device_id>', methods=['PUT'])
@jwt_required()
def update_device(device_id):
    update_data = request.json
    devices = read_json_file(DATA_FILE)
    if device_id not in devices:
        return jsonify({'message': 'Device not found'}), 404
    devices[device_id].update(update_data)
    write_json_file(DATA_FILE, devices)
    return jsonify({'message': 'Device updated successfully'})

@app.route('/device/<device_id>', methods=['DELETE'])
@jwt_required()
def delete_device(device_id):
    devices = read_json_file(DATA_FILE)
    if device_id in devices:
        del devices[device_id]
        write_json_file(DATA_FILE, devices)
        return jsonify({'message': 'Device deleted successfully'})
    else:
        return jsonify({'message': 'Device not found'}), 404

@app.route('/signup', methods=['POST'])
def sign_up():
    user_data = request.json
    username = user_data.get('username')
    password = user_data.get('password')

    if not username or not password:
        return jsonify({'message': 'Username and password required'}), 400

    users = read_json_file(USERS_FILE)
    if username in users:
        return jsonify({'message': 'User already exists'}), 400

    hashed_password = generate_password_hash(password)
    users[username] = hashed_password
    write_json_file(USERS_FILE, users)
    return jsonify({'message': 'User created successfully'}), 201

@app.route('/signin', methods=['POST'])
def sign_in():
    user_data = request.json
    username = user_data.get('username')
    password = user_data.get('password')

    users = read_json_file(USERS_FILE)
    hashed_password = users.get(username)

    if hashed_password and check_password_hash(hashed_password, password):
        access_token = create_access_token(identity=username)
        return jsonify({'access_token': access_token})
    else:
        return jsonify({'message': 'Invalid username or password'}), 401

if __name__ == '__main__':
    app.run(debug=True)
