import socket, sys, select, struct, signal

"""
Aquest programa crea un xat entre dues maquines utilitzant sockets i el protocol TCP.
S'invoca de la seguent manera: python clientservidor.py MODE HOSTADDRESS PORT
Els modes de funcionament son:
	MODE: 1 (argv[1]=1) = servidor
	MODE: 2 (argv[1]=2) = CLIENT
Tambe cal proporcionar la direcció IP del host (no es fa servir quan el programa es crida en mode servidor, pero cal proporcionar-li un valor) i el port sobre el qual s'estableix la comunicació.
"""
#---------------Funcio del client per no esperar els recv ---------------

def no_waitC(llista):
	taula,_,_= select.select(llista , [], [])
	if taula[0] == llista[0]:
		data = sys.stdin.readline()
		s.send(data)
		return True
	elif taula[0] == llista[1]:
		data=llista[1].recv(1024)
		if not data: 
			print "Server disconnected"
			llista[1].close()
			return False
		else:
			print "SERVER: "+data
			return True
	else:
		return 1

#--------------Funcio del servidor per no esperar els recv----------------

def no_waitS(llista):
	taula2,_,_= select.select(llista , [], [])
	if taula2[0] == llista[0]:
		data = sys.stdin.readline()
		conn.send(data)
		return True
	elif taula2[0] == llista[1]:
		data=llista[1].recv(1024)
		if not data:
			print "Client disconnected"
			llista[1].close()
			return False
		else:
			print "CLIENT: "+data
			return True
	else:
		return 1


#--------------PROGRAMA PRINCIPAL--------------

if len(sys.argv) < 4:
	print("Falten arguments. Estructura = SCRIPTNAME MODE HOST PORT")

elif sys.argv[1]!='1' and sys.argv[1]!='2':
	print("Els arguments per definir el mode de funcionament son 1=Server i 2=Client")

elif sys.argv[1]=='1': #SERVIDOR

	HOST = ''
	PORT = int(sys.argv[3])
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((HOST,PORT))
	s.listen(1) 
	print "Server setup done"
	conn, addr = s.accept()
	print 'Connected by ', addr
	taula2=[sys.stdin,conn]
	while True:
		if not no_waitS(taula2):
			break

		

elif sys.argv[1]=='2': #CLIENT

	HOST = sys.argv[2]
	PORT = int(sys.argv[3])
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((HOST,PORT))
	print "Client setup done"
	taula=[sys.stdin,s]
	while True:
		if not no_waitC(taula):
			break
		



