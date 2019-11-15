package multichat;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PrintStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class myServer {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		String str="";
		Scanner cin = new Scanner(System.in);
		 DatagramSocket ds = new DatagramSocket();
		 ds.setReuseAddress(true);
		 
		// while(true){
				
			 InetAddress ip = InetAddress.getByName("127.0.0.1");  
			 System.out.print("Server: ");
			 	str = cin.next();
			    DatagramPacket dp = new DatagramPacket(str.getBytes(), str.length(), ip, 4002);  
			    ds.send(dp);  
			    
			    System.out.print("Client: ");
			    ds.receive(dp);
			    ds.close();  
		   
			     //     Thread t = new clientHandler();
			      //    t.start();
			               
		//	}

	}

}
