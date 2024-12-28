
#class
class sensor:  #class name is in pascal name first letter is in captial letter
    """
    Base class for all sensors.
    This class defines common attributes
    and methods for all sensors.
    
    what is constructer ?
    it is in inbuilt  method in python
    it is automatically called when object  of class is created

    """
    
    #constructer variable i.e methid to the class
    def __init__(self,sensor_name,sensor_unit): 
        # init is method if this method does not have attribute it write self means this belong to this class 
        self.sensor_name = sensor_name
        self.sensor_unit = sensor_unit
        print("hello")
    
    def send_to_cloud(self,sensor_value):
        print(f"sending {self.sensor_name} data: {sensor_value} {self.sensor_unit} to cloud")


#How to create an object 
#1. class name
#2. object name
#3. object name = class name()  init
#4. object name.attribute_name
#5. object_name.method_name()

# obj1               passing by class
temp_sensor = sensor("DHT22","C")
temp_sensor.send_to_cloud(20)


humdity_sensor = sensor("CDACsensor","desd")
humdity_sensor.send_to_cloud(20)
# simulator 