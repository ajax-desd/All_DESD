# CHILD CLASS

from Sensor import sensor
#create a child class from parent class

# this is inheritance
class TemperatureSensor(sensor):
    def __init__(self,sensor_name="DHT22",sensor_unit ="C"):
       
        # super help to call the parent class method
        """
        super keyword allows a subcass to invoke from its parent class
        """

        super().__init__(sensor_name,sensor_unit) #it call Sensor.py init constructor
    
    def read_sensor_value(self):
        import random
        return round(random.uniform(0.0,50.0),2)
    
# 3 file instruction

        
