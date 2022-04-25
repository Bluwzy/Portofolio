#! /usr/bin/env python3


import nmap
import scapy.all as scapy
import re
import argparse
import socket
import os
import sys
import platform
from datetime import datetime


i = 0
print("NET G")
print("<----------------------------------------------------->")

hostname = socket.gethostname()    
IPAddr = socket.gethostbyname(hostname)
nm = nmap.PortScanner()
machine = nm.scan(IPAddr, arguments='-O')
print("Your Computer Name is:" + machine['scan'][IPAddr]['osmatch'][0]['osclass'][0]['osfamily'])        
print("Your Computer IP Address is:" + IPAddr)
while (i != 1):
    resp = input("""\nPlease enter the type of scan you want to run
                        1)Network Scan
                        2)Port scan
                        3)OS fingerprint Scan
                        4)Exit \n""")
            
    print("You have selected option: ", resp)

    if resp == '1':
        ip_addr = input("Please enter the network address you want to scan (eg:192.168.1.0/24): ")
        print("The IP you entered is: ", ip_addr)
        type(ip_addr) 

        request = scapy.ARP() 
                
        request.pdst = ip_addr
        broadcast = scapy.Ether() 
                
        broadcast.dst = 'ff:ff:ff:ff:ff:ff'
                
        request_broadcast = broadcast / request 
        clients = scapy.srp(request_broadcast, timeout = 10,verbose = 1)[0] 
        print("IP\t\tMac Address")
        for element in clients: 
            print(element[1].psrc + "      " + element[1].hwsrc)


    elif resp == '2':
        target = input("Please enter the IP address you want to scan (eg. 192.168.1.12): ")
        print("The IP you entered is: ", target)
        type(target)
            # Add Banner 
        print("-" * 50)
        print("Scanning Target: " + target)
        print("Scanning started at:" + str(datetime.now()))
        print("-" * 50)
            
        try:
                
            # will scan ports between 1 to 65,535
            for port in range(1,65535):
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                socket.setdefaulttimeout(1)
                    
                # returns an error indicator
                result = s.connect_ex((target,port))
                if result ==0:
                    print("Port {} is open".format(port))
                s.close()
                    
        except KeyboardInterrupt:
            print("\n Exitting Program !!!!")
            sys.exit()
        except socket.gaierror:
            print("\n Hostname Could Not Be Resolved !!!!")
            sys.exit()
        except socket.error:
            print("\ Server not responding !!!!")
            sys.exit()

    elif resp == '3':
        ip_add = input("Please enter the IP address you want to scan: ")
        print("The IP you entered is: ", ip_add)
        type(ip_add)
        
        scanner = nmap.PortScanner()
        
    
        print("The targets Operating system fingerprint :\n", scanner.scan(ip_add, arguments="-O")['scan'][ip_add]['osmatch'][0])   
    elif resp == '4':
        x = 1
        print('Thank you for using the application')
        sys.exit()
            

    elif resp >= '5':
        print("Pltease enter a valid option")