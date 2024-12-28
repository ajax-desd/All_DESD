import copy
import json
telemetry_data = {
        "room1_data" : {
        "Hall_Data" : 27,
        "Romm_Data" : 90
        },
        "balcony_data":{
            "temperature" : 18,
            "humidity" : 60,
            "pressure" : 1013,

        },
        "room2_data" :{
            "temperature" : 28,
            "humidity":87
        }

}

shallow_copy = telemetry_data.copy()

#shallow copy new dict
shallow_copy["room1_data"]["Hall_Data"] = 100
shallow_copy["room1_data"]["aqi"] = 56
#in new dict it doesnot affect the old one if we make new dictinory 

shallow_copy["room3_data"] ={
      "room2_data" :{
            "temperature" : 48,
            "humidity":87,
            "loaction" : "Pune"
        }

}

print("main dict", json.dumps(telemetry_data, indent=4))
print("copy dict", json.dumps(shallow_copy, indent=4))





