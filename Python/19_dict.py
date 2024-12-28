"""
key value pair data structure
mutable
dictonary_name = {
    "key1" : value,
    "key2" : "value", #string
}


if there is 2 key2 -> if has same it simply overwrite it 
"""
sensor_reading = {
    "temperature" : 25.5,
    "humidity" : 60,
    "device_name" : "ESP-32",
    "is_online" : True
}


print(sensor_reading)

#Accessing values
print("current room teperature ",sensor_reading["temperature"])

#Add new key
sensor_reading["Fermware_version"] = "1.2.1"

print(sensor_reading)

#updating the value
sensor_reading["temperature"] = 26.5
print(sensor_reading)
#delete key
sensor_reading.pop("humidity")
print(sensor_reading)

# check the existance of a key it automatic alter
if "firmvarse_version" in sensor_reading:
    print("firmware version is available : ",sensor_reading["firmware_version"])
#remove a key
del sensor_reading["device_name"]
print(sensor_reading)


#iterate throgh dict
for sensor , value in sensor_reading.items():
    print(f"{sensor.capitalize()} : {value}")

#get all keys 
print(sensor_reading.keys())
dict_keys = list(sensor_reading.keys())#type cast to list to get list only
print(dict_keys)

print(sensor_reading.values())
dict_values = list(sensor_reading.values())#type cast to list to get list only
print(dict_values)
#dict_values.sort()#sort the list
#dict_values.sort(reverse=True)#sort in reverse order

#one more usecase left
#dict_values.sort(key=lambda x:x[0])#sort based on first element of tuple
#dict_values.sort(key=lambda x:x[0],reverse=True)#sort in reverse order based on

#Default values another way to retrive values
humidity = sensor_reading.get("Humidity","not availbe")
print(humidity)

temperature = sensor_reading.get("temperature","not availbe")
print(temperature)




