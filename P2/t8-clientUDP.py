# Echo client program
import socket

HOST = '172.20.13.1'    # The remote host
PORT = 10000             # The same port as used by the server
Missatge = "Missatge de prova del client"
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.sendto(Missatge, (HOST, PORT))
while True:
	data, addr = s.recvfrom(1024) 
	print "Missatge rebut:", data
	break
s.close()