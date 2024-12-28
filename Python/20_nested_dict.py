#IOT Data
telemetry_data = {
        "room1_data" : {
        "Hall_Data" : 27,
        "Romm_Data" : 90
        },
        "balcony_data":{
            "temperature" : 18,
            "humidity" : 60,
            "pressure" : 1013,
            "firmware_status":{
                "firmware_version" : "1.0.0",
                "status":"availabe",
                "last_update" : "25-Dec-2024"
            }

        },
        "room2_data" :{
            "temperature" : 28,
            "humidity":87
        }

}

#accesiing the balcony temperature
print(telemetry_data["balcony_data"]["temperature"])
print(telemetry_data["balcony_data"]["firmware_status"]["last_update"])

#A code written for dedicated hardware