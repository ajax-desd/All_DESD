sensor_names = ["temperature", "humidity"]
sensor_readings =[22,27]
telemetry_data  = dict(zip(sensor_names,sensor_readings))
print(telemetry_data)

#size of shoulde be same 
sensor_names = ["acts", "rollno"]
sensor_readings =[22,27,23]
#telemetry_data  = dict(zip(sensor_names,sensor_readings))
#map reverse                key                 value
telemetry_data  = dict(zip(sensor_readings,sensor_names))
print(telemetry_data)  

#if uneqaul it ignores it but for best practice we should make sure that the size of both list are same

