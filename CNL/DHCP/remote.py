import os

os.system('ifconfig')
interfaceName = input('Enter Interface Name : ')
os.system('arp')
ipaddress = input('Enter ip address of machine : ')

user = input('Enter User : ')
password = input('password : ')


#os.system('sshpass -p {} scp -o StrictHostKeyChecking=no install.py {}@{}:/home/{}'.format(password,user,ipaddress,user))

#os.system('sshpass -p {} scp -o StrictHostKeyChecking=no nasm-2.13.03-0.fc24.x86_64.rpm {}@{}:/home/{}'.format(password,user,ipaddress,user))

#os.system('sshpass -p {} ssh -t {}@{} python3 install.py'.format(password,user,ipaddress))

os.system('sshpass -p '+ password  +' ssh -t {}@{} yum install nasm'.format(user,ipaddress))

#os.system('sshpass -p {} ssh -t {}@{} rm nasm-2.13.03-0.fc24.x86_64.rpm'.format(password,user,ipaddress))
