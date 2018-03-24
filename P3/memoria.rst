Pràctica 3: Servei de noms
==========================

:authors: Joan Jiménez Alarcón

Objectiu
--------
L'objectiu d'aquesta pràctica és implementar servidors DNS i configurar-los. Per a assolir aquest objectiu s'ha utilitzat el paquet bind9.

Tàsques realitzades
-------------------

El primer pas ha estat crear dues màquines virtuals noves, on hi haurà els serveis de DNS primari i secundari. A cadascuna se li ha assignat una IP dins del rang assignat del VPN de l'assignatura al grup, i s'ha respectat el pacte de que aquestes màquines tinguin la IP 172.20.13.4 pel DNS primari i la IP 172.20.13.5 pel DNS secundari.

Els passos per a crear i configurar la màquina del DNS primari han estat els següents:
1) /var/lib/lxc/DNSPrimari/config

	S'ha modificat aquest fitxer de configuració del contenidor per tal d'establir una IP fixa en aquesta màquina.
	::
		FITXER
____A PARTIR DAQI

2) /etc/network/interfaces

   Dins la maquina virtual, hem modificat l'arxiu interfaces i l'hem deixat d'aquesta manera:
   ::
      # The loopback network interface
      auto lo
      iface lo inet loopback

      auto eth0
      iface eth0 inet manual
      dns-nameservers 127.0.0.1 172.20.6.4

3) /etc/resolv.conf

   Farem que apunti a la xarxa local.
   ::
      nameserver 127.0.0.1

4) /etc/bind/named.conf.local

   Dins d'aquest fitxer definirem la nostra zona. Ho hem fet així:
   ::
      zone "g7.asi.itic.cat" IN {
          type master;
          file "/etc/bind/db.g7.asi.itic.cat";
          allow-transfer {172.20.7.5;};
      };

      // Consider adding the 1918 zones here, if they are not used in your
      // organization
      //include "/etc/bind/zones.rfc1918";

5) /etc/bind/db.g7.asi.itic.cat

   Dins aquest fitxer creem la nostra taula de resolució de noms.
   ::
      $TTL 5H
      g7.asi.itic.cat.        IN      SOA     ns.g7.asi.itic.cat.
                                               adriiauguets@gmail.com. (
                              2014011201      ; serial
                              7200            ; Refresh
                              3600            ; Retry
                              1W              ; Expire
                              1W )            ; Negative Cache TTL
      ;servidors de noms
      g7.asi.itic.cat.        IN      NS      ns.g7.asi.itic.cat.
      g7.asi.itic.cat.        IN      NS      ns2.g7.asi.itic.cat.

      ;Registres A
      ns.g7.asi.itic.cat.     IN      A       172.20.7.4
      ns2.g7.asi.itic.cat.    IN      A       172.20.7.5
      g7.asi.itic.cat.        IN      A       172.20.7.6

   En aquesta taula definim de moment nomes els Registres A per tal que aquests noms responguin amb l'adreça de la maquina esperada.

   Un cop feta aquesta configuració només queda definir el DNS secundari, ip 172.20.7.5 .

6) DNS Secundari. /etc/bind/named.conf.local
   Hem de canviar uns noms a diferencia del fitxer del dns
   ::
     zone "g7.asi.itic.cat" IN {
        type slave;
        file "db.g7.asi.itic.cat";
        masters {172.20.7.4;
        };
     };

     // Consider adding the 1918 zones here, if they are not used in your
     // organization
     //include "/etc/bind/zones.rfc1918";



7) /etc/bind/db.g7.asi.itic.cat

   Per lo tant la resolucio de noms del DNS secundari quedarà de la següent manera:

   ::

	$TTL 1w
      	g7.asi.itic.cat         IN      SOA     ns.g7.asi.itic.cat
	 					pavel.macutela1@gmail.com.(
	                	2013021201      ;serial
			        2h              ;refresh
          		        1h              ;retry
                       	        1w              ;Expire
                       	        1w )            ; Negative cache TTL

     ;servidor de noms
     g7.asi.itic.cat.        IN      NS      ns.g7.asi.itic.cat.
     g7.asi.itic.cat.        IN      NS      ns2.g7.asi.itic.cat.

     ;Registros A
     ns                      IN      A       172.20.7.4
     ns2                     IN      A       172.20.7.5
     g7.asi.itic.cat         IN      A       172.20.7.6


8) Des de la maquina 170.20.7.5 executem la comanda: **dig ns.g7.asi.itic.cat** y el resultat obtingut es:

   ::

	; <<>> DiG 9.10.3-P4-Ubuntu <<>> ns.g7.asi.itic.cat
	;; global options: +cmd
	;; Got answer:
	;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 5654
 	;; flags: qr aa rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 2, ADDITIONAL: 2

	;; OPT PSEUDOSECTION:
	; EDNS: version: 0, flags:; udp: 4096
	;; QUESTION SECTION:
	;ns.g7.asi.itic.cat.		IN	A

 	;; ANSWER SECTION:
	ns.g7.asi.itic.cat.	18000	IN	A	172.20.7.4

 	;; AUTHORITY SECTION:
	g7.asi.itic.cat.	18000	IN	NS	ns.g7.asi.itic.cat.
	g7.asi.itic.cat.	18000	IN	NS	ns2.g7.asi.itic.cat.

	;; ADDITIONAL SECTION:
	ns2.g7.asi.itic.cat.	18000	IN	A	172.20.7.5

        ;; Query time: 94 msec
 	;; SERVER: 172.20.7.4#53(172.20.7.4)
	;; WHEN: Wed Mar 22 19:01:24 UTC 2017
	;; MSG SIZE  rcvd: 111

Dig retorna el resultat esperat, per lo tant podem donat per finalitzada la pràctrica y el seu correcte funcionament