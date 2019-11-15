import os
#import ipaddress	
import math
import socket

#install pip 
#dnf install python3 
#or
#dnf install python-pip  #python2
#pip install ipaddress

subnetmask =""
a =""

def menu():
	print "1. Calculation"
	print "2. Ping"
	print "3. Exit"
	return input ("Choose option")

def calc():
	firstoctet=0
	global a,subnetmask
	if (a==""):
		a = raw_input("Enter IP address: ")
	
	octet = a.split('.')
	c=len(octet)
	if(c==4 or '/' in octet[c-1]):
		s=octet[c-1].split('/')
		octet[c-1]=s[0]
		for i in range (0,c):
			if((int(octet[i])>255 or int(octet[i])<0)):
				a=""
				print "Enter valid IP(e.g. 192.168.1.1)"
				return
	else:
		print "Enter valid IP(e.g. 192.168.1.1)"
		a=""
		return	
	
	if '/' in a :
		print "Classless way of addressing "
		snet = a.split('/')
		octet = snet[0].split('.')
		x = int(snet[1])
		bn=""
		addrmask=[]
		for i in range(0,c):
			bcode = '{0:08b}'.format(int(octet[i]))
			bn+=bcode
		print "IP in binary is "+ bn 
		mask0 = '{0:032b}'.format(0)
		new = list(mask0)
		for i in range(0,x):
			new[i]='1'
		
		s=''
		mask0=s.join(new)
		print mask0		#address mask in binary
		n1 = ~(int(mask0,2))&(0xFFFF)	#returns unsigned value
		n2 = '{0:032b}'.format(n1)
		no = str(int(n2,2)+1)
		print "No. of addresses "+(no)
		
		print "First Address"		#****

		firstaddr = int(mask0,2) & int(bn,2)	#mask AND addr
		faddr = '{0:032b}'.format(firstaddr)
	#	print faddr	#in binary
				
		f_addr = convert(faddr)
		print f_addr		#final first addr

		
		print "Last Address"		#****

		n3 = ~(int(mask0,2))&(0xFFFF) 		#not(mask) OR addr
		n4 = '{0:032b}'.format(n3)
		lastaddr = int(n4,2) | (int(bn,2))
		laddr = '{0:032b}'.format(lastaddr)	
	#	print laddr	#in binary
		
		l_addr = convert(laddr)
		print l_addr
		a=""
		
	else: 
		print "Classful way of addressing "
		firstoctet=int(octet[0])
		subno = input("Enter no. of subnets: ")
		bit = int(math.log(subno,2))+1
		subnet_mask=str(mask(bit))
		no = pow(2,bit) 
		
		if firstoctet<128 :
			
			print a + "  belongs to Class A"
			print "Default Subnet Mask 255.0.0.0 "
			print "Subnet mask : 255."+ subnet_mask + ".0.0"
			subnetmask = "255."+subnet_mask + ".0.0"
			print "First Subnet Block: " + octet[0] +".0.0.0" +" to "+ octet[0] + "."+str((256/no)-1) +".0.0"
			
		elif firstoctet>=128 and firstoctet<192 :
			print a + "  belongs to Class B"
			print "Default Subnet Mask 255.255.0.0 "
			print "Subnet mask : 255.255."+ subnet_mask + ".0"
			subnetmask = "255.255."+ subnet_mask + ".0"
			print "First Subnet Block: " + octet[0] +"."+ octet[1]+".0.0" + " to "+ octet[0] +"." + octet[1]+"."+str((256/no)-1) +".0"

		elif firstoctet>=192 and firstoctet<224 :
			print a + "  belongs to Class C"
			print "Default Subnet Mask 255.255.255.0 "
			print "Subnet mask : 255.255.255."+ subnet_mask 
			subnetmask = "255.255.255."+ subnet_mask 
			print "First Subnet Block: " + octet[0]+"." +octet[1]+"." +octet[2] +".0"+" to "+ octet[0] + "." + octet[1] + "." + octet[2] + "." + str((256/no)-1)

		elif firstoctet>=224 and firstoctet<240 :
			print "Class D IP Address; Used for multicasting"

		elif firstoctet>=240 and firstoctet<256 :
			print "Class D IP Address; Experimental Use"
		a=""


	
def mask(b):
	c=8
	netm=0
	while (b):
		netm = netm + pow(2,c-1)
		b=b-1
		c=c-1
	return netm
			
def ping():
	myhost = socket.gethostname()
	IPaddr = socket.gethostbyname(myhost)
	global a,subnetmask
	mycomputer = raw_input("Set your PC's IP : ")
	a=mycomputer
	calc()
	##change the wired ip address
	os.system('ifconfig')
	os.system('ifconfig p4p1 %s netmask %s'%(mycomputer,subnetmask))
	os.system('ifconfig')

	hostname = raw_input("Input IP you want to ping : ")
	response = os.system ("ping -c 2 " +hostname)
	if response ==0:
    		print(hostname, " is up")
	elif response==256:
		print(hostname, " is not in subnet")
	elif response==512:
		print(hostname, " is shutdown")
	else:
    		print(hostname, " is down")
	
	a=""


	
def convert(addr):		#converts binary to int IP address
	s=''
	l2 = list(addr)

	cnt3=8
	while (cnt3<32):
		l2.insert(cnt3,'.')
		cnt3=cnt3+9
	
	finalno = s.join(l2)		
#	print "final no ", finalno 
	final = finalno.split('.')
	for i in range(4):
		final[i]=int(final[i],2)
#	print final

	final = map(str,final)		#first = list(map(str,first)) in py3 converting int list to str list
		
	cnt4=1
	while(cnt4<6):
		final.insert(cnt4,'.')
		cnt4=cnt4+2
	
			
	final_addr = s.join(final)
	return final_addr		#final converted addr		


choice=0	
loop=1
while loop==1 :
	choice=menu()
	if choice == 1 : 
		calc()
	elif choice == 2 :
		ping()
	elif choice == 3 :
		loop=0
	



#ifconfig code
'''
import commands
from ifparser import Ifcfg
ifdata=Ifcfg(commands.getoutput('ifconfig -a'))
print ifdata.interfaces
eth0=ifdata.get_interfaces('eth0')
print eth0.get_values()
'''
