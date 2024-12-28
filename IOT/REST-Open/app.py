from flask import Flask, request, jsonify
import json
import os
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

DATA_FILE = 'devices.json'
USERS_FILE = 'users.json'

# Helper functions to read and write JSON data
def read_json_file(file_path):
    if not os.path.exists(file_path):
        with open(file_path, 'w') as file:
            json.dump({}, file)
    with open(file_path, 'r') as file:
        return json.load(file)

def write_json_file(file_path, data):
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=4)

@app.route('/', methods=['GET'])
def welcome_to_desd_lab():
    devices = read_json_file(DATA_FILE)
    return "welcome to DESD REST API lab"

# Routes for device operations
@app.route('/devices', methods=['GET'])
def get_all_devices():
    devices = read_json_file(DATA_FILE)
    return jsonify(devices)

@app.route('/device/<device_id>', methods=['GET'])
def get_device(device_id):
    devices = read_json_file(DATA_FILE)
    device = devices.get(device_id)
    if device:
        return jsonify(device)
    else:
        return jsonify({'message': 'Device not found'}), 404

@app.route('/device', methods=['POST'])
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
def update_device(device_id):
    update_data = request.json
    devices = read_json_file(DATA_FILE)
    if device_id not in devices:
        return jsonify({'message': 'Device not found'}), 404
    devices[device_id].update(update_data)
    write_json_file(DATA_FILE, devices)
    return jsonify({'message': 'Device updated successfully'})

@app.route('/device/<device_id>', methods=['DELETE'])
def delete_device(device_id):
    devices = read_json_file(DATA_FILE)
    if device_id in devices:
        del devices[device_id]
        write_json_file(DATA_FILE, devices)
        return jsonify({'message': 'Device deleted successfully'})
    else:
        return jsonify({'message': 'Device not found'}), 404

# Routes for user authentication
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
        return jsonify({'message': 'Signed in successfully'})
    else:
        return jsonify({'message': 'Invalid username or password'}), 401

if __name__ == '__main__':
    app.run(debug=True)
