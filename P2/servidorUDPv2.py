# Echo server program
import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 10000              # Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((HOST, PORT))

while 1:
    data,addr = s.recvfrom(1024)
    if not data: break
    s.sendto('Missatge de prova del server',addr)
    print "Connexio d'entrada "+str(addr)+" "+data
conn.close()