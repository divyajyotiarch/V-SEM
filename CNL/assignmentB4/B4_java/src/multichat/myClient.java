package multichat;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.Scanner;

public class myClient {

	 
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		String str1 = "";
		 DatagramSocket ds = new DatagramSocket(4002); 
		 
		    byte[] buf = new byte[1024];  
		    DatagramPacket dp = new DatagramPacket(buf, 1024);  
		    ds.receive(dp);  
		    String str = new String(dp.getData(), 0, dp.getLength());
		    System.out.print("Server: ");
		    System.out.println(str);  
		    
		     
		    System.out.print("Client: ");
		    str = cin.next();
		    ds.send(dp);  
		    
		    ds.close();  
		 
	}

}
