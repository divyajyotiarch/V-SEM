import socket
import sys
import threading

server=('127.0.0.1',25001)
client_sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
global message
def send_name():
	name=bytes(input("Enter your name: "),encoding='UTF-8')
	client_sock.sendto(name,server)
	
def receive():
	global message
	while True:
		
		message,address=client_sock.recvfrom(4096)
		if message.decode(encoding='UTF-8')!='exit':
			print('Received msg:{}'.format(message.decode(encoding='UTF-8')))
		else:
			print('Exiting multiuser chat')
			break
def send():
	global message
	while True:
		message=bytes(input(),encoding='UTF-8')
		if message.decode(encoding='UTF-8')!='exit':
			client_sock.sendto(message,server)
		else:
			print('Exiting  multiuser chat')
			break


def main():
	send_name()
	print('Type "exit" to exit')
	thread1=threading.Thread(target=send,args=())
	thread2=threading.Thread(target=receive,args=())
	thread1.start()
	thread2.start()

if __name__=='__main__':
	print('Client side')
	main()
