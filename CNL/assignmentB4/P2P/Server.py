import socket
import os
import threading

class Server:
	def create(self):
		self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.port = 2506
		self.s.bind(('127.0.0.1', self.port))#change ip adress here
		print("Socket binded to port: " + str(self.port))
		self.chatWindow()
		return
	def sender(self):
		while True:
			#m = input()
			msg = bytes(input(), "utf-8")
			
			self.s.sendto(msg, self.addr)
			#if m == "bye":
				#self.s.close()
				#exit()

	def receiver(self):
		while True:
			msg, self.addr = self.s.recvfrom(1024)
			#if str(msg.decode("utf-8")) == "bye":
			#	self.s.close()
			#	exit()
			print("Message from " + str(self.addr) + ": " + str(msg.decode("utf-8")))

	def chatWindow(self):
		print("Chat Window\n############################\n say bye to stop")
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)
		threadS.start()
		threadR.start()
if __name__=='__main__':	
	server = Server()
	server.create()
	


