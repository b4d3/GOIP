#A small python server program that excanges data between peers!

import socket

#gets a message from the remote ncl client and stores the information about that client in a list of clients
#blocking call
def get_data(s, client):
    message, address = s.recvfrom(1024)
    client.append(address)
    print(client)


#gets the message from one peer and then routes it to the other one
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


def main():

    #creates the socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    host = socket.gethostname()
    port = 12345
    s.bind((host, port))

    #sets the peers variable to an empty list
    peers = []


    #blocking call
    #receives data from both peers and stores information about them in a list of peers
    get_data(s, peers)
    get_data(s, peers)
    s.sendto("Connection to peer established!", peers[0])
    s.sendto("Connection to peer established!", peers[1])

    #starts an infinite message router which routes the messages from one peer to another
    infinite_message_router(s, peers)

main()
