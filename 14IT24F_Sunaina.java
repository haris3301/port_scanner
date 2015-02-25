package com;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
public class PortScanner {
	public static void main(String args[]) throws IOException
	{
		int startPortRange=1;
		int stopPortRange=1024;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		System.out.println("Enter the range of ports");
		startPortRange=Integer.parseInt(br.readLine());
		stopPortRange=Integer.parseInt(br.readLine());


		System.out.println("Enter the IP Address/ name of the host u want to scan:");
		String ipAddr=br.readLine();
		
		if(!ipAddr.matches("^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$")){
			if(ipAddr!=null){
				InetAddress ip = InetAddress.getByName(ipAddr);
				ipAddr=ip.getHostAddress().toString();
				System.out.println("IP Address is:"+ipAddr);
			}
		}
		System.out.println("Open ports are:");
		for(int i=startPortRange; i <=stopPortRange; i++)
		{
			try
			{
				Socket ServerSok = new Socket(ipAddr,i);

				System.out.println( i );

				ServerSok.close();
			}
			catch (Exception e)
			{
				System.out.print(".");
				//System.out.println("Port not in use: " + i );
			}
		}
	}

}



