
#class
class sensor:
    #constructer variable i.e methid to the class
    def __init__(self,sensor_name,sensor_unit): 
        # init is method if this method does not have attribute it write self means this belong to this class 
        self.sensor_name = sensor_name
        self.sensor_unit = sensor_unit
        print("hello from sensor class")
    
    def send_to_cloud(self,sensor_value):
        print(f"sending {self.sensor_name} data: {sensor_value} {self.sensor_unit} to cloud")

if __name__ == "__main__":
    print("ajay")

#   __name__ this was called when this file run
# main file 33