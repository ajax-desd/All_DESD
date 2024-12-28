from temp import TemperatureSensor
from Sensor import sensor

if __name__ == "__main__":
    temp_sensor = TemperatureSensor() # visible  to all initilize the whole class
    temp_value = temp_sensor.read_sensor_value()
    print(f"Temperature: {temp_value}°C")
    temp_sensor.send_to_cloud(temp_value) #this is because we have inhertied

    print("")
    #overwrite
    temp_sensor = TemperatureSensor("APS-1","F")
    temp_value = temp_sensor.read_sensor_value()
    print(f"Temperature: {temp_value}°C")
    temp_sensor.send_to_cloud(temp_value) #this is because we have inhertied




