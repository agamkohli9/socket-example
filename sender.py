import socket            
from time import sleep
 
# connect to localhost:8080
s = socket.socket()        
port = 8080
s.bind(('', port))        
s.listen(5)    
c, addr = s.accept()
msg ="""[
    {
        "objects": [
            {
                "class": "car",
                "heading": -135.54637281438883,
                "lat": 42.300862173106005,
                "lon": -83.69792816363847,
                "object_id": 42
            },
            {
                "class": "pedestrian",
                "heading": 65.36442874827932,
                "lat": 42.30099394023257,
                "lon": -83.69803984060701,
                "object_id": 45
            }
        ],
        "timestamp": 1669910806531
    }
]"""
while True:
  # send message 
  c.send(msg.encode())

  print('message sent')

  sleep(5)
