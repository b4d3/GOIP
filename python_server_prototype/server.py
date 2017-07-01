#A small python server program that excanges the data between peers!

import socket

def get_data(s, client):
    message, address = s.recvfrom(1024)
    client.append(address)
    print(client)


def infinite_message_router(s, peers):
    while True:
        message, address = s.recvfrom(1024)
        print "peers0 .. " + str(peers[0])
        print "peers1 .. " + str(peers[1])
        print "address .. " + str(address)
        print message
        if address != peers[0]:
            s.sendto(message, peers[0])
        else:
            s.sendto(message, peers[1])

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host = socket.gethostname()
port = 12345
s.bind((host, port))

peers = []

get_data(s, peers)
get_data(s, peers)


s.sendto("Connection to peer established!", peers[0])
s.sendto("Connection to peer established!", peers[1])

infinite_message_router(s, peers)


print ("End of execution")

