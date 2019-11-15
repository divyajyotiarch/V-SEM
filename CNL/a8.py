import os
import socket


print("*********MENU**********")
print("1.URL->IP")
print("2.IP->URL")
loop=1
while(loop==1) :
	menu=int(input("Enter choice:"))
	if menu==1:
		url=""
		url=input("Enter URL ")
		ip=socket.gethostbyname(url)
		print("Corresponding IP "+ip)

	if menu==2:
		ip=""
		ip=input("Enter IP ")
		url=socket.gethostbyaddr(ip)
		print("Corresponding URL "+url[0])
		print("Alias list -> ".format(url[1]))
	if menu==3:
		loop=0


print("\nnslookup command")
os.system("nslookup www.google.co.in" )


'''

nslookup

os.system("nslookup +" url)

'''
