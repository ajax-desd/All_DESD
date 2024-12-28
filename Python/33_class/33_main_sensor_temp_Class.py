from temp import TemperatureSensor
from Sensor import sensor

if __name__ == "__main__":
    temp_sensor = TemperatureSensor()
    temp_value = temp_sensor.read_sensor_value()
    print(f"Temperature: {temp_value}°C")
