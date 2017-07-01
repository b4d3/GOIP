import threading
import socket
import sys

#this will run on a separate thread and simply print any messages received from the peer
def message_receiver(socket):
    while True:
        data, addr = socket.recvfrom(1024)
        print "Peer: ", data

#sends message to the connected peer
def message_sender(socket, local_peer_address, message):
    socket.sendto(message, local_peer_address)

def main():
    #setting the connection properties
    UDP_IP = "localhost"
    if len(sys.argv) is 1: 
        UDP_PORT = 56712
    else:
        UDP_PORT = int(sys.argv[1])

    #creating the socket object
    local_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    #sending the message that ncl is expecting to receive to establish connection
    message_sender(local_socket, (UDP_IP, UDP_PORT), "init_connection")
    
    #start listening for any messages on a separate thread
    receiver_thread = threading.Thread(target=message_receiver, args=(local_socket,))
    receiver_thread.start()

    #infinite loop which allows user to send messages from terminal
    while True:
        user_message = sys.stdin.readline()
        message_sender(local_socket, (UDP_IP, UDP_PORT), user_message)

main()
