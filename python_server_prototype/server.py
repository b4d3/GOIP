#A small python server program that excanges the data between peers!

import socket               

def get_data(socket, client):
    message, address = s.recvfrom(1024)
    client.append(address)
    print(client)

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)        
host = socket.gethostname() 
port = 12345                
s.bind((host, port))        

peers = []

get_data(s, peers)
get_data(s, peers)

print (peers[0])
print (peers[1])

s.sendto(str(peers[0]) + "\n", peers[1])
s.sendto(str(peers[1]) + "\n", peers[0])





print ("End of execution")

