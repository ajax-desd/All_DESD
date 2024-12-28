Endpoints:

    Devices:
        GET /devices: Retrieve all devices.
        GET /device/<device_id>: Retrieve a single device by ID.
        POST /device: Create a new device (expects a JSON payload with device details).
        PUT /device/<device_id>: Update a device by ID (expects a JSON payload with updated details).
        DELETE /device/<device_id>: Delete a device by ID.
    Authentication:
        POST /signup: Sign up a new user (expects a JSON payload with username and password).
        POST /signin: Sign in an existing user (expects a JSON payload with username and password).

